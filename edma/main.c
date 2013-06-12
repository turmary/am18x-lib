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
	.src		= (uint32_t)&src,
	.dst		= (uint32_t)&dst,

	.a_cnt		= sizeof src,
	.b_cnt		= 1,

	.c_cnt		= 1,
	.link		= LINK_NULL,

	.src_b_idx	= 1,
	.dst_b_idx	= 1,

	.src_c_idx	= 0,
	.dst_c_idx	= 0,

	.tcc		= 0,
	.priv_id	= 0,		// priv_id
	.index		= 0,
	// .reserved0	= {0,},

	.flags		= FLAG_SYNCTYPE_AB | FLAG_TRANS_INTR |
			FLAG_LAST_PAENTRY | FLAG_TCC_NORMAL,
}
};

static edma_conf_t edma_conf[1] = {
{
	.channel	= CHANNEL(0),
	.region		= REGION_0,
	.queue		= EDMA_Q0,
	.trigger	= DMA_MANUALLY_TRIGGERED,
	.tr_word	= 0,
	// .reserved0	= {0},
	.pa_cnt		= countof(pa_conf),
	.pa_conf	= pa_conf,
}
};

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for edma!\n";
	char* status[16];
	uint32_t completed;
	int i;

	arm_intr_enable();
	systick_start();

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	debug_buf("src", src, sizeof src);
	printk("\nbefore transfer");
	debug_buf("dst", dst, sizeof dst);

	psc_state_transition(PSC_EDMA3_0_C0, PSC_STATE_ENABLE);
	psc_state_transition(PSC_EDMA3_0_T0, PSC_STATE_ENABLE);

	*(unsigned*)&edma_conf->pa_conf += get_exec_base();
	pa_conf->src += get_exec_base();
	pa_conf->dst += get_exec_base();

	edma_init(DMA_NR, edma_conf);
	edma_param(DMA_NR, edma_conf);
	edma_interrupt(DMA_NR, edma_conf);

	#if 0
	printk("&param0 = 0x%.8X\n", &DMA_NR->CC.PAEntry);
	dump_regs_word("param0", (uint32_t)&DMA_NR->CC.PAEntry, sizeof(PaRAM_entry_t));
	#endif

	edma_transfer(DMA_NR, edma_conf);

	if (AM18X_OK == edma_status(DMA_NR, status, &completed)) {
		printk("completed %d requests\n", completed);
		for (i = 0; status[i] != NULL; i++) {
			printk("S%d %s\n", i, status[i]);
		}
	}

	while (AM18X_OK != edma_completed(DMA_NR, edma_conf)) {
		printk(".");
	}

	#if 0
	dump_regs_word("CC0 Region0", (uint32_t)&DMA_NR->CC.Region0, sizeof(EDMA3CC_rgn_t));
	#endif

	printk("\nafter  transfer");
	debug_buf("dst", dst, sizeof dst);

	return 0;
}
