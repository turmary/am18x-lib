// tary, 22:38 2013/6/5
#include "am18x_edma.h"

am18x_rt pru_load(PRU_con_t* pcon, const uint32_t* inst, uint32_t count) {
	uint32_t* pram;
	int i;

	pram = (uint32_t*)PRU_InstRAM0_BASE;
	if (pcon == PRU1) {
		pram = (uint32_t*)PRU_InstRAM1_BASE;
	}

	if (count * sizeof(uint32_t) > PRU_InstRAM0_SIZE) {
		count = PRU_InstRAM0_SIZE / sizeof(uint32_t);
	}

	for (i = 0; i < count; i++) {
		pram[i] = inst[i];
	}
	return AM18X_OK;
}

