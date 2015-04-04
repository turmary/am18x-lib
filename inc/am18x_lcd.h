// tary, 17:57 2013/12/8

#ifndef __AM18X_LCD_H__
#define __AM18X_LCD_H__

#include "am18x_map.h"

typedef struct {
	uint32_t	pclk;
	uint32_t	width, height;
	uint16_t	hfp, hsw, hbp;
	uint16_t	vfp, vsw, vbp;
} lcd_conf_t;

am18x_rt lcd_conf(LCD_con_t* lcdc, const lcd_conf_t* conf);

#endif//__AM18X_LCD_H__
