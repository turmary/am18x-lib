// tary, 0:51 2012/12/23
#include "am18x_lib.h"
#include "auxlib.h"
#include "uart.h"

const uint32_t f_osc = F_OSC;

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for am1808 uart!\n";

	printk(title);
	printk("now press any key\n");
	getchar();
	printk("press complete\n");
	return 0;
}
