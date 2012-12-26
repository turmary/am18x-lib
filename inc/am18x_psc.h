// tary, 0:27 2012/12/27

#ifndef __AM18X_PSC_H__
#define __AM18X_PSC_H__

#include "am18x_map.h"

typedef enum {
	PSC_STATE_SW_RST_DISABLE,
	PSC_STATE_SYNC_RESET,
	PSC_STATE_DISABLE,
	PSC_STATE_ENABLE,
	PSC_STATE_IN_TRANSITION,
} psc_state_t;

am18x_rt psc_state_transition(psc_module_t module, psc_state_t state);
psc_state_t psc_get_state(psc_module_t module);

#endif//__AM18X_PSC_H__
