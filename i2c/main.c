// tary, 23:04 2013/3/25
#include "am18x_lib.h"
#include "arm920t.h"
#include "auxlib.h"
#include "tca6416.h"
#include "systick.h"

const uint32_t f_osc = F_OSCIN;

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for i2c-gpio!\n";
	int i;

	arm_intr_enable();
	systick_start();

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	tca6416_conf(0xFF23UL);
	for (i = 0; i < 2 * 120; i++) {
		printk("Port[1:0] = 0x%.4X\n", 0xFFE3UL & tca6416_read());
		tca6416_write(__field_xset(0, 0x00C0UL, i));
		systick_sleep(500);
	}

	return 0;
}
