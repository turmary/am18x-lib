// tary, 1:04 2012/12/23
#include "am18x_lib.h"

extern void systick_isr(void);
/*
static none_arg_handler_t isr_vector[] = {
	NULL,
	NULL,
	NULL,
	NULL,

	NULL,
	NULL,
	NULL,
	NULL,

	NULL,
	NULL,
	NULL,
	NULL,

	NULL,
	NULL,
	systick_isr,
	NULL,

	NULL,
	NULL,
	NULL,
	NULL,

	NULL,
	NULL,
	NULL,
	NULL,

	NULL,
	NULL,
	NULL,
	NULL,

	NULL,
	NULL,
	NULL,
	NULL,
};

int isr_set_hander(int intr_nr, none_arg_handler_t handle) {
	if (intr_nr >= countof(isr_vector)) {
		return -1;
	}
	isr_vector[intr_nr] = handle;
	return 0;
}

int c_irq_handler(void) {
	int32_t irq_nr = intr_get_active(INTRCON);

	if (irq_nr == INTR_INVALID_ACTIVE) {
		return -1;
	}
	if (isr_vector[irq_nr] != NULL) {
		(*isr_vector[irq_nr])();
	}

	intr_clear(INTRCON, irq_nr);

	return 0;
}
*/
