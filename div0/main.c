// tary, 1:12 2013/3/6
#include "am18x_lib.h"
#include "auxlib.h"

const uint32_t f_osc = F_OSCIN;

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for div by 0!\n";
	int divider = 0;
	int result = 5;

	printk(title);
	result = 0x100 / divider;
	printk("divide process end with [%d]\n", result);
	return 0;
}
