// tary, 5:40 2013/4/17
#include "am18x_lib.h"
#include "arm920t.h"
#include "systick.h"
#include "tps6507x.h"
#include "auxlib.h"
#include "uart.h"

const uint32_t f_osc = F_OSCIN;

static uint32_t one_second_counter(am18x_bool with_wfi) {
	uint32_t milli_seconds = 1000;
	uint32_t counter;

	counter = 0;
	systick_timeout(0);
	while (systick_timeout(milli_seconds) == 0) {
		counter++;
		if (with_wfi) {
			arm_wfi();
		}
	}
	return counter;
}

// 9.6.2 ARM Clock OFF
// The following sequence should be executed by the ARM within
// the ARM Clock Stop Request interrupt ISR
static void arm_clock_off_isr(void) {
	// 1. Check for completion of all ARM master requests
	// (the ARM polls transfer completion statuses of all
	// Master peripherals).

	// 2. Enable the interrupt to be used as the wake-up interrupt
	// that will be used to wake-up the ARM during the ARM
	// clock-on sequence.

	// 3. Execute the wait-for-interrupt (WFI) ARM instruction.
	arm_wfi();

	return;
}

// should be executed by other master as dsp, pru, etc.
static uint32_t arm_clock_off_and_on(void) {
	// 1. The ARM must have the ARM Clock Stop Request interrupt
	// enabled and the associated interrupt serive routine (ISR)
	// set up before the folloing ARM clock shutdown procedure.
	isr_set_hander(AINTC_ARMCLKSTOPREQ, arm_clock_off_isr);
	aintc_sys_enable(AINTC_ARMCLKSTOPREQ);

	psc_state_transition(PSC_ARM, PSC_STATE_DISABLE);

	psc_state_transition(PSC_ARM, PSC_STATE_ENABLE);
	return 0;
}

#define KV_X(x)		{ PWR_TYPE_##x, #x }
kv_t kv_powers[] = {
	KV_X(DCDC1),
	KV_X(DCDC2),
	KV_X(DCDC3),
	KV_X(LDO1),
	KV_X(LDO2),
};

static int wfi_test(void) {
	pll_conf_t pllconf[1];

	printk("one second counter\n");
	pll_get_conf(PLL0, pllconf);
	// pllconf->cflag |= PLL_CFLAG_FROM_POWERON;
	pll_set_conf(PLL0, pllconf);
	clk_node_recalc();
	uart_init();
	printk("pll enabled counter = %d\n", one_second_counter(AM18X_FALSE));
	pll_cmd(PLL0, PLL_CMD_POWER_DOWN, 0);
	clk_node_recalc();
	uart_init();
	printk("pll bypass  counter = %d\n", one_second_counter(AM18X_FALSE));

	printk("one second counter\n");
	printk("without wfi counter = %d\n", one_second_counter(AM18X_FALSE));
	printk("with    wfi counter = %d\n", one_second_counter(AM18X_TRUE));
	return 0;
}

static int poweron_pin_test(void) {
	// tps65070 power_on pin don't work
	psc_state_transition(PSC_GPIO, PSC_STATE_ENABLE);
	gpio_set_mux(GPIO_BANK2, GPIO_PIN_2, GPIO_DIR_OUTPUT);
	gpio_set_output1(GPIO_BANK2, GPIO_PIN_2, GPIO_LOW);
	return 0;
}

static int arm_clock_off_test(void) {
	// arm clock off don't work
	arm_clock_off_and_on();
	printk("%s() complete!\n", "arm_clock_off_and_on");
	return 0;
}

static int pmu_init(void) {
	int i, r;

	tps6507x_conf();
	tps6507x_dump_regs();

	for (i = 0; i < 4; i++) {
		if (i & 0x01) {
			r = tps6507x_get_adc(PWR_TYPE_AC);
			printk("power ac  ");
		} else {
			r = tps6507x_get_adc(PWR_TYPE_SYS);
			printk("power sys ");
		}
		r = r * 1000 * 6 / 0x400UL;
		printk(" voltage: %.4d mV\n", r);
		systick_sleep(100);
	}

	for (i = 0; i < countof(kv_powers); i++) {
		r = tps6507x_get_output(kv_powers[i].key);
		printk("%-5s voltage: %.4d mV\n", kv_powers[i].val, r);
	}

	printk("Setting output voltages\n");
	// tps6507x_set_output(PWR_TYPE_DCDC3, 1300);
	// tps6507x_set_output(PWR_TYPE_LDO1, 1600);

	// am1808.pdf
	// 4.2 Recommanded Operating Conditions
	// Internal RAM Supply Voltage
	// 456MHz versions 1.3V
	tps6507x_set_output(PWR_TYPE_LDO2, 1300);
	for (i = 0; i < countof(kv_powers); i++) {
		r = tps6507x_get_output(kv_powers[i].key);
		printk("%-5s voltage: %.4d mV\n", kv_powers[i].val, r);
	}
	return 0;
}

