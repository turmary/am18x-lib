// tary, 17:51 2013/3/9
#include "am18x_lib.h"
#include "auxlib.h"
#include "systick.h"
#include "arm920t.h"

const uint32_t f_osc = F_OSCIN;

int systick_callback(int ticks) {
	static int l_ticks = 0;

	if ((ticks - l_ticks) * systick_period() >= 1000UL) {
		l_ticks = ticks;
		printk("\nelapse %d seconds", ticks * systick_period() / 1000UL);
		return 1;
	}
	return 0;
}

int systick_callbackx(int ticks) {
	static int l_seconds = 0;

	printk("\nelapse %d seconds", l_seconds);

	if (l_seconds != systick_elapsed() / 1000UL) {
		l_seconds = systick_elapsed() / 1000UL;
		printk("\nelapse %d seconds", l_seconds);
		return 1;
	}
	return 0;
}

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for am18x interrupt!\n";
	unsigned milli_seconds = 5000;

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	arm_intr_enable();

	systick_set_handler(systick_callbackx);
	systick_start();
	/*
	systick_timeout(0);
	while (systick_timeout(milli_seconds) == 0);
	*/
	systick_sleep(milli_seconds);

	printk("\n");

	arm_intr_disable();

	return 0;
}
