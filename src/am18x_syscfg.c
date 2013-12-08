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

	return AM18X_OK;
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

	return AM18X_OK;
}

am18x_rt syscfg_aync3(am18x_bool ispll0) {
	uint32_t msk, v;

	msk = CFGCHIP3_ASYNC3_CLKSRC_MASK;
	v = ispll0? CFGCHIP3_ASYNC3_CLKSRC_pll0: CFGCHIP3_ASYNC3_CLKSRC_pll1;
	SYSCFG0->CFGCHIP3 = FIELD_SET(SYSCFG0->CFGCHIP3, msk, v);

	return AM18X_OK;
}

// pos = [0,4,8,12,16,20,24,28]
// val = [0..15]
am18x_rt syscfg_pinmux(uint32_t mux, uint32_t pos, uint32_t val) {
	uint32_t reg;

	if (mux >= 20 || pos >= 32 || (pos & 0x3UL) != 0 || val >= 8) {
		return AM18X_ERR;
	}

	reg = SYSCFG0->PINMUXx[mux];
	SYSCFG0->PINMUXx[mux] = __field_xset(reg, (0xFUL << pos), val);

	return AM18X_OK;
}

int32_t syscfg_bootmode(void) {
	return __field_xget(SYSCFG0->BOOTCFG, BOOTCFG_BOOTMODE_MASK);
}

am18x_rt syscfg_vtpio_calibrate(void) {
	uint32_t reg, msk, v;

	reg = SYSCFG1->VTPIO_CTL;
	// a) Clear POWERDN bit in the VTPIO_CTL
	reg = FIELD_SET(reg, VTPIO_CTL_POWERDN_MASK, VTPIO_CTL_POWERDN_no);
	SYSCFG1->VTPIO_CTL = reg;

	// b) Clear LOCK bit in VTPIO_CTL
	reg = FIELD_SET(reg, VTPIO_CTL_LOCK_MASK, VTPIO_CTL_LOCK_no);
	SYSCFG1->VTPIO_CTL = reg;

	// c) Pulse CLKRZ bit in VTPIO_CTL
	msk = VTPIO_CTL_CLKRZ_MASK;
	reg = FIELD_SET(SYSCFG1->VTPIO_CTL, msk, VTPIO_CTL_CLKRZ_none);
	SYSCFG1->VTPIO_CTL = reg;
	reg = FIELD_SET(SYSCFG1->VTPIO_CTL, msk, VTPIO_CTL_CLKRZ_clear);
	SYSCFG1->VTPIO_CTL = reg;
	reg = FIELD_SET(SYSCFG1->VTPIO_CTL, msk, VTPIO_CTL_CLKRZ_none);
	SYSCFG1->VTPIO_CTL = reg;

	// d) Poll READY bit in VTPIO_CTL until it changes to 1
	do {
		reg = FIELD_GET(SYSCFG1->VTPIO_CTL, VTPIO_CTL_READY_MASK);
	} while (reg != VTPIO_CTL_READY_yes);

	// e) Set LOCK bit in VTPIO_CTL is locked
	// and dynamic calibration is disabled
	reg = SYSCFG1->VTPIO_CTL;
	reg = FIELD_SET(reg, VTPIO_CTL_LOCK_MASK, VTPIO_CTL_LOCK_yes);
	SYSCFG1->VTPIO_CTL = reg;

	// f) Set POWERDN bit in VTPIO_CTL to save power
	reg = FIELD_SET(reg, VTPIO_CTL_POWERDN_MASK, VTPIO_CTL_POWERDN_yes);
	SYSCFG1->VTPIO_CTL = reg;

	reg = FIELD_SET(reg, VTPIO_CTL_IOPWRDN_MASK, VTPIO_CTL_IOPWRDN_yes);
	SYSCFG1->VTPIO_CTL = reg;
	
	return AM18X_OK;
}

am18x_rt syscfg_ddr_slew(am18x_bool ddr2_not_mddr) {
	uint32_t reg, v;

	reg = SYSCFG1->DDR_SLEW;
	if (ddr2_not_mddr) {
		v = DDR_SLEW_CMOSEN_SSTL;
	} else {
		v = DDR_SLEW_CMOSEN_LVCMOS;
	}
	SYSCFG1->DDR_SLEW = FIELD_SET(reg, DDR_SLEW_CMOSEN_MASK, v);
	return AM18X_OK;
}
