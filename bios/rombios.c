// tary, 18:43 2016/3/25
#include "rombios.h"

// This is for compiling with gcc
// #define ASM_START	asm (
// #define ASM_END		);

int function(int in) {
	return in * in;
}

void rombios(void) {
ASM_START
	.global __got_start
	.global __got_end

	.section .init, \"ax\"
	nop
	nop

	.section .text, \"ax\"
	.global	_start
_start:
	b	__entry

	.global get_exec_base
get_exec_base:
	MOV	R0, SL
	MOV	PC, LR

@--------
@- POST -
@--------
	.org	0xe05b		@ POST Entry Point
	.byte	0x0
post:
	MOV	R0, #R0_INIT

	.org	0xfff0		@ Power-up Entry Point
__entry:
	b	post
ASM_END
}
