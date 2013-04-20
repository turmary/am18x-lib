// tary, 1:38 2012/12/23
#include "am18x_lib.h"
#include "uart.h"

// AM1808 UART2 pins
#define UART2_TXD		4,20,2
#define UART2_RXD		4,16,2

int uart_init(void) {
	uart_conf_t conf;

	psc_state_transition(PSC_UART2, PSC_STATE_DISABLE);
	psc_state_transition(PSC_UART2, PSC_STATE_ENABLE);

	syscfg_pinmux(UART2_TXD);
	syscfg_pinmux(UART2_RXD);

	uart_init_conf(&conf);
	uart_set_conf(UART2, &conf);

	return 0;
}

int __putchar(int c) {
	while (AM18X_FALSE == uart_state(UART2, STATE_TX_EMPTY));
	uart_write_byte(UART2, c);
	return c;
}

int putchar(int c) {
	if (c == '\n') {
		__putchar('\r');
	}
	__putchar(c);
	return c;
}

int getchar(void) {
	while (AM18X_FALSE == uart_state(UART2, STATE_RX_READY));
	return uart_read_byte(UART2);
}

int peekchar(void) {
	if (AM18X_FALSE == uart_state(UART2, STATE_RX_READY)) {
		return -1;
	}
	return uart_read_byte(UART2);
}
