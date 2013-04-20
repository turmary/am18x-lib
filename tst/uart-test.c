// tary, 23:32 2013/1/5
#include <stdio.h>
#include "am18x_lib.h"

UART_con_t uart_reg[1] = {
{
	0,		// RBR
	0,		// IER
	0x0001,		// IIR
	0,		// LCR

	0,		// MCR
	0x60,		// LSR
	0,		// MSR
	0,		// SCR

	0,{0,0,0},	// DLL
	0,{0,0,0},	// DLH
	{0x11020002,	// REVID1
	0},		// REVID2

	0x0002,		// PWREMU_MGMT
	0,		// MDR
},
};

uint32_t dev_get_freq(uint32_t dc_id) {
	return F_OSCIN;
}

int main(int argc, char* argv[]) {
	uart_conf_t conf;
	int i;

	uart_init_conf(&conf);
	uart_set_conf(uart_reg, &conf);

	for (i = 0; i < sizeof(uart_reg) / sizeof (unsigned); i++) {
		printf("reg[%2d] = 0x%.8X\n", i, ((unsigned*)uart_reg)[i]);
	}
	return 0;
}
