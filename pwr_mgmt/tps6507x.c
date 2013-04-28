// tary, 1:49 2013/4/28
#include "am18x_lib.h"
#include "tps6507x.h"
#include "auxlib.h"
#include "i2c_inf.h"

// 1015640A_AM1808_SOM-M1_Schematic.pdf
// Page 7, PMIC
#define TPS6507X_BUS			I2C0

// slvs950f.pdf
// Device Address
#define TPS6507X_ADDR			0x48

#define TPS6507X_SPEED			350000	// 400K

// REGISTERS
typedef enum {
	TPS6507X_REG_NULL,		// 0x00
	TPS6507X_REG_PPATH1,
	TPS6507X_REG_INT,
	TPS6507X_REG_CHGCONFIG0,

	TPS6507X_REG_CHGCONFIG1,	// 0x04
	TPS6507X_REG_CHGCONFIG2,
	TPS6507X_REG_CHGCONFIG3,
#define ADCONFIG_SELECT_MASK		0x0FUL
#define ADCONFIG_SELECT_ac		0x06UL
#define ADCONFIG_SELECT_sys		0x07UL
	TPS6507X_REG_ADCONFIG,

	TPS6507X_REG_TSCMODE,		// 0x08
	TPS6507X_REG_ADRESULT_1,
	TPS6507X_REG_ADRESULT_2,
	TPS6507X_REG_PGOOD,

	TPS6507X_REG_PGOODMASK,		// 0x0C
	TPS6507X_REG_CON_CTRL1,
	TPS6507X_REG_CON_CTRL2,
	TPS6507X_REG_CON_CTRL3,

	TPS6507X_REG_DEFDCDC1,		// 0x10
	TPS6507X_REG_DEFDCDC2_LOW,
	TPS6507X_REG_DEFDCDC2_HIGH,
	TPS6507X_REG_DEFDCDC3_LOW,

	TPS6507X_REG_DEFDCDC3_HIGH,	// 0x14
	TPS6507X_REG_DEFSLEW,
	TPS6507X_REG_LDO_CTRL1,
	TPS6507X_REG_DEFLDO2,

	TPS6507X_REG_WLED_CTRL1,	// 0x18
	TPS6507X_REG_WLED_CTRL2,
	TPS6507X_REG_CNT,
} TPS6507X_reg_t;

enum {
	BIT_DEF(ADCONFIG,7,Enable,no,yes),
	BIT_DEF(ADCONFIG,6,Start,no,yes),
	BIT_DEF(ADCONFIG,5,End,no,yes),
	BIT_DEF(ADCONFIG,4,Vref,disable,enable),
};

static inline int tps6507x_reg_write(uint8_t reg, uint8_t val) {
	uint8_t bytes[2];

	bytes[0] = reg;
	bytes[1] = val;

	i2c_write(TPS6507X_BUS, TPS6507X_ADDR, bytes, sizeof bytes);

	return 0;
}

static inline int tps6507x_reg_read(uint8_t reg) {
	uint8_t bytes[1];

	bytes[0] = reg;
	i2c_write(TPS6507X_BUS, TPS6507X_ADDR, bytes, 1);
	i2c_read(TPS6507X_BUS, TPS6507X_ADDR, bytes, sizeof bytes);

	return bytes[0];
}

int tps6507x_conf(void) {
	int i;

	i2c_init(TPS6507X_BUS, TPS6507X_SPEED);

	for (i = 1; i < TPS6507X_REG_CNT ; i++) {
		printk("[0x%.2X] = 0x%.2X\n", i, tps6507x_reg_read(i));
	}
	return 0;
}

int tps6507x_get_adc(int is_ac) {
	uint16_t r;
	uint32_t msk;
	uint8_t v;

	// Set Bit AD ENABLE = 1 to provide power to the ADC
	msk = ADCONFIG_Enable_MASK;
	v = tps6507x_reg_read(TPS6507X_REG_ADCONFIG);
	v = FIELD_SET(v, msk, ADCONFIG_Enable_yes);
	tps6507x_reg_write(TPS6507X_REG_ADCONFIG, v);

	// Set input select for the ADC in register ADCONFIG to 011X
	v = tps6507x_reg_read(TPS6507X_REG_ADCONFIG);
	msk = ADCONFIG_SELECT_MASK;
	if (is_ac) {
		v = FIELD_SET(v, msk, ADCONFIG_SELECT_ac);
	} else {
		v = FIELD_SET(v, msk, ADCONFIG_SELECT_sys);
	}
	tps6507x_reg_write(TPS6507X_REG_ADCONFIG, v);

	// Start a conversion by setting CONVERSION START = 1;
	// wait until END OF CONVERSION = 1
	msk = ADCONFIG_Start_MASK;
	v = tps6507x_reg_read(TPS6507X_REG_ADCONFIG);
	v = FIELD_SET(v, msk, ADCONFIG_Start_yes);
	tps6507x_reg_write(TPS6507X_REG_ADCONFIG, v);

	msk = ADCONFIG_End_MASK;
	do {
		v = tps6507x_reg_read(TPS6507X_REG_ADCONFIG);
	} while (FIELD_GET(v, msk) != ADCONFIG_End_yes);

	// Read register ADRESULT_1 and ADRESULT_2
	r = tps6507x_reg_read(TPS6507X_REG_ADRESULT_1);
	v = tps6507x_reg_read(TPS6507X_REG_ADRESULT_2);
	r = __field_xset(r, 0x0300UL, v);

	return r;
}

int tps6507x_read(void) {
	uint8_t v;

	v = tps6507x_reg_read(TPS6507X_REG_PPATH1);
	return v;
}

int tps6507x_write(uint8_t val) {
	tps6507x_reg_write(TPS6507X_REG_PPATH1, val);
	return 0;
}
