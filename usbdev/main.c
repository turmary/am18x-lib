// tary, 21:20 2015/6/4
#include "am18x_lib.h"
#include "arm920t.h"
#include "systick.h"
#include "auxlib.h"
#include "uart.h"

const uint32_t f_osc = F_OSCIN;

const usb0_conf_t usb0_data[1] = {
{
	.highspeed = AM18X_FALSE,
	.host_n_device = AM18X_FALSE,
},
};

static kv_t intrs_kv[] = {
	INTxR_TXEPn_yes(0), "EP0",
	INTxR_TXEPn_yes(1), "EP1T",
	INTxR_TXEPn_yes(2), "EP2T",
	INTxR_TXEPn_yes(3), "EP3T",
	INTxR_TXEPn_yes(4), "EP4T",
	INTxR_RXEPn_yes(1), "EP1R",
	INTxR_RXEPn_yes(2), "EP2R",
	INTxR_RXEPn_yes(3), "EP3R",
	INTxR_RXEPn_yes(4), "EP4R",
	INTxR_INTUSB_yes(INTUSB_SUSPEND), "SUSPEND",
	INTxR_INTUSB_yes(INTUSB_RESUME), "RESUME",
	INTxR_INTUSB_yes(INTUSB_RESET), "RESET",
	INTxR_INTUSB_yes(INTUSB_SOF), "SOF",
	INTxR_INTUSB_yes(INTUSB_CONN), "CONN",
	INTxR_INTUSB_yes(INTUSB_DISCON), "DISCON",
	INTxR_INTUSB_yes(INTUSB_SESSREQ), "SESSREQ",
	INTxR_INTUSB_yes(INTUSB_VBUSERR), "VBUSERR",
	INTxR_INTUSB_yes(INTUSB_DRVVBUS), "DRVVBUS",
};

#define QUEUE_SIZE	1024
uint32_t queue[QUEUE_SIZE];
vuint32_t queue_front = 0, queue_rear = 0;

int queue_in(uint32_t data) {
	uint32_t front;

	front = (queue_front + 1) % QUEUE_SIZE;
	if (front == queue_rear ) {
		printk("*");
		return -1;
	}

	queue[queue_front] = data;

	// arm_intr_disable();
	queue_front = front;
	// arm_intr_enable();

	return 0;
}

int queue_out(uint32_t* pdata) {
	uint32_t data;

	if (queue_rear == queue_front) {
		return -1;
	}

	data = queue[queue_rear];

	arm_intr_disable();
	queue_rear = (queue_rear + 1) % QUEUE_SIZE;
	arm_intr_enable();

	if (pdata) {
		*pdata = data;
	}

	return 0;
}

int print_intrs(uint32_t intr) {
	int i, k;

	k = 0;
	for (i = 0; i < countof(intrs_kv); i++) {
		if (intr & intrs_kv[i].key) {
			printk("%s ", intrs_kv[i].val);
			k++;
		}
	}
	if (k) {
		printk("\n");
	}

	return 0;
}

static void usb0_isr(void) {
	uint32_t intr;

	intr = usb0_intr_state();
	usb0_intr_clear();

	// printk("intr =    0x%.8X\n", intr);
	queue_in(intr);
	/*
	printk("INTRTX =  0x%.8X\n", USB0->INTRTX);
	printk("INTRRX =  0x%.8X\n", USB0->INTRRX);
	printk("INTRUSB = 0x%.8X\n", USB0->INTRUSB);
	*/
	return;
}

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for am1808 usb device!\n";
	int i;

	arm_intr_enable();
	systick_start();

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	usb0_conf(usb0_data);

	printk("usb0 session started\n");

	for (i = 0; i < countof(intrs_kv); i++) {
		intrs_kv[i].val += get_exec_base();
	}
	isr_set_handler(AINTC_USB0_INT, usb0_isr);
	aintc_sys_enable(AINTC_USB0_INT);

	for(;;) {
		uint32_t intr;

		if (queue_out(&intr) == 0) {
			print_intrs(intr);
		}
	}

	return 0;
}