// am1808.pdf
// 4.2 Recommanded Operating Conditions
// Operating Frequency
typedef struct {
	uint32_t	freq;
	uint16_t	volt;
} opp_t;

static opp_t opps[] = {
	{F_OSCIN,     1000},
	{100000000UL, 1000},
	{200000000UL, 1100},
	{375000000UL, 1200},
	{456000000UL, 1300},
};

static int abs(int x) {
	return x > 0? x: -x;
}

static int dvfs_get_opp(void) {
	int i, volt;

	if (pll_cmd(PLL0, PLL_CMD_IS_ENABLE, 0) != AM18X_OK) {
		return 0;
	}

	volt = tps6507x_get_output(PWR_TYPE_DCDC3);
	for (i = 1; i < countof(opps); i++) {
		if (abs(volt - opps[i].volt) < 50) {
			break;
		}
	}

	if (i >= countof(opps)) {
		i--;
	}
	return i;
}

#define _1K		1000UL
#define _1M		1000000UL

static int dvfs_set_opp(int opp) {
	pll_conf_t pcf[1];
	int l_opp;

	l_opp = dvfs_get_opp();
	if (opp == l_opp) {
		return 0;
	}

	if (opp == 0) {
		pll_cmd(PLL0, PLL_CMD_POWER_DOWN, 0);
		tps6507x_set_output(PWR_TYPE_DCDC3, opps[opp].volt);
		clk_node_recalc();
		uart_init();
		return 0;
	}

	if (opp > l_opp) {
		tps6507x_set_output(PWR_TYPE_DCDC3, opps[opp].volt);		
	}
	pll_get_conf(PLL0, pcf);
	pcf->pllm = opps[opp].freq * pcf->prediv * pcf->postdiv / F_OSCIN;
	// am1808.pdf
	// Page 79,
	// The multiplier values must be chosen such that the PLL output
	// frequency is between 300 and 600 MHz
	if (F_OSCIN * pcf->pllm / pcf->prediv > 600 * _1M) {
		pcf->pllm /= 2;
		pcf->postdiv /= 2;
	}
	pll_set_conf(PLL0, pcf);
	if (opp < l_opp) {
		tps6507x_set_output(PWR_TYPE_DCDC3, opps[opp].volt);		
	}

	clk_node_recalc();
	uart_init();
	return 0;
}

static int dvfs_test(void) {
	int cnt = 0;

	while (cnt++ < 5 * 5 / 2) {
		dvfs_set_opp(cnt % countof(opps));
		printk("Current OPerating Point: %5d mV\n", opps[dvfs_get_opp()].volt);
		printk("Current Frequency:   %9d Hz\n", dev_get_freq(DCLK_ID_ARM));
		#if 0
		if (dvfs_get_opp() == countof(opps) - 1) {
			clk_node_tree();
			break;
		}
		#endif
		systick_sleep(200);
	}
	while (cnt-- > 0) {
		dvfs_set_opp(cnt % countof(opps));
		printk("Current OPerating Point: %5d mV\n", opps[dvfs_get_opp()].volt);
		printk("Current Frequency:   %9d Hz\n", dev_get_freq(DCLK_ID_ARM));
		systick_sleep(200);
	}

	return cnt;
}

static int pmu_power_off_test(void) {
	printk("power off DCDC1\n");
	systick_sleep(100);
	tps6507x_power_switch(PWR_TYPE_DCDC1, AM18X_FALSE);

	printk("power off LDO1\n");
	systick_sleep(100);
	tps6507x_power_switch(PWR_TYPE_LDO1, AM18X_FALSE);

	printk("power off DCDC3\n");
	systick_sleep(100);
	tps6507x_power_switch(PWR_TYPE_DCDC3, AM18X_FALSE);

	#if 0
	// power off worked
	printk("power off usb\n");
	tps6507x_power_switch(PWR_TYPE_USB, AM18X_FALSE);
	printk("power off ac\n");
	tps6507x_power_switch(PWR_TYPE_AC, AM18X_FALSE);
	#endif

	tps6507x_dump_regs();
	return 0;
}

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for power management!\n";
	int i;

	for (i = 0; i < countof(kv_powers); i++) {
		kv_powers[i].val += get_exec_base();
	}

	arm_intr_enable();
	systick_start();

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	pmu_init();

	dvfs_test();

	wfi_test();

	// arm_clock_off_test();

	// poweron_pin_test();

	pmu_power_off_test();

	return 0;
}
