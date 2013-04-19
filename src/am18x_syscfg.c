// tary, 13:15 2012/12/28
#include "am18x_syscfg.h"

am18x_rt syscfg_kick(am18x_bool lock) {
	uint32_t kick0, kick1;

	if (lock) {
		kick0 = KICK0R_LOCK;
		kick1 = KICK1R_LOCK;
	} else {
		kick0 = KICK0R_UNLOCK;
		kick1 = KICK1R_UNLOCK;
	}

	SYSCFG0->KICKxR[0] = kick0;
	SYSCFG0->KICKxR[1] = kick1;

	return AM18X_TRUE;
}

am18x_rt syscfg_pll(am18x_bool lock) {
	uint32_t cfg0, cfg3, msk;

	cfg0 = SYSCFG0->CFGCHIP0;
	cfg3 = SYSCFG0->CFGCHIP3;
	if (lock) {
		msk = CFGCHIP0_PLL_MASTER_LOCK_MASK;
		cfg0 = FIELD_SET(cfg0, msk, CFGCHIP0_PLL_MASTER_LOCK_yes);
		msk = CFGCHIP3_PLL1_MASTER_LOCK_MASK;
		cfg3 = FIELD_SET(cfg3, msk, CFGCHIP3_PLL1_MASTER_LOCK_yes);
	} else {
		msk = CFGCHIP0_PLL_MASTER_LOCK_MASK;
		cfg0 = FIELD_SET(cfg0, msk, CFGCHIP0_PLL_MASTER_LOCK_no);
		msk = CFGCHIP3_PLL1_MASTER_LOCK_MASK;
		cfg3 = FIELD_SET(cfg3, msk, CFGCHIP3_PLL1_MASTER_LOCK_no);
	}

	SYSCFG0->CFGCHIP0 = cfg0;
	SYSCFG0->CFGCHIP3 = cfg3;

	return AM18X_TRUE;
}

// pos = [0,4,8,12,16,20,24,28]
// val = [0..15]
am18x_rt syscfg_pinmux(uint32_t mux, uint32_t pos, uint32_t val) {
	uint32_t reg;

	if (mux >= 20 || pos >= 32 || pos % 4 != 0 || val >= 8) {
		return AM18X_FALSE;
	}

	reg = SYSCFG0->PINMUXx[mux];
	SYSCFG0->PINMUXx[mux] = __field_xset(reg, (0xFUL << pos), val);

	return AM18X_TRUE;
}
