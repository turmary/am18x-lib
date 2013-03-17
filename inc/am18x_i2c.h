// tary, 22:00 2013/3/13

#ifndef __AM18X_I2C_H__
#define __AM18X_I2C_H__

#include "am18x_map.h"

typedef enum {
	I2C_BITMODE_7BIT,
	I2C_BITMODE_10BIT,
} i2c_bitmode_t;

typedef enum {
	I2C_,
} i2c_;

typedef struct {
	uint32_t	freq;
	uint8_t		bitmode;
} i2c_conf_t;

#endif//__AM18X_I2C_H__
