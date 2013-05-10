// tary, 23:50 2013/5/10

// instruction guide refer to
// http://processors.wiki.ti.com/index.php/PRU_Assembly_Instructions

	.origin		0
	.entrypoint	load

load:
	QBA	_start

putchar:
	// uart_write_byte(UART2, c);
	SBCO	R0.B0, C12, #0x00, 1
	// while (AM18X_FALSE == uart_state(UART2, STATE_TX_EMPTY));
_putchar_1:
	LBCO	R1.B0, C12, #0x14, 1
	QBBC	_putchar_1, R1.T6

	RET

_start:
	ZERO	&R2, 4

_puts:
	LBBO	R0.B0, R2, #0x00, 1
	QBEQ	_exit, R0.B0, #0x00
	CALL	putchar
	ADD	R2, R2, #0x01
	QBA	_puts

_exit:
	HALT
