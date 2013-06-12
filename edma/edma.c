// tary, 17:03 2013/6/12
#include "am18x_lib.h"
#include "auxlib.h"
#include "edma.h"

#define DMA_NR		EDMA0

static char src[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ01234"};
static char dst[sizeof src * 2] = {0};

static pa_conf_t pa_conf[2] = {
{
	// .src		= (uint32_t)&src,
	// .dst		= (uint32_t)&dst,

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
			FLAG_LAST_PAENTRY | FLAG_TCC_EARLY,
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
	// .pa_cnt	= countof(pa_conf),
	// .pa_conf	= pa_conf,
}
};

static int edma_transfer_inner(edma_conf_t* edma_conf) {
	#define RETRY_COUNT		200
	edma_stat_t dma_stat[1];
	int i;

	edma_init(DMA_NR, edma_conf);
	edma_param(DMA_NR, edma_conf);
	edma_interrupt(DMA_NR, edma_conf);

	#if 0
	dump_regs_word("param0", (uint32_t)&DMA_NR->CC.PAEntry[pa_conf[0].index], sizeof(PaRAM_entry_t));
	if (edma_conf->pa_cnt > 1) {
	dump_regs_word("param1", (uint32_t)&DMA_NR->CC.PAEntry[pa_conf[1].index], sizeof(PaRAM_entry_t));
	}
	#endif

	edma_transfer(DMA_NR, edma_conf);

	if (AM18X_OK == edma_status(DMA_NR, dma_stat)) {
		for (i = 0; dma_stat->status[i] != NULL; i++) {
			printk("S%d %s\n", i, dma_stat->status[i]);
		}
		printk("completed requests # = %d\n", dma_stat->comp_actv);
		printk("queue0 events      # = %d\n", dma_stat->queue_evts[0]);
		printk("queue1 events      # = %d\n", dma_stat->queue_evts[1]);
	}

	for (i = 0; i < RETRY_COUNT && AM18X_OK != edma_completed(DMA_NR, edma_conf); i++) {
		printk(".");
	}
	if (i != 0) {
		printk("\n");
	}

	#if 0
	dump_regs_word("Region0", (uint32_t)&DMA_NR->CC.Region0, sizeof(EDMA3CC_rgn_t));
	dump_regs_word("param0", (uint32_t)&DMA_NR->CC.PAEntry[pa_conf[0].index], sizeof(PaRAM_entry_t));
	if (edma_conf->pa_cnt > 1) {
	dump_regs_word("param1", (uint32_t)&DMA_NR->CC.PAEntry[pa_conf[1].index], sizeof(PaRAM_entry_t));
	}
	#endif

	if (i >= RETRY_COUNT) {
		return -1;
	}

	return 0;
}

int edma_block_move_example(void) {
	printk("\n\n\n###### %s() ######\n", __func__);

	debug_buf("src", src, sizeof src);
	printk("\nbefore transfer");
	memset(dst, '\0', sizeof dst);
	debug_buf("dst", dst, sizeof dst);

	pa_conf->src		= (uint32_t)src;
	pa_conf->dst		= (uint32_t)dst;
	edma_conf->pa_conf	= pa_conf;
	edma_conf->pa_cnt	= 1;
	edma_conf->channel	= pa_conf[0].index;

	edma_transfer_inner(edma_conf);

	printk("\nafter  transfer");
	debug_buf("dst", dst, sizeof dst);
	return 0;
}

int edma_linked_transfer_example(void) {
	printk("\n\n\n###### %s() ######\n", __func__);

	debug_buf("src", src, sizeof src);
	printk("\nbefore transfer");
	memset(dst, '\0', sizeof dst);
	debug_buf("dst", dst, sizeof dst);

	pa_conf[1]		= pa_conf[0];		// *** important ***
	pa_conf[1].index	= 127;
	pa_conf[1].src		= (uint32_t)src + 1;
	pa_conf[1].dst		= (uint32_t)dst + sizeof src;
	pa_conf[1].a_cnt	= 1;
	pa_conf[1].b_cnt	= sizeof src / 2;
	pa_conf[1].src_b_idx	= 2;
	pa_conf[1].dst_b_idx	= 1;
	pa_conf[1].tcc		= 1;
	pa_conf[1].link		= LINK_NULL;
	pa_conf[1].flags	= FLAG_SYNCTYPE_AB | FLAG_TRANS_INTR |
				FLAG_LAST_PAENTRY | FLAG_TCC_EARLY,

	pa_conf[0].index	= 0;
	pa_conf[0].src		= (uint32_t)src + 0;
	pa_conf[0].dst		= (uint32_t)dst + 0;
	pa_conf[0].a_cnt	= 1;
	pa_conf[0].b_cnt	= sizeof src / 2;
	pa_conf[0].src_b_idx	= 2;
	pa_conf[0].dst_b_idx	= 1;
	pa_conf[0].tcc		= 0;
	pa_conf[0].link		= LINK_NEXT(pa_conf[1].index);
	pa_conf[0].flags	= FLAG_SYNCTYPE_AB | FLAG_TRANS_INTR | FLAG_TCC_EARLY |
				FLAG_TRANS_EVT /* event to trigger pa_conf[1] */;

	edma_conf->pa_conf	= pa_conf;
	edma_conf->pa_cnt	= 2;
	edma_conf->channel	= pa_conf[0].index;

	edma_transfer_inner(edma_conf);

	printk("\nafter  transfer");
	debug_buf("dst", dst, sizeof dst);
	return 0;
}

int edma_transfer_channing_example(void) {
	printk("\n\n\n###### %s() ######\n", __func__);

	debug_buf("src", src, sizeof src);
	printk("\nbefore transfer");
	memset(dst, '\0', sizeof dst);
	debug_buf("dst", dst, sizeof dst);

	pa_conf[0].index	= 2;
	pa_conf[0].src		= (uint32_t)src + 0;
	pa_conf[0].dst		= (uint32_t)dst + 0;
	pa_conf[0].a_cnt	= 1;
	pa_conf[0].b_cnt	= 2;
	pa_conf[0].c_cnt	= sizeof src / pa_conf[0].b_cnt / 2;
	pa_conf[0].src_b_idx	= 1;
	pa_conf[0].src_c_idx	= 2;
	pa_conf[0].dst_b_idx	= 1;
	pa_conf[0].dst_c_idx	= 2;
	pa_conf[0].tcc		= 3;	/* event to trigger pa_conf[1] */
	pa_conf[0].link		= LINK_NULL;
	pa_conf[0].flags	= FLAG_SYNCTYPE_AB | FLAG_TRANS_INTR | FLAG_TCC_EARLY |
				FLAG_TRANS_EVT;

	pa_conf[1]		= pa_conf[0];
	pa_conf[1].index	= 3;
	pa_conf[1].src		= (uint32_t)src + sizeof src / 2;
	pa_conf[1].dst		= (uint32_t)dst + sizeof src;
	pa_conf[1].tcc		= 2;	/* event to trigger pa_conf[0] */

	edma_conf->pa_conf	= pa_conf;
	edma_conf->pa_cnt	= 2;
	edma_conf->channel	= pa_conf[0].index;

	edma_transfer_inner(edma_conf);

	printk("\nafter  transfer");
	debug_buf("dst", dst, sizeof dst);
	return 0;
}
