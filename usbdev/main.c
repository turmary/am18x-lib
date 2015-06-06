// tary, 21:20 2015/6/4
#include "am18x_lib.h"
#include "auxlib.h"
#include "uart.h"

const uint32_t f_osc = F_OSCIN;

const usb0_conf_t usb0_data[1] = {
{
	AM18X_FALSE,
	AM18X_FALSE,
},
};

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for am1808 usb device!\n";

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	usb0_conf(usb0_data);

	for(;;);

	return 0;
}
