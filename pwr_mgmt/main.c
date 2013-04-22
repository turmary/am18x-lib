// tary, 5:40 2013/4/17
#include "am18x_lib.h"
#include "arm920t.h"
#include "systick.h"
#include "auxlib.h"

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

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for power management!\n";
	int i;

	arm_intr_enable();
	systick_start();

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	printk("one second counter\n");
	printk("without wfi counter = %d\n", one_second_counter(AM18X_FALSE));
	printk("with    wfi counter = %d\n", one_second_counter(AM18X_TRUE));

	return 0;
}
