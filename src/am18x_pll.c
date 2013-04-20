// tary, 21:18 2013/4/15
#include "am18x_pll.h"
#include "auxlib.h"

// PLL0 plldivn = 1..7
// PLL1 plldivn = 1..3
am18x_rt pll_changing_sysclk_dividers(PLL_con_t* pcon, uint32_t plldivn, uint32_t divider) {
	uint32_t reg, msk, idx;

	// 1. Wait for the GOSTAT bit in PLLSTAT to clear to 0
	while (FIELD_GET(pcon->PLLSTAT, PLLSTAT_GOSTAT_MASK) != PLLSTAT_GOSTAT_done);

	// 2. Program the RATIO field in PLLDIVn
	msk = XXXDIVx_RATIO_MASK;
	if (plldivn < 4) {
		idx = PLLDIVxA_IDX_1 + plldivn - 1;
		reg = pcon->PLLDIVxA[idx];
		pcon->PLLDIVxA[idx] = FIELD_SET(reg, msk, XXXDIVx_RATIO_WR(divider));
	} else if (plldivn < 8) {
		idx = PLLDIVxB_IDX_4 + plldivn - 4;
		reg = pcon->PLLDIVxB[idx];
		pcon->PLLDIVxB[idx] = FIELD_SET(reg, msk, XXXDIVx_RATIO_WR(divider));
	}

	// 3. Set the GOSET bit in PLLCMD to 1
	pcon->PLLCMD = FIELD_SET(pcon->PLLCMD, PLLCMD_GOSET_MASK, PLLCMD_GOSET_initiate);

	// 4. Wait for the GOSTAT bit in PLLSTAT to clear to 0
	while (FIELD_GET(pcon->PLLSTAT, PLLSTAT_GOSTAT_MASK) != PLLSTAT_GOSTAT_done);

	return AM18X_OK;
}

