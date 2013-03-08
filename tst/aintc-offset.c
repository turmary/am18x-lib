// tary, 21:40 2013/3/8
#include <stdio.h>
#include <stddef.h>
#include "am18x_lib.h"

#define KV(x)		{ offsetof(AINTC_con_t, x), #x }
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

int main(int argc, char* argv[]) {
	const char* title = "\nAINTC_con_t members offset test program!\n";
	int i;

	printf(title);

	for (i = 0; i < countof(aintc_kv); i++) {
		aintc_kv[i].offset += 0xFFFEE000UL;
	}

	for (i = 0; i < countof(aintc_kv); i++) {
		printf("[%2d] %-20s =[0x%.8X]\n", i, aintc_kv[i].name, aintc_kv[i].offset);
	}

	return 0;
}
