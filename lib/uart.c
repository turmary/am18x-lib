// tary, 1:38 2012/12/23
#include "am18x_lib.h"
#include "uart.h"

// S3C2440 UART0 pins
#define UART0_PORT		GPIOH
#define UART0_TXD_PIN		GPIO_PIN_2
#define UART0_RXD_PIN		GPIO_PIN_3

int uart_init(void) {
	uart_conf_t conf;

	gpio_set_res(UART0_PORT, UART0_TXD_PIN, GPIO_RES_NONE);
	gpio_set_mux(UART0_PORT, UART0_RXD_PIN, GPIO_AF);
	gpio_set_res(UART0_PORT, UART0_TXD_PIN, GPIO_RES_NONE);
	gpio_set_mux(UART0_PORT, UART0_RXD_PIN, GPIO_AF);

	uart_init_conf(&conf);
	uart_set_conf(UART0, &conf);

	return 0;
}

int __putchar(int c) {
	while (AM18X_FALSE == uart_state(UART0, STATE_TX_EMPTY));
	uart_write_byte(UART0, c);
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
	while (AM18X_FALSE == uart_state(UART0, STATE_RX_READY));
	return uart_read_byte(UART0);
}

int peekchar(void) {
	if (AM18X_FALSE == uart_state(UART0, STATE_RX_READY)) {
		return -1;
	}
	return uart_read_byte(UART0);
}