am18x_rt pll_conf(PLL_con_t* pcon, const pll_conf_t* conf) {
	uint32_t msk, v;

	// 1. Program the CLKMODE bit in PLLC0 PLLCTL
	if (pcon == PLL0 && (conf->cflag & PLL_CFLAG_FROM_POWER_DOWN)) {
		msk = PLLCTL_CLKMODE_MASK;
		if (conf->cflag & PLL_CFLAG_REF_SQUARE) {
			v = PLLCTL_CLKMODE_wave;
		} else {
			v = PLLCTL_CLKMODE_crystal;
		}
		pcon->PLLCTL = FIELD_SET(pcon->PLLCTL, msk, v);
	}

	// 2. Switch the PLL to bypass mode
	// a) Clear the PLLENSRC bit in PLLCTL to 0
	//    allows PLLEN bit to take effect
	msk = PLLCTL_PLLENSRC_MASK;
	pcon->PLLCTL = FIELD_SET(pcon->PLLCTL, msk, PLLCTL_PLLENSRC_cleared);

	// b) For PLL0 only, select the clock source by programming
	//    the EXTCLKSRC bit in PLLCTL
	if (pcon == PLL0) {
		msk = PLLCTL_EXTCLKSRC_MASK;
		if (conf->cflag & PLL_CFLAG_EXT_CLK_PLL1) {
			v = PLLCTL_EXTCLKSRC_PLL1sysclk3;
		} else {
			v = PLLCTL_EXTCLKSRC_oscin;
		}
		pcon->PLLCTL = FIELD_SET(pcon->PLLCTL, msk, v);
	}

	// c) Clear the PLLEN bit in PLLCTL to 0
	msk = PLLCTL_PLLEN_MASK;
	pcon->PLLCTL = FIELD_SET(pcon->PLLCTL, msk, PLLCTL_PLLEN_no);

	// d) Wait for 4 OSCIN cycles to ensure that
	//    the PLLC has switch to bypass mode
	for (v = 0; v < 456 * 4 / 12; v++) {
		asm volatile ("nop");
	}

	// 3. Clear PLLRST in PLLCTL to 0
	msk = PLLCTL_PLLRST_MASK;
	pcon->PLLCTL = FIELD_SET(pcon->PLLCTL, msk, PLLCTL_PLLRST_asserted);

	// 4. Clear the PLLPWRDN bit in PLLCTL to 0
	if (conf->cflag & PLL_CFLAG_FROM_POWER_DOWN) {
		msk = PLLCTL_PLLPWRDN_MASK;
		pcon->PLLCTL = FIELD_SET(pcon->PLLCTL, msk, PLLCTL_PLLPWRDN_no);
	}

	// 5. Program the desired multiplier value in PLLM.
	//    Program the POSTDIV, as needed.
	pcon->PLLM = FIELD_SET(0, PLLM_MASK, PLLM_WR(conf->pllm));
	msk = XXXDIVx_DxEN_MASK | XXXDIVx_RATIO_MASK;
	v = XXXDIVx_DxEN_enable | XXXDIVx_RATIO_WR(conf->postdiv);
	pcon->POSTDIV = FIELD_SET(0, msk, v);

	// 6. If desired, program PLLDIVn registers to change
	//    the SYSCLKn divide values
	for (v = 0; v < 7; v++) {
		if (pcon == PLL1 && v >= 3) break;
		pll_changing_sysclk_dividers(pcon, v + 1, conf->plldiv[v]);
	}

	// 7. Set the PLLRST bit in PLL to 1 (brings PLL out of reset)
	msk = PLLCTL_PLLRST_MASK;
	pcon->PLLCTL = FIELD_SET(pcon->PLLCTL, msk, PLLCTL_PLLRST_deasserted);

	// 8. Wait for the PLL to lock
	// am1808.pdf 5.6.1 PLL Device-Specific Information
	// Max PLL Lock Time = 2000 * N / sqrt(M)
	// N = Pre-Divider Ratio
	// M = PLL Multiplier
	for (v = 0; v < 456 * ( 2000 * conf->prediv / 2) / 12; v++) {
		asm volatile ("nop");
	}

	// 9. Set the PLLEN bit in PLLCTL to 1 (removes PLL from bypass mode)
	msk = PLLCTL_PLLEN_MASK;
	pcon->PLLCTL = FIELD_SET(pcon->PLLCTL, msk, PLLCTL_PLLEN_yes);
	
	return AM18X_OK;
}

am18x_rt pll_cmd(PLL_con_t* pcon, uint32_t cmd, uint32_t arg) {
	uint32_t reg, msk;
	int i;

	switch (cmd) {
	case PLL_CMD_SOFT_RESET:
		if (pcon != PLL0) break;
		pcon->RSCTRL = FIELD_SET(0, RSCTRL_KEY_MASK, RSCTRL_KEY_unlock);
		while (FIELD_GET(pcon->RSCTRL, RSCTRL_KEY_MASK) != RSCTRL_KEY_unlocked);
		pcon->RSCTRL = FIELD_SET(0, RSCTRL_SWRST_MASK, RSCTRL_SWRST_yes);
		break;

	case PLL_CMD_ENABLE_PLL1_DIVS:
		if (pcon != PLL1) break;
		msk = XXXDIVx_DxEN_MASK;
		for (i = 0; i < 3; i++) {
			int idx = PLLDIVxA_IDX_1 + i;
			reg = pcon->PLLDIVxA[idx];
			pcon->PLLDIVxA[idx] = FIELD_SET(reg, msk, XXXDIVx_DxEN_enable);
		}
		break;

	default:
		break;
	}
	
	return AM18X_OK;
}

pll_reset_t pll_get_reset(void) {
	PLL_con_t* pcon = PLL0;
	pll_reset_t r;

	r = PLL_RESET_SOFTWARE;
	if (FIELD_GET(pcon->RSTYPE, RSTYPE_XWRST_MASK) == RSTYPE_XWRST_yes) {
		r = PLL_RESET_EXTERNAL;
	}
	if (FIELD_GET(pcon->RSTYPE, RSTYPE_POR_MASK) == RSTYPE_POR_yes) {
		r = PLL_RESET_POWER_ON;
	}

	return r;
}

