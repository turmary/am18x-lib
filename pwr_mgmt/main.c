// tary, 5:40 2013/4/17
#include "am18x_lib.h"
#include "arm920t.h"
#include "systick.h"
#include "tps6507x.h"
#include "auxlib.h"
#include "uart.h"
#include "dvfs.h"
#include "psc_config.h"

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

static void chipsig0_isr(void) {
	SYSCFG0->CHIPSIG_CLR = FIELD_SET(0, CHIPSIG_X_MASK(0), CHIPSIG_X_clear(0));
	printk("%s()\n", __func__);
	return;
}

// 9.6.2 ARM Clock OFF
// The following sequence should be executed by the ARM within
// the ARM Clock Stop Request interrupt ISR
static void arm_clock_off_isr(void) {
	// printk("%s()\n", __func__);
	// 1. Check for completion of all ARM master requests
	// (the ARM polls transfer completion statuses of all
	// Master peripherals).

	// 2. Enable the interrupt to be used as the wake-up interrupt
	// that will be used to wake-up the ARM during the ARM
	// clock-on sequence.
	isr_set_hander(AINTC_SYSCFG_CHIPINT0, chipsig0_isr);
	aintc_sys_enable(AINTC_SYSCFG_CHIPINT0);

	// 3. Execute the wait-for-interrupt (WFI) ARM instruction.
	arm_wfi();

	return;
}

// should be executed by other master as dsp, pru, etc.
static uint32_t arm_clock_off_and_on(void) {
	PRU_con_t* pru = PRU0;
	am18x_rt r;
	uint32_t* pram;

	// 1. The ARM must have the ARM Clock Stop Request interrupt
	// enabled and the associated interrupt serive routine (ISR)
	// set up before the folloing ARM clock shutdown procedure.
	isr_set_hander(AINTC_ARMCLKSTOPREQ, arm_clock_off_isr);
	aintc_sys_enable(AINTC_ARMCLKSTOPREQ);

	psc_state_transition(PSC_PRU, PSC_STATE_ENABLE);

	pru_cmd(pru, PRU_CMD_ENABLE, 0);

	pram = (uint32_t*)PRU_DataRAM0_BASE;
#if 1
	pram[0] = 2;
#else
	pram[0] = 0;
	isr_set_hander(AINTC_SYSCFG_CHIPINT0, chipsig0_isr);
	aintc_sys_enable(AINTC_SYSCFG_CHIPINT0);
	// SYSCFG0->CHIPSIG = FIELD_SET(0, CHIPSIG_X_MASK(0), CHIPSIG_X_assert(0));
#endif
	// psc_state_transition(PSC_ARM, PSC_STATE_DISABLE);
	pram[1] = ((0) << 24)	|
		((0) << 16)	|
		((PSC_ARM) << 8)|
		((MDSTATx_STATE_Disable) << 0);
	// psc_state_transition(PSC_ARM, PSC_STATE_ENABLE);
	pram[2] = ((0) << 24)	|
		((0) << 16)	|
		((PSC_ARM) << 8)|
		((MDSTATx_STATE_Enable) << 0);
	pru_load(pru, (const uint32_t*)pru_code, countof(pru_code));

	pru_cmd(pru, PRU_CMD_RUN, 0);
	delay(1000000);
	while ((r = pru_cmd(pru, PRU_CMD_IS_HALT, 0)) != AM18X_OK);

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

	// tps6507x_conf();
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

static int dvfs_test(void) {
	int cnt = 0;

	while (cnt++ < 5 * 5 / 2) {
		dvfs_set_opp(cnt % OPP_CNT);
		printk("Current OPerating Point: %5d mV\n", dvfs_get_volt(dvfs_get_opp()));
		printk("Current Frequency:   %9d Hz\n", dev_get_freq(DCLK_ID_ARM));
		#if 0
		if (dvfs_get_opp() == OPP_CNT - 1) {
			clk_node_tree();
			break;
		}
		#endif
		systick_sleep(200);
	}
	while (cnt-- > 0) {
		dvfs_set_opp(cnt % OPP_CNT);
		printk("Current OPerating Point: %5d mV\n", dvfs_get_volt(dvfs_get_opp()));
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

	arm_clock_off_test();

	pmu_init();

	dvfs_test();

	wfi_test();

	// poweron_pin_test();

	pmu_power_off_test();

	return 0;
}
