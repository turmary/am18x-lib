// tary, 0:18 2013/6/6

#ifndef __AM18X_EDMA_H__
#define __AM18X_EDMA_H__

#include "am18x_map.h"

#define CHANEL_X_MAX			(0x1FUL)
#define CHANEL(x)			((x) & CHANEL_X_MAX)
#define QCHANEL_X_MAX			(0x7UL)
#define QCHANEL(x)			((x) & QCHANEL_X_MAX)
#define TR_WORD(addr)			(((addr) & 0x1FUL) >> 2)

typedef enum {
	REGION_0,
	REGION_1,
	REGION_GLOBAL,
} edma_region_t;

typedef enum {
	EDMA_Q0,
	EDMA_Q1,	// EDMA1 only
} emda_queue_t;

typedef enum {
	DMA_EVENT_TRIGGERED,
	DMA_MANUALLY_TRIGGERED,
	// DMA_CHAIN_TRIGGERED,
	QDMA_AUTO_TRIGGERED,
	// QDMA_LINK_TRIGGERED,
} edma_trigger_t;

typedef enum {
	// each sync event initiates the transfer of
	// one array (ACNT bytes) only
	FLAG_SYNCTYPE_A = 0,
	// each sync event initiates the transfer of
	// one frame (BCNT arrays of ACNT bytes)
	FLAG_SYNCTYPE_AB = BIT(0),
	FLAG_TRANS_EVT = BIT(1),
	FLAG_TRANS_INTR = BIT(2),
	FLAG_LAST_PAENTRY = BIT(3),
	FLAG_TCC_NORMAL = 0,
	FLAG_TCC_EARLY = BIT(4),
} conf_flags_t;

typedef struct {
	uint32_t	src;		// source start address
	uint32_t	dst;		// destination start address

	uint16_t	a_cnt;		// (one array has a_cnt bytes)
	uint16_t	b_cnt;		// (one frame has b_cnt arrays)

	uint16_t	c_cnt;		// (one transfer has c_cnt frames)
#define LINK_NULL			0xFFFFUL
	uint16_t	link;		// linked as pa[n].link = &param[pa[n+1].index]

	uint16_t	src_b_idx;	// dist(arrrys[n+1], array[n]) in a frame
	uint16_t	dst_b_idx;	//

	uint16_t	src_c_idx;	// A-sync for  dist(frames[n + 1].0, frames[n].last)
	uint16_t	dst_c_idx;	// AB-sync for dist(frames[n + 1].0, frames[n].0)

	uint8_t		tcc;		// chain channel or interrupt bit index #
	uint8_t		priv_id;
	uint8_t		index;		// index of PaRAM set
	uint8_t		reserved0[1];	// QCHANNEL --- customized by user
					// CHANNEL  --- first one identical with edma_conf_t.channel
					//              other ones can be chained as pa[n].tcc = pa[n + 1].index
	uint32_t	flags;
} pa_conf_t;

typedef struct {
	uint8_t		channel;	// CHANEL(n) or QCHANEL(n)
	uint8_t		region;		// edma_region_t
	uint8_t		queue;		// emda_queue_t
	uint8_t		trigger;	// edma_trigger_t

	uint8_t		tr_word;	// QCHANNEL only
	uint8_t		reserved0[2];
	uint8_t		pa_cnt;		// elements count of pa_conf
	pa_conf_t*	pa_conf;	// param sets as chained or linked
} edma_conf_t;

am18x_rt edma_init(EDMA_con_t* econ, const edma_conf_t* conf);
am18x_rt edma_param(EDMA_con_t* econ, const edma_conf_t* conf);
am18x_rt edma_interrupt(EDMA_con_t* econ, const edma_conf_t* conf);
am18x_rt edma_transfer(EDMA_con_t* econ, const edma_conf_t* conf);
am18x_rt edma_wait_completion(EDMA_con_t* econ);

#endif//__AM18X_EDMA_H__