#define cfdc_pllx_sysclk_1_3(pll_nr, s_nr)					\
uint32_t calc_freq_PLL##pll_nr##_SYSCLK##s_nr (uint32_t parent) {		\
	uint32_t id = CLK_NODE_PLL##pll_nr##_SYSCLK##s_nr;			\
	uint32_t msk = XXXDIVx_RATIO_MASK;					\
										\
	clk_nodes[id].divider = 1UL + FIELD_XGET(PLL##pll_nr->PLLDIVxA[PLLDIVxA_IDX_##s_nr], msk);\
	return 0;								\
}										\
										\
uint32_t do_change_PLL##pll_nr##_SYSCLK##s_nr (uint32_t parent) {		\
	uint32_t id = CLK_NODE_PLL##pll_nr##_SYSCLK##s_nr;			\
	uint32_t msk = XXXDIVx_RATIO_MASK;					\
	uint32_t reg, divider;							\
										\
	divider = clk_nodes[id].divider;					\
	reg = PLL##pll_nr->PLLDIVxA[PLLDIVxA_IDX_##s_nr];			\
	PLL##pll_nr->PLLDIVxA[PLLDIVxA_IDX_##s_nr] = FIELD_SET(reg, msk, XXXDIVx_RATIO_WR(divider));\
	return 0;								\
}

#define cfdc_pllx_sysclk_4_7(pll_nr, s_nr)					\
uint32_t calc_freq_PLL##pll_nr##_SYSCLK##s_nr (uint32_t parent) {		\
	uint32_t id = CLK_NODE_PLL##pll_nr##_SYSCLK##s_nr;			\
	uint32_t msk = XXXDIVx_RATIO_MASK;					\
										\
	clk_nodes[id].divider = 1UL + FIELD_XGET(PLL##pll_nr->PLLDIVxB[PLLDIVxB_IDX_##s_nr], msk);\
	return 0;								\
}										\
										\
uint32_t do_change_PLL##pll_nr##_SYSCLK##s_nr (uint32_t parent) {		\
	uint32_t id = CLK_NODE_PLL##pll_nr##_SYSCLK##s_nr;			\
	uint32_t msk = XXXDIVx_RATIO_MASK;					\
	uint32_t reg, divider;							\
										\
	divider = clk_nodes[id].divider;					\
	reg = PLL##pll_nr->PLLDIVxB[PLLDIVxB_IDX_##s_nr];			\
	PLL##pll_nr->PLLDIVxB[PLLDIVxB_IDX_##s_nr] = FIELD_SET(reg, msk, XXXDIVx_RATIO_WR(divider));\
	return 0;								\
}

#define cfdc_switch(name, cntrl, r, m, vdis, ven, ndis, nen)			\
uint32_t calc_freq_##name (uint32_t parent) {					\
	uint32_t id = CLK_NODE_##name;						\
	if (FIELD_GET(XX##cntrl->XX##r,r##_##m) == r##_##vdis ) {		\
		clk_nodes[id].parent = CLK_NODE_##ndis;				\
	} else {								\
		clk_nodes[id].parent = CLK_NODE_##nen;				\
	}									\
	return 0;								\
}										\
uint32_t do_change_##name (uint32_t parent) {					\
	uint32_t id = CLK_NODE_##name;						\
	if (clk_nodes[id].parent != CLK_NODE_##ndis) {				\
		XX##cntrl->XX##r = FIELD_SET(XX##cntrl->XX##r, r##_##m, r##_##ven);\
	} else {								\
		XX##cntrl->XX##r = FIELD_SET(XX##cntrl->XX##r, r##_##m, r##_##vdis);\
	}									\
	return 0;								\
}

#define cfdc_pllx_xxxdiv(reg, pll_nr, mr)					\
uint32_t calc_freq_##reg##pll_nr (uint32_t parent) {				\
	uint32_t id = CLK_NODE_##reg##pll_nr;					\
	uint32_t msk = XXXDIVx_RATIO_MASK;					\
										\
	clk_nodes[id].XX##mr = 1UL + FIELD_XGET(PLL##pll_nr->XX##reg, msk);	\
	return 0;								\
}										\
										\
