// tary, 1:38 2012/12/23
#include "am18x_lib.h"
#include "uart.h"

// AM1808 UART2 pins
#define UART2_TXD		4,20,2
#define UART2_RXD		4,16,2
#define UART_DEL        	0x7F
#define UART_BACKSPACE		0x08
#define UART_CR			0x0D
#define UART_LF			0x0A

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
	uart_write_byte(UART2, c);
	while (AM18X_FALSE == uart_state(UART2, STATE_TX_EMPTY));
	return c;
}

int putchar(int c) {
	if (c == UART_LF) {
		__putchar(UART_CR);
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

int uart_gets(char *line, int n) {
	int cnt = 0;
	char c;

	do {
		if ((c = getchar()) == UART_CR) {
			c = UART_LF;				/* read character */
		}

		if (c != UART_BACKSPACE	&& c != UART_DEL) {	/* process backspace */
			cnt++;
			*line++ = c;
			if (c != UART_LF) {			/* echo and store character */
				putchar(c);
			}
		} else if (cnt != 0) {
			cnt--;
			line--;
			putchar(UART_BACKSPACE);		/* echo backspace */
			putchar(' ');
			putchar(UART_BACKSPACE);
		}
	} while (cnt < n - 1 &&	c != UART_LF);			/* check limit and line feed */
	*line = 0;						/* mark end of string */
	return cnt;
}
