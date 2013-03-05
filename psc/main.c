// tary, 21:37 2013/1/2
#include "am18x_lib.h"
#include "auxlib.h"

const uint32_t f_osc = F_OSCIN;

#define KV(x)		{ x, #x }
typedef struct {
	int key;
	char* val;
} kv_t;

kv_t psc_kv[] = {
	KV(PSC_EDMA3_0_C0),
	KV(PSC_EDMA3_0_T0),
	KV(PSC_EDMA3_0_T1),
	KV(PSC_EMIFA),
	KV(PSC_SPI0),
	KV(PSC_MMC_SD0),
	KV(PSC_ARM_INTC),
	KV(PSC_ARM_RAM_ROM),
	KV(PSC_RESERVED0),
	KV(PSC_UART0),
	KV(PSC_SCR0),
	KV(PSC_SCR1),
	KV(PSC_SCR2),
	KV(PSC_PRU),
	KV(PSC_ARM),
	KV(PSC_RESERVED1),
	KV(PSC_EDMA3_1_C0),
	KV(PSC_USB0),
	KV(PSC_USB1),
	KV(PSC_GPIO),
	KV(PSC_HPI),
	KV(PSC_EMAC),
	KV(PSC_DDR2),
	KV(PSC_MCASP0),
	KV(PSC_SATA),
	KV(PSC_VPIF),
	KV(PSC_SPI1),
	KV(PSC_I2C1),
	KV(PSC_UART1),
	KV(PSC_UART2),
	KV(PSC_MCBSP0),
	KV(PSC_MCBSP1),
	KV(PSC_LCDC),
	KV(PSC_EHRPWM),
	KV(PSC_MMC_SD1),
	KV(PSC_UPP),
	KV(PSC_ECAP),
	KV(PSC_EDMA3_1_T0),
	KV(PSC_RESERVED2),
	KV(PSC_RESERVED3),
	KV(PSC_SCR_F0),
	KV(PSC_SCR_F1),
	KV(PSC_SCR_F2),
	KV(PSC_SCR_F6),
	KV(PSC_SCR_F7),
	KV(PSC_SCR_F8),
	KV(PSC_BR_F7),
	KV(PSC_ON_CHIP_RAM),
};

kv_t state_kv[] = {
	KV(PSC_STATE_SW_RST_DISABLE),
	KV(PSC_STATE_SYNC_RESET),
	KV(PSC_STATE_DISABLE),
	KV(PSC_STATE_ENABLE),
	KV(PSC_STATE_IN_TRANSITION),
};

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for am1808 psc!\n";
	int i;

	printk(title);

	for (i = 0; i < countof(psc_kv); i++) {
		int v;
		char* stat;

		v = psc_get_state(psc_kv[i].key);
		stat = state_kv[v].val + get_exec_base();
		printk("[%2d] %-20s =[%2d] %s\n", psc_kv[i].key, psc_kv[i].val + get_exec_base(), v, stat);
	}
/*
     950:	e59f3050 	ldr	r3, [pc, #80]	; 9a8 <main+0x6c>	;r3 = 0x31c4
     954:	e79a6003 	ldr	r6, [sl, r3]				;r6 = 0x3000 = &psc_kv
     958:	e7d60004 	ldrb	r0, [r6, r4]				;r0 = psc_kv[i].key
     95c:	eb00003e 	bl	a5c <psc_get_state>			;r0 = psc_get_state(key)
		stat = state_kv[v].val;
     960:	e59f2044 	ldr	r2, [pc, #68]	; 9ac <main+0x70>	;r2 = 0x000031bc

	for (i = 0; i < countof(psc_kv); i++) {
		int v;
		char* stat;

		v = psc_get_state(psc_kv[i].key);
     964:	e0845006 	add	r5, r4, r6				;r5 = &psc_kv[i].key
		stat = state_kv[v].val;
     968:	e79a2002 	ldr	r2, [sl, r2]				;r2 = 0x3180 = &state_kv
     96c:	e0822180 	add	r2, r2, r0, lsl #3			;r2 = &state_kv[v]
		printk("[%2d] %-20s =[%2d] %s\n", psc_kv[i].key, psc_kv[i].val, v, stat);
     970:	e5922004 	ldr	r2, [r2, #4]				;r2 = stat = state_kv[v].val

	for (i = 0; i < countof(psc_kv); i++) {
		int v;
		char* stat;

		v = psc_get_state(psc_kv[i].key);
     974:	e1a03000 	mov	r3, r0					;r3 = v
		stat = state_kv[v].val;
		printk("[%2d] %-20s =[%2d] %s\n", psc_kv[i].key, psc_kv[i].val, v, stat);
     978:	e59f0030 	ldr	r0, [pc, #48]	; 9b0 <main+0x74>	;r0 = 0x21ac
     97c:	e58d2000 	str	r2, [sp]				;v4 = stat
     980:	e08f0000 	add	r0, pc, r0				;r0 = 0x2b34
     984:	e7941006 	ldr	r1, [r4, r6]				;r1 = psc_kv[i].key
     988:	e5952004 	ldr	r2, [r5, #4]				;r2 = psc_kv[i].val
     98c:	eb00019d 	bl	1008 <printk>
     990:	e2844008 	add	r4, r4, #8				;i++
	const char* title = "\nam18x library for am1808 psc!\n";
	int i;

	printk(title);

	for (i = 0; i < countof(psc_kv); i++) {
     994:	e3540d06 	cmp	r4, #384	; 0x180
     998:	1affffec 	bne	950 <main+0x14>
*/

	return 0;
}
