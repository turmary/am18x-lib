// tary, 5:40 2013/4/17
#include "am18x_lib.h"
#include "arm920t.h"
#include "systick.h"
#include "auxlib.h"
#include "uart.h"

const uint32_t f_osc = F_OSCIN;
static const int32_t delay_count = 284 * 1000;

static const pll_conf_t pllconf[1] = {
{
	.pllm = 30,
	.prediv = 1,
	.postdiv = 2,
	.plldiv = { 1, 2, 3, 4, 3, 1, 6, },
	.cflag = PLL_CFLAG_EXT_CLK_OSCIN |
		PLL_CFLAG_REF_CRYSTAL    |
		PLL_CFLAG_FROM_POWERON,
}
};

static kv_t reset_sources[] = {
	KV(PLL_RESET_SOFTWARE),
	KV(PLL_RESET_EXTERNAL),
	KV(PLL_RESET_POWER_ON),
};

static int check_delay(void) {
	uint32_t start_minutes, stop_minutes;

	start_minutes = systick_elapsed();
	delay(delay_count);
	stop_minutes = systick_elapsed();
	printk("delay start: %d ms\n", start_minutes);
	printk("delay stop : %d ms\n", stop_minutes);
	printk("delay used : %d ms\n", stop_minutes - start_minutes);
	printk("\n\n");
	return 0;
}

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for pll!\n";
	pll_reset_t reset;

	arm_intr_enable();
	systick_start();

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	reset = pll_get_reset();
	printk("RSTYPE = 0x%.8X\n", PLL0->RSTYPE);
	printk("Reset by %s\n", reset_sources[reset].val);

	check_delay();

	pll_set_conf(PLL0, pllconf);
	clk_node_recalc();
	uart_init();

	printk("After pll opened\n");
	check_delay();

	pll_cmd(PLL0, PLL_CMD_SOFT_RESET, 0);

	return 0;
}
