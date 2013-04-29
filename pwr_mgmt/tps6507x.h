// tary, 2:11 2013/4/28
#ifndef __TPS6507X_H__
#define __TPS6507X_H__

#include "am18x_lib.h"

typedef enum {
	// adc && switch
	PWR_TYPE_AC,
	PWR_TYPE_USB,
	PWR_TYPE_SYS,

	// output && switch
	PWR_TYPE_DCDC1,
	PWR_TYPE_DCDC2,
	PWR_TYPE_DCDC3,
	PWR_TYPE_LDO1,
	PWR_TYPE_LDO2,

	PWR_TYPE_CNT,
} pwr_type_t;

int tps6507x_conf(void);
int tps6507x_dump_regs(void);
int tps6507x_get_adc(pwr_type_t pt);
// return uinit: milli volt
int tps6507x_get_output(pwr_type_t pt);
int tps6507x_power_switch(pwr_type_t pt, am18x_bool on_noff);

#endif//__TPS6507X_H__
