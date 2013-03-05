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
		stat = state_kv[v].val;
		printk("[%2d] %-20s =[%2d] %s\n", psc_kv[i].key, psc_kv[i].val, v, stat);
	}

	return 0;
}
