// tary, 1:03 2012/12/23
#include "am18x_lib.h"
#include "systick.h"
#include "uart.h"
#include "auxlib.h"

#define SYSTICK_PERIOD			10/* milli seconds */

// 1015640A_AM1808_SOM-M1_Schematic.pdf
#define BUFF_OEn			GPIO_BANK2,GPIO_PIN_6

static int buff_en_enable(am18x_bool on_noff) {
	uint32_t v = on_noff? GPIO_LOW: GPIO_HIGH;

	psc_state_transition(PSC_GPIO, PSC_STATE_ENABLE);

	gpio_set_mux(BUFF_OEn, GPIO_DIR_OUTPUT);
	gpio_set_output1(BUFF_OEn, v);

	// gpio_set_mux(BUFF_OEn, GPIO_DIR_INPUT);
	// printk("BUFF_OEn = %d\n", gpio_get_output1(BUFF_OEn));
	return 0;
}

int low_level_init(void) {
	extern int isr_init(void);
	extern int output_a_char(int);
	int r;

	// output_a_char('S');

	syscfg_kick(AM18X_FALSE);

	isr_init();

	clk_node_init();
	uart_init();

	if (AM18X_OK != (r = systick_init(SYSTICK_PERIOD))) {
		printk("systick_init() error\n");
		return r;
	}

/*	if (AM18X_OK != (r = systick_start())) {
		printk("systick_start() error\n");
		return r;
	}
*/
	// invalid operation
	buff_en_enable(AM18X_FALSE);

#ifdef _M_BOOT_DELAY
	delay(284091 * 3);
#endif
	return AM18X_OK;
}