uint32_t do_change_##reg##pll_nr (uint32_t parent) {				\
	uint32_t id = CLK_NODE_##reg##pll_nr;					\
	uint32_t msk = XXXDIVx_RATIO_MASK;					\
	uint32_t reg, rate;							\
										\
	rate = clk_nodes[id].XX##mr;						\
	reg = PLL##pll_nr->XX##reg;						\
	PLL##pll_nr->XX##reg = FIELD_SET(reg, msk, XXXDIVx_RATIO_WR(rate));	\
	return 0;								\
}

cfdc_pllx_sysclk_1_3(0,1)
cfdc_pllx_sysclk_1_3(0,2)
cfdc_pllx_sysclk_1_3(0,3)
cfdc_pllx_sysclk_4_7(0,4)
cfdc_pllx_sysclk_4_7(0,5)
cfdc_pllx_sysclk_4_7(0,6)
cfdc_pllx_sysclk_4_7(0,7)
cfdc_pllx_sysclk_1_3(1,1)
cfdc_pllx_sysclk_1_3(1,2)
cfdc_pllx_sysclk_1_3(1,3)
#define XXPLL0    PLL0
#define XXPLL1    PLL1
#define XXCKEN    CKEN
#define XXPLLCTL  PLLCTL
#define XXPREDIV  PREDIV
#define XXPLLM    PLLM
#define XXPOSTDIV POSTDIV
#define XXOSCDIV  OSCDIV
cfdc_switch(PLL0_AUXCLK,PLL0,CKEN,AUXEN_MASK,AUXEN_disable,AUXEN_enable,INVALID,PLL_CLKMODE)
cfdc_switch(PLL0_OBSCLK,PLL0,CKEN,OBSEN_MASK,OBSEN_disable,OBSEN_enable,INVALID,OSCDIV0)
cfdc_switch(PLL1_OBSCLK,PLL1,CKEN,OBSEN_MASK,OBSEN_disable,OBSEN_enable,INVALID,OSCDIV1)
cfdc_switch(PLL0_PLLEN,PLL0,PLLCTL,PLLEN_MASK,PLLEN_no,PLLEN_yes,PLL_EXTSRC,POSTDIV0)
cfdc_switch(PLL1_PLLEN,PLL1,PLLCTL,PLLEN_MASK,PLLEN_no,PLLEN_yes,PLL_CLKMODE,POSTDIV1)
cfdc_switch(PLL_EXTSRC,PLL0,PLLCTL,EXTCLKSRC_MASK,EXTCLKSRC_oscin,EXTCLKSRC_PLL1sysclk3,PLL_CLKMODE,PLL1_SYSCLK3)
#define XXSYSCFG0 SYSCFG0
#define XXCFGCHIP3 CFGCHIP3
cfdc_switch(EMA_CLKSRC,SYSCFG0,CFGCHIP3,EMA_CLKSRC_MASK,EMA_CLKSRC_sysclk3,EMA_CLKSRC_pll_out,PLL0_SYSCLK3,DIV4_5X)
cfdc_switch(ASYNC3,SYSCFG0,CFGCHIP3,ASYNC3_CLKSRC_MASK,ASYNC3_CLKSRC_pll0,ASYNC3_CLKSRC_pll1,PLL0_SYSCLK2,PLL1_SYSCLK2)
cfdc_switch(DIV4_5X,SYSCFG0,CFGCHIP3,DIV45PENA_MASK,DIV45PENA_no,DIV45PENA_yes,INVALID,DIV4_5)
#define XXdivider divider
#define XXmultiplier multiplier
cfdc_pllx_xxxdiv(PREDIV,0,divider)
cfdc_pllx_xxxdiv(PLLM,0,multiplier)
cfdc_pllx_xxxdiv(POSTDIV,0,divider)
cfdc_pllx_xxxdiv(OSCDIV,0,divider)
cfdc_pllx_xxxdiv(PLLM,1,multiplier)
cfdc_pllx_xxxdiv(POSTDIV,1,divider)
cfdc_pllx_xxxdiv(OSCDIV,1,divider)

