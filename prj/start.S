@tary, 22:42 2012/11/27
		.section .init, "ax"
		.arm

		.macro	ldr_fix, Rx, symbol
		LDR	\Rx, = \symbol
		ADD	\Rx, \Rx, R9
		.endm

		.global	_start
_start:
__load_addr:
		NOP
		MRS	r0, cpsr
		BIC	r0, r0, #0x1F       @ CLEAR MODES
		ORR	r0, r0, #0x13       @ SET SUPERVISOR mode
		ORR	r0, r0, #0xC0       @ Disable FIQ and IRQ
		MSR	cpsr_cxsf, r0
		NOP

		@ Set the IVT to low memory, leave MMU & caches disabled
		MRC	p15, #0, r0, c1, c0, #0
		BIC	r0, r0, #0x00002300
		BIC	r0, r0, #0x00000087
		ORR	r0, r0, #0x00000002
		ORR	r0, r0, #0x00001000
		MCR	p15, #0, r0, c1, c0, #0
		NOP

		@ retrive image offset (load address - link address)
		LDR	R0, __link_addr
		ADR	R9, __load_addr
		SUB	R9, R9, R0

		@ Setup the stack pointer
		LDR	r0, stack_top
		ADD	sp, r0, r9
		SUB	sp, sp, #4
		BIC	sp, sp, #7

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
		LDR	R4, [R1]
		ADD	R4, R4, R0
		STR	R4, [R1], #4
		CMP	R1, R2
		BLO	__reloc_got
		MOV	PC, LR

__link_addr:
		.long	__load_addr
		.extern	__got_size
		.long	__got_size

		.global	stack_top
stack_top:
		.long	__stack_top
		.ltorg

		.align	2
		.section .stack, "w"
		.space	0x4000
__stack_top:
		.end
