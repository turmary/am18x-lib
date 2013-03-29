// tary, 1:12 2013/3/6
#include "am18x_lib.h"
#include "arm920t.h"
#include "systick.h"
#include "auxlib.h"

const uint32_t f_osc = F_OSCIN;

const int32_t delay_count = 284 * 1000;

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for div by 0!\n";
	int divider = 0;
	int result = 5;

	arm_intr_enable();
	systick_start();

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	printk("delay start: %d ms\n", systick_elapsed());
	delay(delay_count);
	printk("delay stop : %d ms\n", systick_elapsed());

	result = 0x100 / divider;
	printk("divide process end with [%d]\n", result);
	return 0;
}