uint32_t calc_freq_OCSEL0_OCSRC (uint32_t parent) {
	uint32_t id = CLK_NODE_OCSEL0_OCSRC;
	uint32_t par;

	switch (FIELD_GET(PLL0->OCSEL,OCSEL_OCSRC_MASK)) {
	case OCSEL_OCSRC_PLLsysclkx(1):
		par = CLK_NODE_PLL0_SYSCLK1;
		break;
	case OCSEL_OCSRC_PLLsysclkx(2):
		par = CLK_NODE_PLL0_SYSCLK2;
		break;
	case OCSEL_OCSRC_PLLsysclkx(3):
		par = CLK_NODE_PLL0_SYSCLK3;
		break;
	case OCSEL_OCSRC_PLLsysclkx(4):
		par = CLK_NODE_PLL0_SYSCLK4;
		break;
	case OCSEL_OCSRC_PLLsysclkx(5):
		par = CLK_NODE_PLL0_SYSCLK5;
		break;
	case OCSEL_OCSRC_PLLsysclkx(6):
		par = CLK_NODE_PLL0_SYSCLK6;
		break;
	case OCSEL_OCSRC_PLLsysclkx(7):
		par = CLK_NODE_PLL0_SYSCLK7;
		break;
	case OCSEL_OCSRC_PLL1obsclk:
		par = CLK_NODE_PLL1_OBSCLK;
		break;
	case OCSEL_OCSRC_oscin:
	default:
		par = CLK_NODE_PLL_CLKMODE;
		break;
	}
	clk_nodes[id].parent = par;
	return 0;
}
uint32_t do_change_OCSEL0_OCSRC (uint32_t parent) {
	uint32_t id = CLK_NODE_OCSEL0_OCSRC;
	uint32_t v;
	switch (clk_nodes[id].parent) {
	case CLK_NODE_PLL0_SYSCLK1:
		v = OCSEL_OCSRC_PLLsysclkx(1);
		break;
	case CLK_NODE_PLL0_SYSCLK2:
		v = OCSEL_OCSRC_PLLsysclkx(2);
		break;
	case CLK_NODE_PLL0_SYSCLK3:
		v = OCSEL_OCSRC_PLLsysclkx(3);
		break;
	case CLK_NODE_PLL0_SYSCLK4:
		v = OCSEL_OCSRC_PLLsysclkx(4);
		break;
	case CLK_NODE_PLL0_SYSCLK5:
		v = OCSEL_OCSRC_PLLsysclkx(5);
		break;
	case CLK_NODE_PLL0_SYSCLK6:
		v = OCSEL_OCSRC_PLLsysclkx(6);
		break;
	case CLK_NODE_PLL0_SYSCLK7:
		v = OCSEL_OCSRC_PLLsysclkx(7);
		break;
	case CLK_NODE_PLL1_OBSCLK:
		v = OCSEL_OCSRC_PLL1obsclk;
		break;
	case CLK_NODE_PLL_CLKMODE:
	default:
		v = OCSEL_OCSRC_oscin;
		break;
	}
	PLL0->OCSEL = FIELD_SET(PLL0->OCSEL, OCSEL_OCSRC_MASK, v);
	return 0;
}

