// tary, 20:48 2016/4/1

#ifndef __AM18X_RTC_H__
#define __AM18X_RTC_H__

#include "am18x_map.h"

#define BCD2BIN(val)	(((val) & 0x0F) + ((val) >> 4) * 10)
#define BIN2BCD(val)	((((val) / 10) << 4) + (val) % 10)

#endif//__AM18X_RTC_H__
