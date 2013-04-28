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

int main(int argc, char* argv[]) {
	pll_conf_t pllconf[1];
	const char* title = "\nam18x library for power management!\n";
	uint32_t r;
	int i;

	arm_intr_enable();
	systick_start();

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	tps6507x_conf();

	for (i = 0; i < 2 * 120; i++) {
		r = tps6507x_get_adc(i & 0x01);
		r = r * 1000 * 6 / 0x400UL;
		if (i & 0x01) {
			printk("power ac  ");
		} else {
			printk("power sys ");
		}
		printk(" voltage: %.4d mV\n", r);
		systick_sleep(500);
	}

	#if 0
	// arm clock off don't work
	arm_clock_off_and_on();
	printk("%s() complete!\n", "arm_clock_off_and_on");
	#endif

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

	#if 0
	// tps65070 power_on pin don't work
	psc_state_transition(PSC_GPIO, PSC_STATE_ENABLE);
	gpio_set_mux(GPIO_BANK2, GPIO_PIN_2, AM18X_TRUE);
	gpio_set_output1(GPIO_BANK2, GPIO_PIN_2, GPIO_LOW);
	#endif

	return 0;
}