uint32_t calc_freq_OCSEL1_OCSRC (uint32_t parent) {
	uint32_t id = CLK_NODE_OCSEL1_OCSRC;
	uint32_t par;

	switch (FIELD_GET(PLL1->OCSEL,OCSEL_OCSRC_MASK)) {
	case OCSEL_OCSRC_PLLsysclkx(1):
		par = CLK_NODE_PLL1_SYSCLK1;
		break;
	case OCSEL_OCSRC_PLLsysclkx(2):
		par = CLK_NODE_PLL1_SYSCLK2;
		break;
	case OCSEL_OCSRC_PLLsysclkx(3):
		par = CLK_NODE_PLL1_SYSCLK3;
		break;
	case OCSEL_OCSRC_oscin:
	default:
		par = CLK_NODE_PLL_CLKMODE;
		break;
	}
	clk_nodes[id].parent = par;
	return 0;
}
uint32_t do_change_OCSEL1_OCSRC (uint32_t parent) {
	uint32_t id = CLK_NODE_OCSEL1_OCSRC;
	uint32_t v;
	switch (clk_nodes[id].parent) {
	case CLK_NODE_PLL1_SYSCLK1:
		v = OCSEL_OCSRC_PLLsysclkx(1);
		break;
	case CLK_NODE_PLL1_SYSCLK2:
		v = OCSEL_OCSRC_PLLsysclkx(2);
		break;
	case CLK_NODE_PLL1_SYSCLK3:
		v = OCSEL_OCSRC_PLLsysclkx(3);
		break;
	case CLK_NODE_PLL_CLKMODE:
	default:
		v = OCSEL_OCSRC_oscin;
		break;
	}
	PLL1->OCSEL = FIELD_SET(PLL1->OCSEL, OCSEL_OCSRC_MASK, v);
	return 0;
}

#define cnm(name)	CLK_NODE_##name, #name
#define cm(name)	CLK_NODE_##name
#define cfdc(name)	calc_freq_##name, do_change_##name
#define CFMUX		CN_FLAG_MUX
#define REREAD		CN_FLAG_REREAD
#define CFDC_VALID(flg)	((flg) & (CN_FLAG_MUX | CN_FLAG_REREAD))
#define RECALC		CN_FLAG_RECALC

clk_node_t clk_nodes[] = {
	// ID                  PARENT,       FLAG, MULT, DIV, CALC_FREQ, DO_CHANGE, PARENT_LIST
	{ 0, 0, },
	{ cnm(PLL0_SYSCLK1), cm(PLL0_PLLEN),  REREAD, 0, 1, cfdc(PLL0_SYSCLK1), },
	{ cnm(PLL0_SYSCLK2), cm(PLL0_PLLEN),  REREAD, 0, 2, cfdc(PLL0_SYSCLK2), },
	{ cnm(PLL0_SYSCLK3), cm(PLL0_PLLEN),  REREAD, 0, 3, cfdc(PLL0_SYSCLK3), },
	{ cnm(PLL0_SYSCLK4), cm(PLL0_PLLEN),  REREAD, 0, 4, cfdc(PLL0_SYSCLK4), },
	{ cnm(PLL0_SYSCLK5), cm(PLL0_PLLEN),  REREAD, 0, 3, cfdc(PLL0_SYSCLK5), },
	{ cnm(PLL0_SYSCLK6), cm(PLL0_PLLEN),  REREAD, 0, 1, cfdc(PLL0_SYSCLK6), },
	{ cnm(PLL0_SYSCLK7), cm(PLL0_PLLEN),  REREAD, 0, 6, cfdc(PLL0_SYSCLK7), },
	{ cnm(EMA_CLKSRC),   cm(PLL0_SYSCLK3), CFMUX, 0, 0, cfdc(EMA_CLKSRC),   },
	{ cnm(PLL0_AUXCLK),  cm(PLL_CLKMODE),  CFMUX, 0, 0, cfdc(PLL0_AUXCLK),  },
	{ cnm(PLL0_OBSCLK),  cm(OSCDIV0),      CFMUX, 0, 0, cfdc(PLL0_OBSCLK),  },
	{ cnm(PLL1_SYSCLK1), cm(PLL1_PLLEN),  REREAD, 0, 1, cfdc(PLL1_SYSCLK1), },
	{ cnm(PLL1_SYSCLK2), cm(PLL1_PLLEN),  REREAD, 0, 2, cfdc(PLL1_SYSCLK2), },
	{ cnm(PLL1_SYSCLK3), cm(PLL1_PLLEN),  REREAD, 0, 3, cfdc(PLL1_SYSCLK3), },
	{ cnm(PLL1_OBSCLK),  cm(OSCDIV1),      CFMUX, 0, 0, cfdc(PLL1_OBSCLK),  },
	{ cnm(ASYNC3),       cm(PLL0_SYSCLK2), CFMUX, 0, 0, cfdc(ASYNC3),       },
	{ cnm(PLL0_PLLEN),   cm(PLL_EXTSRC),   CFMUX, 0, 0, cfdc(PLL0_PLLEN),   },
	{ cnm(PLL_EXTSRC),   cm(PLL_CLKMODE),  CFMUX, 0, 0, cfdc(PLL_EXTSRC),   },
	{ cnm(POSTDIV0),     cm(PLLM0),       REREAD, 0, 0, cfdc(POSTDIV0),     },
	{ cnm(PLLM0),        cm(PREDIV0),     REREAD, 0, 0, cfdc(PLLM0),        },
	{ cnm(PREDIV0),      cm(PLL_CLKMODE), REREAD, 0, 0, cfdc(PREDIV0),      },
	{ cnm(PLL_CLKMODE),  cm(OSCIN),            0, 1, 0, },
	{ cnm(DIV4_5X),      cm(DIV4_5),       CFMUX, 0, 0, cfdc(DIV4_5X),      },
	{ cnm(DIV4_5),       cm(PLLM0),            0, 2, 9, },
	{ cnm(OSCDIV0),      cm(OCSEL0_OCSRC),REREAD, 0, 0, cfdc(OSCDIV0),      },
	{ cnm(OCSEL0_OCSRC), cm(PLL_CLKMODE),  CFMUX, 0, 0, cfdc(OCSEL0_OCSRC), },
	{ cnm(PLL1_PLLEN),   cm(POSTDIV1),     CFMUX, 0, 0, cfdc(PLL1_PLLEN),   },
	{ cnm(POSTDIV1),     cm(PLLM1),       REREAD, 0, 0, cfdc(POSTDIV1),     },
	{ cnm(PLLM1),        cm(PLL_CLKMODE), REREAD, 0, 0, cfdc(PLLM1),        },
	{ cnm(OSCDIV1),      cm(OCSEL1_OCSRC),REREAD, 0, 0, cfdc(OSCDIV1),      },
	{ cnm(OCSEL1_OCSRC), cm(PLL_CLKMODE),  CFMUX, 0, 0, cfdc(OCSEL1_OCSRC), },
	{ cnm(OSCIN),	     cm(INVALID),          0, 0, 0, },
};

