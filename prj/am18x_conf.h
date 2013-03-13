// tary, 1:05 2012/12/23
#ifndef __AM18X_CONF_H__
#define __AM18X_CONF_H__

#define __USE_STDINT_H

#include <am18x_type.h>

#define F_OSCIN			24000000UL	//Hz

#define _PSC
#define _PSC0
#define _PSC1

#define _SYSCFG
#define _SYSCFG0
#define _SYSCFG1

#define _AINTC

#define _I2C
#define _I2C0
#define _I2C1

#define _TIMER
#define _TIMER0
#define _TIMER1
#define _TIMER2
#define _TIMER3

#define _UART
#define _UART0
#define _UART1
#define _UART2


#ifdef DEBUG
#define assert(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
void assert_failed(uint8_t* file, uint32_t line);
#else
#define assert(expr) ((void)0)
#endif // DEBUG

typedef void (*none_arg_handler_t)(void);

int isr_set_hander(int intr_nr, none_arg_handler_t handle);


#endif//__AM18X_CONF_H__
