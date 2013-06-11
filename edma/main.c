// tary, 14:00 2013/6/11
#include "am18x_lib.h"
#include "arm920t.h"
#include "systick.h"
#include "auxlib.h"

const uint32_t f_osc = F_OSCIN;

#define DMA_NR		EDMA0

static char src[] = {"0123456789ABCDEF"};
static char dst[sizeof src] = {0};

static pa_conf_t pa_conf[1] = {
{
	(uint32_t)&src,
	(uint32_t)&dst,

	sizeof src,
	1,

	1,
	LINK_NULL,

	1,
	1,

	0,
	0,

	0,
	0,		// priv_id
	0,
	{0,},

	FLAG_SYNCTYPE_A | FLAG_TRANS_INTR |
	FLAG_LAST_PAENTRY | FLAG_TCC_NORMAL,
}
};

static edma_conf_t edma_conf[1] = {
{
	CHANNEL(0),
	REGION_0,
	EDMA_Q0,
	DMA_MANUALLY_TRIGGERED,
	0,
	{0, 0},
	countof(pa_conf),
	pa_conf,
}
};

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for edma!\n";


	edma_conf->pa_conf = pa_conf;
	pa_conf->src = (uint32_t)&src;
	pa_conf->dst = (uint32_t)&dst;

	arm_intr_enable();
	systick_start();

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	debug_buf("src", src, sizeof src);
	printk("\nbefore transfer");
	debug_buf("dst", dst, sizeof dst);

	psc_state_transition(PSC_EDMA3_0_C0, PSC_STATE_ENABLE);
	psc_state_transition(PSC_EDMA3_0_T0, PSC_STATE_ENABLE);

	edma_init(DMA_NR, edma_conf);
	edma_param(DMA_NR, edma_conf);
	edma_interrupt(DMA_NR, edma_conf);

	#if 0
	printk("\n\n");
	printk("&param0 = 0x%.8X\n", &DMA_NR->CC.PAEntry);
	dump_regs_word("param0", 0x01C04000UL, sizeof(PaRAM_entry_t));
	#endif

	edma_transfer(DMA_NR, edma_conf);
	while (AM18X_OK != edma_is_completion(DMA_NR, edma_conf)) {
		printk(".");
	}

	#if 0
	printk("\n");
	dump_regs_word("CC0 Region0", (unsigned int)&DMA_NR->CC.Region0, sizeof DMA_NR->CC.Region0);
	#endif

	printk("\nafter  transfer");
	debug_buf("dst", dst, sizeof dst);

	return 0;
}
