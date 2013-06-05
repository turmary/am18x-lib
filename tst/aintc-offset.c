// tary, 21:40 2013/3/8
#include <stdio.h>
#include <stddef.h>
#include "am18x_lib.h"

#define KV(x)		{ offsetof(AINTC_con_t, x), #x }
#define KVS(x)		{ sizeof (x), #x }
#define KVX(s,x)	{ offsetof(s,x), #x }
typedef struct {
	int	offset;
	char*	name;
} kv_t;

kv_t aintc_kv[] = {
	KV(REVID),
	KV(CR),
	KV(GER),
	KV(GNLR),
	KV(SIxR),
	KV(EIxR),
	KV(HIEIxR),
	KV(VBR),
	KV(VSR),
	KV(VNR),
	KV(GPIR),
	KV(GPVR),
	KV(SRSRx),
	KV(SECRx),
	KV(ESRx),
	KV(ECRx),
	KV(CMRx),
	KV(HIPIRx),
	KV(HINLRx),
	KV(HIER),
	KV(HIPVRx),
};

kv_t edma_kv[] = {
	KVS(PaRAM_entry_t),
	KVS(EDMA3CC_CH_t),
	KVS(EDMA3CC_con_t),
	KVS(EDMA3TC_fifo_t),
	KVS(EDMA3TC_con_t),
};

kv_t edma_kvx[] = {
	KVX(EDMA_con_t,CC),
	KVX(EDMA_con_t,TC),
	KVX(EDMA_con_t,TC[0]),
	KVX(EDMA_con_t,TC[1]),
};

int main(int argc, char* argv[]) {
	const char* title = "\nAINTC_con_t members offset test program!\n";
	int i;

	printf(title);

	for (i = 0; i < countof(aintc_kv); i++) {
		aintc_kv[i].offset += 0xFFFEE000UL;
	}

	for (i = 0; i < countof(edma_kvx); i++) {
		edma_kvx[i].offset += 0x01C00000L;
	}

	for (i = 0; i < countof(aintc_kv); i++) {
		printf("[%2d] %-20s =[0x%.8X]\n", i, aintc_kv[i].name, aintc_kv[i].offset);
	}

	for (i = 0; i < countof(edma_kv); i++) {
		printf("[%2d] %-20s =[0x%.8X]\n", i, edma_kv[i].name, edma_kv[i].offset);
	}

	for (i = 0; i < countof(edma_kvx); i++) {
		printf("[%2d] %-20s =[0x%.8X]\n", i, edma_kvx[i].name, edma_kvx[i].offset);
	}

	return 0;
}
