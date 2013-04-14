// tary, 0:39 2012/12/23

#ifndef __AM18X_LIB_H__
#define __AM18X_LIB_H__

#include "am18x_map.h"

#ifdef _SYSCFG
#include "am18x_syscfg.h"
#endif

#ifdef _PSC
#include "am18x_psc.h"
#endif

#ifdef _I2C
#include "am18x_i2c.h"
#endif

#ifdef _TIMER
#include "am18x_timer.h"
#endif

#ifdef _UART
#include "am18x_uart.h"
#endif

#ifdef _AINTC
#include "am18x_aintc.h"
#endif

#ifdef _PLL
#include "am18x_pll.h"
#endif

#endif//__AM18X_LIB_H__