am18x_rt clk_node_init(void) {
	int i;

	pll_cmd(PLL1, PLL_CMD_ENABLE_PLL1_DIVS, 0);

	for (i = 0; i < countof(clk_nodes); i++) {
		clk_node_t* cni = clk_nodes + i;

		cni->name += get_exec_base();
		*(uint32_t*)&cni->calc_freq += get_exec_base();
		*(uint32_t*)&cni->do_change += get_exec_base();
		cni->flag |= CN_FLAG_RECALC;
	}
	return AM18X_OK;
}

static uint32_t clk_node_calc_freq_inner(uint32_t id) {
	uint32_t freq;
	clk_node_t* cni = clk_nodes + id;

	#if 0
	printk("%d ", id);
	#endif

	if (id == CLK_NODE_INVALID) {
		return 0UL;
	}
	if (id == CLK_NODE_OSCIN) {
		return F_OSCIN;
	}
	if ((cni->flag & CN_FLAG_RECALC) == 0) {
		return cni->freq;
	}

	if (CFDC_VALID(cni->flag)) {
		(cni->calc_freq)(0);
	}
	
	freq = clk_node_calc_freq_inner(cni->parent);
	if ((cni->flag & CN_FLAG_MUX) == 0) {
		if (cni->multiplier != 0) freq *= cni->multiplier;
		if (cni->divider != 0) freq /= cni->divider;
	}

	if (cni->flag & CN_FLAG_RECALC) {
		cni->flag &= ~CN_FLAG_RECALC;
		cni->freq = freq;
	}
	return freq;
}

