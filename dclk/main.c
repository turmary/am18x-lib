// tary, 5:40 2013/4/17
#include "am18x_lib.h"
#include "arm920t.h"
#include "systick.h"
#include "auxlib.h"
#include "uart.h"

uint32_t f_osc = F_OSCIN;

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

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for dclk!\n";

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	clk_node_output();

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
	// clk_node_set_parent(CLK_NODE_PLL0_PLLEN, CLK_NODE_PLL_EXTSRC);
	clk_node_set_parent(CLK_NODE_EMA_CLKSRC, CLK_NODE_DIV4_5X);
	clk_node_set_parent(CLK_NODE_OCSEL0_OCSRC, CLK_NODE_PLL1_OBSCLK);
	clk_node_recalc_freq();
	uart_init();

	// ********** tree 3 **********
	printk("\n\n");
	clk_node_tree();

	clk_node_set_parent(CLK_NODE_DIV4_5X, CLK_NODE_DIV4_5);
	clk_node_set_parent(CLK_NODE_PLL1_OBSCLK, CLK_NODE_OSCDIV1);
	clk_node_set_parent(CLK_NODE_ASYNC3, CLK_NODE_PLL1_SYSCLK2);
	uart_init();
	// ********** tree 4 **********
	printk("\n\n");
	clk_node_tree();

	return 0;
}
