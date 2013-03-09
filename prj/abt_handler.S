// tary, 18:51 2011/8/6
#include "arm920t.h"

	.text
	.arm

.global HandlePrefetchAbort
	@	LR_abt	= PC + 4 (arm or thumb)
	@		PC is address of instruction 
	@		that had the Prefetch Abort
	@	return instruction SUBS PC, R14_abt, #4
	@
	@	now in Abort Mode
	@	R13 = SP = SP_abt
	@	R14 = LR = LR_abt
	@	SPSR = SPSR_abt = CPSR(saved)
	.func	pabt
HandlePrefetchAbort:
	PUSH	{R0, R1, V1-V3, LR}

	MRS	V1, SPSR
	ANDS	V3, V1, #XPSR_F_Thumb
	LDREQ	R1, =__arm_mode_fmt
	SUBEQ	V2, LR, #4
	LDRNE	R1, =__thumb_mode_fmt
	SUBNE	V2, LR, #4
	ADD	R1, R1, SL

	LDR	V1, =printk
	ADD	V1, V1, SL

	LDR	R0, =__pabt_fmt
	ADD	R0, R0, SL
	MOV	LR, PC
	BX	V1

	LDR	R0, =__abt_pc_fmt
	ADD	R0, R0, SL
	MOV	R1, V2
	MOV	LR, PC
	BX	V1

	LDR	R0, =__new_line__
	ADD	R0, R0, SL
2:
	MOV	LR, PC
	BX	V1
	POP	{R0, R1, V1-V3, LR}
	@SUBS	PC, LR, #4
__pabt_loop:
	B	__pabt_loop
	.endfunc

@.global HandleDataAbort
.weak HandleDataAbort
	@	LR_abt	= PC + 8 (arm or thumb)
	@		PC is address of instruction 
	@		that had the Data Abort
	@	return instruction SUBS PC, R14_abt, #8
	@
	@	now in Abort Mode
	@	R13 = SP = SP_abt
	@	R14 = LR = LR_abt
	@	SPSR = SPSR_abt = CPSR(saved)
	.func	dabt
HandleDataAbort:
	PUSH	{R0, R1, V1-V3, LR}

	MRS	V1, SPSR
	ANDS	V3, V1, #XPSR_F_Thumb
	LDREQ	R1, =__arm_mode_fmt
	SUBEQ	V2, LR, #8
	LDRNE	R1, =__thumb_mode_fmt
	SUBNE	V2, LR, #8
	ADD	R1, R1, SL

	LDR	V1, =printk
	ADD	V1, V1, SL

	LDR	R0, =__dabt_fmt
	ADD	R0, R0, SL
	MOV	LR, PC
	BX	V1

	LDR	R0, =__abt_pc_fmt
	ADD	R0, R0, SL
	MOV	R1, V2
	MOV	LR, PC
	BX	V1

	MOVS	V3, V3
	BNE	1f
0:
	LDR	R0, =__abt_arm_instruction
	ADD	R0, R0, SL
	LDR	R1, [V2, #0]
	B	2f
1:
	LDR	R0, =__abt_thumb_instruction
	ADD	R0, R0, SL
	LDRH	R1, [V2, #0]
	B	2f
2:
	MOV	LR, PC
	BX	V1

	BL	arm_read_cp15_fault_address
	MOV	R1, R0
	LDR	R0, =__dabt_addr_fmt
	ADD	R0, R0, SL
	MOV	LR, PC
	BX	V1

	POP	{R0, R1, V1-V3, LR}
	@SUBS	PC, LR, #8
	SUBS	PC, LR, #4
__dabt_loop:
	B	__dabt_loop
	.endfunc

	.align	4
	.ltorg

__pabt_fmt:
	.string "\n****** Prefetch Abort --- %s mode ******\n"
__dabt_fmt:
	.string "\n****** Data Abort --- %s mode ******\n"
__dabt_addr_fmt:
	.string "\tAbort address = 0x%.8X\n"
__arm_mode_fmt:
	.string	"arm"
__thumb_mode_fmt:
	.string "thumb"
__abt_pc_fmt:
	.string "\tPC = 0x%.8X"
__abt_arm_instruction:
	.string " \t[PC] = 0x%.8X\n"
__abt_thumb_instruction:
	.string " \t[PC] = 0x%.4X\n"
__new_line__:
	.string "\n"

	.align	4
	.end
