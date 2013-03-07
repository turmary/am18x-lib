// tary, 23:23 2013/3/7
#include "am18x_lib.h"
#include "auxlib.h"

const uint32_t f_osc = F_OSCIN;

#define TIMER_NR	TIMER0

int timer_init(void) {
	am18x_rt r;
	timer_conf_t tconf = {
		TIMER_MODE_32_BIT_UNCHANINED,
		TIMER_RESULT_NONE,
		TIMER_SOURCE_INTERNAL,
		TIMER_OPER_CONTINUOUS,
		24000000UL,
	};

	r = timer_conf(TIMER_NR, &tconf);
	if (AM18X_OK != r) {
		printk("error timer_conf()\n");
	}

	timer_cmd(TIMER_NR, TIMER_CMD_START, 0);

	return 0;
}

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for am1808 timer!\n";
	int i = 0;

	printk(title);

	timer_init();

	printk("SYSCFG0->SUSPSRC = 0x%.8X\n", SYSCFG0->SUSPSRC);
/*	printk("TCFG1 = 0x%.8X\n", TIMERCON->TCFG1);
	printk("TCON  = 0x%.8X\n", TIMERCON->TCON);
*/
	while (i++ < 200) {
		printk("%d ", timer_get_count(TIMER_NR));
	}

	printk("\n");

	return 0;
}
