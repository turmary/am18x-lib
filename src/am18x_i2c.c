// tary, 22:02 2013/3/13
#include "am18x_i2c.h"

// 22.2.2 Clock Generation
#define PrescaledModuleClockLow			(6700000UL)
#define PrescaledModuleClockHigh		(13300000UL)

// static inline
uint32_t i2c_input_clock_frequency(I2C_con_t* icon) {
	// from PLL0.AUXCLK
	// 6.3.7 I/O Domains
	// They are fed the AUXCLK directly from the oscillator input
	if (icon == I2C0) {
		return F_OSCIN;
	}
	// from PLL0.SYSCLK4
	return F_OSCIN / 4UL;
}

uint32_t i2c_get_serial_clock(I2C_con_t* icon) {
	uint32_t freq, scale_freq, ipsc, d, divider;

	freq = i2c_input_clock_frequency(icon);

	ipsc = FIELD_XGET(icon->ICPSC, ICPSC_IPSC_MASK);

	if (ipsc == 0) {
		d = 7;
	} else if (ipsc == 1) {
		d = 6;
	} else {
		d = 5;
	}

	divider = (d << 1);
	divider += FIELD_XGET(icon->ICCLKL, ICCLKL_MASK);
	divider += FIELD_XGET(icon->ICCLKH, ICCLKH_MASK);

	scale_freq = freq / (ipsc + 1);

	return scale_freq / divider;
}

am18x_rt i2c_set_serial_clock(I2C_con_t* icon, uint32_t freq) {
	uint32_t msk, ipsc, d, scale_freq;

	if (icon == I2C0) {
		ipsc = 0;
	} else {
		ipsc = 1;
	}

	scale_freq = i2c_input_clock_frequency(icon) / (ipsc + 1);

	msk = ICMDR_IRS_MASK;
	icon->ICMDR = FIELD_SET(icon->ICMDR, msk, ICMDR_IRS_reset);

	icon->ICPSC = FIELD_SET(0, ICPSC_IPSC_MASK, ICPSC_IPSC_VAL(ipsc));

	if (ipsc == 0) {
		d = 7;
	} else if (ipsc == 1) {
		d = 6;
	} else {
		d = 5;
	}

	// 22.2.2 Clock Generation
	// I2C serial clock frequency = prescaled module clock frequency
	//                              / ( ICCL + d ) + ( ICCH + d )
	icon->ICCLKL = scale_freq / (freq * 2) - d;
	icon->ICCLKH = icon->ICCLKL;

	icon->ICMDR = FIELD_SET(icon->ICMDR, msk, ICMDR_IRS_none);

	return AM18X_TRUE;
}

am18x_rt i2c_conf(I2C_con_t* icon, i2c_conf_t* conf) {
	i2c_set_serial_clock(icon, conf->freq);

	return AM18X_TRUE;
}
