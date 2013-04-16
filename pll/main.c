// tary, 5:40 2013/4/17
#include "am18x_lib.h"
#include "arm920t.h"
#include "systick.h"
#include "auxlib.h"

extern uint32_t f_osc = F_OSCIN;
const int32_t delay_count = 284 * 1000;

static const pll_conf_t pllconf[1] = {
{
	.pllm = 30,
	.prediv = 1,
	.postdiv = 2,
	.plldiv = { 1, 2, 3, 4, 3, 1, 6, },
	.cflag = PLL_CFLAG_EXT_CLK_OSCIN |
		PLL_CFLAG_REF_CRYSTAL    |
		PLL_CFLAG_FROM_POWER_DOWN,
}
};

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for pll!\n";

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	pll_conf(PLL0, pllconf);
	f_osc = F_OSCIN * pllconf->pllm / (pllconf->prediv * pllconf->postdiv);

	uart_init();

	arm_intr_enable();
	systick_start();

	printk("delay start: %d ms\n", systick_elapsed());
	delay(delay_count);
	printk("delay stop : %d ms\n", systick_elapsed());

	return 0;
}
