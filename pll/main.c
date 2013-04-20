// tary, 5:40 2013/4/17
#include "am18x_lib.h"
#include "arm920t.h"
#include "systick.h"
#include "auxlib.h"
#include "uart.h"

uint32_t f_osc = F_OSCIN;
const int32_t delay_count = 284 * 1000;

static pll_conf_t pllconf[1] = {
{
	.pllm = 30,
	.prediv = 1,
	.postdiv = 2,
	.plldiv = { 1, 2, 3, 4, 3, 1, 6, },
	.cflag = PLL_CFLAG_EXT_CLK_OSCIN |
		PLL_CFLAG_REF_CRYSTAL    |
		PLL_CFLAG_FROM_POWER_DOWN|
		PLL_CFLAG_EXT_CLK_PLL1,
}
};

kv_t reset_sources[] = {
	KV(PLL_RESET_SOFTWARE),
	KV(PLL_RESET_EXTERNAL),
	KV(PLL_RESET_POWER_ON),
};

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for pll!\n";
	uint32_t start_minutes, stop_minutes;
	pll_reset_t reset;
	int i;

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	for (i = 0; i < countof(reset_sources); i++) {
		reset_sources[i].val += get_exec_base();
	}
	reset = pll_get_reset();
	printk("RSTYPE = 0x%.8X\n", PLL0->RSTYPE);
	printk("Reset by %s\n", reset_sources[reset].val);

	// ********** tree 1 **********
	printk("\n\n");
	clk_node_tree();

	pllconf->pllm = 7;
	pll_conf(PLL1, pllconf);
	clk_node_recalc_freq();
	// ********** tree 2 **********
	printk("\n\n");
	clk_node_tree();

	pllconf->pllm = 25;
	pll_conf(PLL0, pllconf);
	clk_node_change_parent(CLK_NODE_PLL0_PLLEN, CLK_NODE_PLL_EXTSRC);
	clk_node_change_parent(CLK_NODE_EMA_CLKSRC, CLK_NODE_DIV4_5X);
	clk_node_change_parent(CLK_NODE_OCSEL0_OCSRC, CLK_NODE_PLL1_OBSCLK);
	clk_node_recalc_freq();
	uart_init();
	// ********** tree 3 **********
	printk("\n\n");
	clk_node_tree();

	arm_intr_enable();
	systick_start();

	start_minutes = systick_elapsed();
	delay(delay_count);
	stop_minutes = systick_elapsed();
	printk("delay start: %d ms\n", start_minutes);
	printk("delay stop : %d ms\n", stop_minutes);

	clk_node_output();

	clk_node_change_parent(CLK_NODE_DIV4_5X, CLK_NODE_DIV4_5);
	clk_node_change_parent(CLK_NODE_PLL1_OBSCLK, CLK_NODE_OSCDIV1);
	clk_node_change_parent(CLK_NODE_ASYNC3, CLK_NODE_PLL1_SYSCLK2);
	uart_init();
	// ********** tree 4 **********
	printk("\n\n");
	clk_node_tree();

	// pll_cmd(PLL0, PLL_CMD_SOFT_RESET, 0);

	return 0;
}
