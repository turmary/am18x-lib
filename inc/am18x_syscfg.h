// tary, 13:11 2012/12/28

#ifndef __AM18X_SYSCFG_H__
#define __AM18X_SYSCFG_H__

#include "am18x_map.h"

am18x_rt syscfg_kick(am18x_bool lock);
am18x_rt syscfg_pll(am18x_bool lock);
am18x_rt syscfg_aync3(am18x_bool ispll0);
// pos = [0,4,8,12,16,20,24,28]
// val = [0..15]
am18x_rt syscfg_pinmux(uint32_t mux, uint32_t pos, uint32_t val);

#endif//__AM18X_SYSCFG_H__
