// tary, 18:43 2016/3/25
#include "rombios.h"

// This is for compiling with gcc
#define ASM_START	asm (
#define ASM_END		);


asm (
"	.section .init, \"ax\"	\n"
"	.global	_start		\n"
"_start:			\n"
"	.org	0x10		\n"
"	nop			\n"
"	mov	r0, r0		\n"
"	.global get_exec_base	\n"
"get_exec_base:			\n"
"	MOV	R0, SL		\n"
"	MOV	PC, LR		\n"
);
