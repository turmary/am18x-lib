// tary, 21:20 2015/6/4
#include "am18x_lib.h"
#include "auxlib.h"
#include "uart.h"

const uint32_t f_osc = F_OSCIN;

const usb0_conf_t usb0_data[1] = {
{
	.highspeed = AM18X_FALSE,
	.host_n_device = AM18X_FALSE,
},
};

static void usb0_isr(void) {
	uint32_t intr;

	intr = usb0_intr_state();
	printk("intr = 0x%.8X\n", intr);

	usb0_intr_clear();
	return;
}

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for am1808 usb device!\n";

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	usb0_conf(usb0_data);

	isr_set_handler(AINTC_USB0_INT, usb0_isr);
	aintc_sys_enable(AINTC_USB0_INT);

	printk("usb0 session started\n");

	for(;;);

	return 0;
}