am18x_rt clk_node_recalc_freq(void) {
	int i;

	for (i = CLK_NODE_INVALID + 1; i < CLK_NODE_CNT; i++) {
		clk_node_t* cni = clk_nodes + i;
		cni->flag |= CN_FLAG_RECALC;
		cni->flag &= ~CN_FLAG_VISITED;
	}
	for (i = CLK_NODE_INVALID + 1; i < CLK_NODE_CNT; i++) {
		clk_node_calc_freq_inner(i);
	}
	return AM18X_OK;
}

uint32_t clk_node_get_freq(uint32_t id) {
	uint32_t freq;

	freq = clk_node_calc_freq_inner(id);

	return freq;
}

am18x_rt clk_node_output(void) {
	#define ONE_MEGA	1000000
	int i;

	clk_node_recalc_freq();

	for (i = CLK_NODE_INVALID + 1; i < CLK_NODE_CNT; i++) {
		uint32_t f = clk_node_get_freq(i);

		printk("[%12s] = ", clk_nodes[i].name);
		if (f % ONE_MEGA == 0) {
			printk("%10dMhz\n", f / ONE_MEGA);
		} else {
			uint32_t frac = f % ONE_MEGA / 1000;
			printk("%6d.%3dMhz\n", f / ONE_MEGA, frac);
		}
	}
	return AM18X_OK;
}

static uint32_t clk_node_tree_innner(uint32_t id, int level) {
	#define LINE_SIZE	1024
	#define LINE_UNIT	14
	static char line0[LINE_SIZE];
	static char line1[LINE_SIZE];
	uint32_t freq;
	am18x_bool found = AM18X_FALSE;
	int i;

	freq = clk_node_get_freq(id);

	sprintf(line0 + LINE_UNIT * level, "[%12s]", clk_nodes[id].name);
	sprintf(line1 + LINE_UNIT * level, "    %4dMhz   ", freq / ONE_MEGA);

	for (i = CLK_NODE_INVALID + 1; i < CLK_NODE_CNT; i++) {
		if (clk_nodes[i].parent == id) {
			clk_node_tree_innner(i, level + 1);
			found = AM18X_TRUE;
		}
	}

	if (found) {
		return 0;
	}

	for (i = level; i >= 0; i--) {
		if (line0[i * LINE_UNIT] != '[') {
			break;
		}
	}
	if (i >= 0) {
		int j = i * LINE_UNIT + LINE_UNIT / 2 + 1;

		line0[j++] = '|';
		for (; j < (i + 1) * LINE_UNIT; j++) {
			line0[j] = '_';
		}
	}
	printk("%s\n", line0);
	printk("%s\n", line1);

	for (i = 0; i < level * LINE_UNIT; i++) {
		line0[i] = line1[i] = ' ';
	}
	return 0;
}

am18x_rt clk_node_tree(void) {
	int i;

	clk_node_recalc_freq();

	for (i = CLK_NODE_INVALID + 1; i < CLK_NODE_CNT; i++) {
		clk_node_t* cni = clk_nodes + i;

		if (cni->parent != CLK_NODE_INVALID) {
			continue;
		}
		clk_node_tree_innner(i, 0);
	}
	return AM18X_OK;
}

static am18x_bool clk_node_change_parent_inner(uint32_t id) {
	am18x_bool found = AM18X_FALSE;
	int i;

	clk_nodes[id].flag |= CN_FLAG_RECALC;

	for (i = CLK_NODE_INVALID + 1; i < CLK_NODE_CNT; i++) {
		if (clk_nodes[i].parent == id) {
			clk_node_change_parent_inner(i);
			found = AM18X_TRUE;
		}
	}

	return found;
}

am18x_rt clk_node_change_parent(uint32_t id, uint32_t parent) {
	clk_node_t* cni = clk_nodes + id;

	if (CFDC_VALID(cni->flag) == 0) {
		return AM18X_FALSE;
	}

	cni->parent = parent;
	(cni->do_change)(0);

	clk_node_change_parent_inner(id);
	clk_node_calc_freq_inner(id);
	return AM18X_OK;
}

uint32_t dev_get_freq(uint32_t dclk_id) {
	uint32_t cn_id = dclk_id / DCLK_ID_GRP_SZ;

	return clk_node_get_freq(cn_id);
}