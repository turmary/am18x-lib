// tary, 1:03 2012/12/23
#include "am18x_lib.h"
#include "systick.h"
#include "uart.h"
#include "auxlib.h"

#define SYSTICK_PERIOD			10/* milli seconds */

int low_level_init(void) {
	int r;
/*
	if (AM18X_OK != (r = intr_con_init(INTRCON))) {
		return r;
	}

	if (AM18X_OK != (r = timer_con_init())) {
		return r;
	}
*/
	uart_init();
	putchar('H');
	putchar('E');
	putchar('L');
	putchar('L');
	putchar('O');
	putchar('\n');
	for(;;);
/*
	if (AM18X_OK != (r = systick_init(SYSTICK_PERIOD))) {
		printk("systick_init() error\n");
		return r;
	}

	if (AM18X_OK != (r = systick_start())) {
		printk("systick_start() error\n");
		return r;
	}
*/
	return AM18X_OK;
}
