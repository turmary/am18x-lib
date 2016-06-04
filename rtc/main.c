// tary, 1:07 2011/9/12
#include "am18x_lib.h"
#include "auxlib.h"
#include "arm920t.h"
#include "rtc.h"

const uint32_t f_osc = F_OSCIN;

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for rtc!\n";

	arm_intr_enable();
	systick_start();

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	rtc_operation();

	printk("\n");

	arm_intr_disable();

	return 0;
}
