@tary, 22:42 2012/11/27
@*******************************************************************************
@*                     the startup code for am18x_lib                          *
@*******************************************************************************

#include "linkage.h"
#include "arm920t.h"
#include "am18x_map_s.h"

.EQU		USR_Stack_Size, 0x00002000
.EQU		ISR_Stack_Size, 0x00002000
.EQU		ABT_Stack_Size, 0x00002000
.EQU		UND_Stack_Size, 0x00002000

		.section .init, "ax"
		.arm

		.macro	ldr_fix, Rx, symbol
		LDR	\Rx, = \symbol
		ADD	\Rx, \Rx, R9
		.endm

		.global	_start
_start:
__load_addr:
__vectors_start:
		B	HandleReset
		LDR	PC, undef_addr
		LDR	PC, swi_addr
		LDR	PC, pabt_addr
		LDR	PC, dabt_addr
		LDR	PC, notused_addr
		LDR	PC, irq_addr
		LDR	PC, fiq_addr
__vectors_jump:	.long	HandleReset
undef_addr:	.long	HandleUndef
swi_addr:	.long	HandleSWI
pabt_addr:	.long	HandlePrefetchAbort
dabt_addr:	.long	HandleDataAbort
notused_addr:	.long	HandleNotUsed
irq_addr:	.long	HandleIRQ
fiq_addr:	.long	HandleFIQ
__vectors_end:

HandleSWI:
HandleNotUsed:
HandleFIQ:
__dummy_handler:
		B	__dummy_handler


HandleIRQ:
		.EXTERN	c_irq_handler

		SUB	LR, LR, #4
		STMDB	SP!, {R0-R12, LR}

		BL	c_irq_handler

		LDMIA	SP!, {R0-R12, PC}^

HandleReset:
		@ retrive image offset (load address - link address)
		LDR	R0, __link_addr
		ADR	R9, __load_addr
		SUB	R9, R9, R0

		@ Enter User Mode and set its Stack Pointer
		MSR	CPSR_c, #XPSR_Mode_System | XPSR_F_FIQ | XPSR_F_IRQ
		ldr_fix R0, StackUsr
		MOV	SP, R0

		MSR	CPSR_c, #XPSR_Mode_IRQ | XPSR_F_FIQ | XPSR_F_IRQ
		ldr_fix	R0, StackIsr
		MOV	SP, R0

		MSR	CPSR_c, #XPSR_Mode_Abort | XPSR_F_FIQ | XPSR_F_IRQ
		ldr_fix	R0, StackAbt
		MOV	SP, R0

		MSR	CPSR_c, #XPSR_Mode_Undefined | XPSR_F_FIQ | XPSR_F_IRQ
		ldr_fix	R0, StackUnd
		MOV	SP, R0

		MSR	CPSR_c, #XPSR_Mode_System | XPSR_F_FIQ | XPSR_F_IRQ

		@ Set the IVT to high memory, leave MMU & caches disabled
		MRC	p15, #0, r0, c1, c0, #0
		BIC	r0, r0, #0x00000300
		BIC	r0, r0, #0x00000087
		ORR	r0, r0, #0x00000002
		ORR	r0, r0, #0x00003000
		MCR	p15, #0, r0, c1, c0, #0
		NOP

		@ fix vector jump address
		MOV	R0, R9
		ldr_fix	R1, __vectors_jump
		ldr_fix R2, __vectors_end
		BL	__reloc_got

		@ copy vectors to high memory
		LDR	R0, =ARMlocalRAM_BASE
		ldr_fix	R1, __vectors_start
		ldr_fix	R2, __vectors_end
		BL	__copy_mem

		@ Clear BSS area
		.extern	__bss_start
		.extern	__bss_end
		MOV	R0, #0
		ldr_fix R1, __bss_start
		ldr_fix R2, __bss_end
__bss_clear_loop:
		STR	R0, [R1], #4
		CMP	R1, R2
		BLO	__bss_clear_loop

		.extern	arm_intr_disable
		BL	arm_intr_disable

		ldr_fix SL, __load_addr

		@ relocation got to untranslated address
		.global	__got_start
		.global	__got_end
		MOV	R0, R9
		ldr_fix	R1, __got_start
		ldr_fix R2, __got_end
		BL	__reloc_got

		.extern	low_level_init
		BL	low_level_init

		@ Call to main entry point
		.extern	main
		bl	main

_loop:
		B	_loop

		.global get_exec_base
get_exec_base:
		MOV	R0, SL
		MOV	PC, LR

		@ Add every element in [r1,r2) with r0
		.global	__reloc_got
__reloc_got:
		CMP	R1, R2
		MOVHS	PC, LR
__reloc_got_1:
		LDR	R4, [R1]
		ADD	R4, R4, R0
		STR	R4, [R1], #4
		CMP	R1, R2
		BLO	__reloc_got_1
		MOV	PC, LR

		@ copy memory from [r1, r2) to [r0, r0 + r2 - r1)
		.global __copy_mem
__copy_mem:
		CMP	R1, R2
		MOVHS	PC, LR
__copy_mem_1:
		LDR	R3, [R1], #4
		STR	R3, [R0], #4
		CMP	R1, R2
		BLO	__copy_mem_1
		MOV	PC, LR


__link_addr:
		.long	__load_addr
		.extern	__got_size
		.long	__got_size
		.ltorg

		.section .stack, "w"
		.balign	0x10
StackMem:
		.SPACE	USR_Stack_Size
StackUsr:
		.SPACE	ISR_Stack_Size
StackIsr:
		.SPACE	ABT_Stack_Size
StackAbt:
		.SPACE	UND_Stack_Size
StackUnd:
		.end
