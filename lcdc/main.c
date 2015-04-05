// tary, 3:28 2013/10/27
#include "am18x_lib.h"
#include "arm920t.h"
#include "systick.h"
#include "auxlib.h"
#include "tft43.h"

const uint32_t f_osc = F_OSCIN;

const int32_t delay_count = 284 * 1000;

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for lcdc!\n";

	arm_intr_enable();
	systick_start();

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	tft43_init();

	/* printk("PINMUXx[5]  = 0x%.8X\n", SYSCFG0->PINMUXx[5]);
	printk("PINMUXx[16] = 0x%.8X\n", SYSCFG0->PINMUXx[16]);
	printk("PINMUXx[17] = 0x%.8X\n", SYSCFG0->PINMUXx[17]);
	printk("PINMUXx[18] = 0x%.8X\n", SYSCFG0->PINMUXx[18]);
	printk("PINMUXx[19] = 0x%.8X\n", SYSCFG0->PINMUXx[19]);
	*/

	tft43_colors();
	
	return 0;
}
