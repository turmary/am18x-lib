// tary, 23:04 2013/4/26
#include "am18x_lib.h"
#include "arm920t.h"
#include "systick.h"
#include "auxlib.h"

const uint32_t f_osc = F_OSCIN;

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for gpio!\n";
	int i;

	arm_intr_enable();
	systick_start();

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	psc_state_transition(PSC_GPIO, PSC_STATE_ENABLE);
	gpio_set_mux(GPIO_BANK7, GPIO_PIN_1, GPIO_DIR_INPUT);
	gpio_set_mux(GPIO_BANK7, GPIO_PIN_2, GPIO_DIR_INPUT);
	gpio_set_mux(GPIO_BANK7, GPIO_PIN_3, GPIO_DIR_INPUT);
	gpio_set_mux(GPIO_BANK7, GPIO_PIN_4, GPIO_DIR_INPUT);

	for (i = 0; i < 2 * 120; i++) {
		printk("BOOT[4:1] = 0x%.4X\n", 
		  gpio_get_inputs(GPIO_BANK7,
			GPIO_PINS_1 |
			GPIO_PINS_2 |
			GPIO_PINS_3 |
			GPIO_PINS_4
		  ) >> 1
		);
		systick_sleep(500);
	}

	return 0;
}
