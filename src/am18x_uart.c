// tary, 0:22 2012/12/22
#include "am18x_uart.h"

uint32_t uart_input_clock_frequency(UART_con_t* ucon) {
	return F_OSC;
}

static inline uint32_t uart_get_divisor(UART_con_t* ucon, uint32_t baud_rate) {
	uint32_t samp_clk;

	samp_clk = 16;
	if (FIELD_GET(ucon->MDR, MDR_OSM_SEL_MASK) == MDR_OSM_SEL_13x) {
		samp_clk = 13;
	}

	return uart_input_clock_frequency(ucon) / (samp_clk * baud_rate);
}

