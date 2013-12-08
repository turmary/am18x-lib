// tary, 11:46 2013/12/7
#include "am18x_ddr.h"
#include "am18x_pll.h"
#include "am18x_psc.h"
#include "am18x_dclk.h"
#include "am18x_syscfg.h"
#include "auxlib.h"

static pll_conf_t pllconf[1] = {
{
	.pllm = 30,
	.prediv = 1,
	.postdiv = 2,
	.plldiv = { 1, 2, 3, 0, 0, 0, 0, },
	.cflag = 0,
}
};

static uint32_t tv2v(uint32_t freq_hz, uint32_t tv_ns) {
	uint32_t r;

	r = (freq_hz / 100000 * tv_ns) / 10000;
	return r;
}

am18x_rt ddr_initialize(DDR_con_t* dcon, const ddr_conf_t* conf) {
#define _TV2V(tv)	tv2v(mclk, (tv))
	uint32_t mclk, _2x_clk, reg, v;

	// 14.2.13.1 Initializing Following Device Power up or Reset

	// 1. Program PLLC1 registers to start the PLL1_SYSCLK1
	mclk = conf->freq_ck;
	if (mclk > 150000000UL) {
		mclk = 150000000UL;
	}
	pllconf->pllm = mclk * 2 * pllconf->postdiv / F_OSCIN;
	pll_set_conf(PLL1, pllconf);
	clk_node_recalc();
	_2x_clk = dev_get_freq(DCLK_ID_DDR2_MDDR_PHY);

	mclk = _2x_clk / 2;
	printk("MCLK = %d Hz\n", mclk);

	// 2. Program PSC to enable the DDR2/mDDR memory controller clock
	psc_state_transition(PSC_DDR2, PSC_STATE_ENABLE);

	// 3. Perform VTP IO calibration
	// 4. Set IOPWRDN bit in VTPIO_CTL
	// to allow the input receivers to save power
	syscfg_vtpio_calibrate();

	// 5. Configure DRPYC1R
	reg = dcon->DRPYC1R;
	reg = FIELD_SET(reg, DRPYC1R_EXTSTRBEN_MASK, DRPYC1R_EXTSTRBEN_external);
	reg = FIELD_SET(reg, DRPYC1R_PWRDNEN_MASK, DRPYC1R_PWRDNEN_powerdown);
	reg = FIELD_SET(reg, DRPYC1R_RL_MASK, DRPYC1R_RL_VAL(conf->cl));
	dcon->DRPYC1R = reg;

	// 6. Configure the DDR_SLEW
	syscfg_ddr_slew(conf->ddr2_not_mddr);

	// 7. Set the BOOTUNLOCK bit (unlocked) in the SDCR
	reg = dcon->SDCR;
	reg = FIELD_SET(reg, SDCR_BOOTUNLOCK_MASK, SDCR_BOOTUNLOCK_unlock);
	dcon->SDCR = reg;

	// 8. Program SDCR to the desired value with BOOTUNLOCK bit
	// cleared to 0 and TIMUNLOCK bit set to 1
	reg = FIELD_SET(reg, SDCR_BOOTUNLOCK_MASK, SDCR_BOOTUNLOCK_none);
	reg = FIELD_SET(reg, SDCR_TIMUNLOCK_MASK, SDCR_TIMUNLOCK_unlock);
	reg = FIELD_SET(reg, SDCR_DDR2TERM_MASK, SDCR_DDR2TERM_disable);
	reg = FIELD_SET(reg, SDCR_DDRDRIVE_MASK, SDCR_DDRDRIVE_full);
	if (conf->ddr2_not_mddr) {
		reg = FIELD_SET(reg, SDCR_IBANKPOS_MASK, SDCR_IBANKPOS_normal);
		reg = FIELD_SET(reg, SDCR_MSDRAMEN_MASK, SDCR_MSDRAMEN_no);
		reg = FIELD_SET(reg, SDCR_DDR2EN_MASK, SDCR_DDR2EN_yes);
	} else {
		reg = FIELD_SET(reg, SDCR_IBANKPOS_MASK, SDCR_IBANKPOS_special);
		reg = FIELD_SET(reg, SDCR_MSDRAMEN_MASK, SDCR_MSDRAMEN_yes);
		reg = FIELD_SET(reg, SDCR_DDR2EN_MASK, SDCR_DDR2EN_no);
	}
	reg = FIELD_SET(reg, SDCR_DDRDLLDIS_MASK, SDCR_DDRDLLDIS_no);
	reg = FIELD_SET(reg, SDCR_DDREN_MASK, SDCR_DDREN_yes);
	reg = FIELD_SET(reg, SDCR_SDRAMEN_MASK, SDCR_SDRAMEN_yes);

	reg = FIELD_SET(reg, SDCR_CL_MASK, SDCR_CL_VAL(conf->cl));
	switch (conf->bank_cnt) {
	case 2:  v = SDCR_IBANK_2banks;break;
	case 4:  v = SDCR_IBANK_4banks;break;
	case 8:  v = SDCR_IBANK_8banks;break;
	default: v = SDCR_IBANK_1bank;break;
	}
	reg = FIELD_SET(reg, SDCR_IBANK_MASK, v);
	switch (conf->page_size) {
	case 9:  v = SDCR_PAGESIZE_512w9col;break;
	case 10: v = SDCR_PAGESIZE_1kw10col;break;
	case 11: v = SDCR_PAGESIZE_2kw11col;break;
	default: v = SDCR_PAGESIZE_256w8col;break;
	}
	reg = FIELD_SET(reg, SDCR_PAGESIZE_MASK, v);

	dcon->SDCR = reg;

	// 9. For mDDR only, program the SDCR2 to the desired value
	reg = dcon->SDCR2;
	if (!conf->ddr2_not_mddr) {
		switch (conf->pasr) {
		case 2:  v = SDCR2_PASR_2banks; break;
		case 4:  v = SDCR2_PASR_1banks; break;
		case 8:  v = SDCR2_PASR_half_bank; break;
		case 16: v = SDCR2_PASR_quarter_bank; break;
		default: v = SDCR2_PASR_4banks; break;
		}
		reg = FIELD_SET(reg, SDCR2_PASR_MASK, v);

		v = SDCR2_ROWSIZE_VAL(conf->row_size - 9);
		reg = FIELD_SET(reg, SDCR2_ROWSIZE_MASK, v);
	}
	dcon->SDCR2 = reg;

	// 10. Program the SDTIMR1 and SDTIMR2 to
	// the desired values to meet the memory data sheet specification
	reg = dcon->SDTIMR1;
	v = _TV2V(conf->trfc);
	reg = __field_xset(reg, SDTIMR1_TRFC_MASK, v);
	v = _TV2V(conf->trp);
	reg = __field_xset(reg, SDTIMR1_TRP_MASK, v);
	v = _TV2V(conf->trcd);
	reg = __field_xset(reg, SDTIMR1_TRCD_MASK, v);
	v = _TV2V(conf->twr);
	reg = __field_xset(reg, SDTIMR1_TWR_MASK, v);
	v = _TV2V(conf->tras);
	reg = __field_xset(reg, SDTIMR1_TRAS_MASK, v);
	v = _TV2V(conf->trc);
	reg = __field_xset(reg, SDTIMR1_TRC_MASK, v);
	v = _TV2V(conf->trrd);
	reg = __field_xset(reg, SDTIMR1_TRRD_MASK, v);
	v = _TV2V(conf->twtr);
	reg = __field_xset(reg, SDTIMR1_TWTR_MASK, v);
	dcon->SDTIMR1 = reg;

	reg = dcon->SDTIMR2;
	v = conf->trasmax / conf->trefi - 1;
	reg = __field_xset(reg, SDTIMR2_TRASMAX_MASK, v);
	if (conf->txp > conf->tcke) {
		reg = __field_xset(reg, SDTIMR2_TXP_MASK, conf->txp - 1);
	} else {
		reg = __field_xset(reg, SDTIMR2_TXP_MASK, conf->tcke - 1);
	}
	v = _TV2V(conf->txsnr);
	reg = __field_xset(reg, SDTIMR2_TXSNR_MASK, v);
	reg = __field_xset(reg, SDTIMR2_TXSRD_MASK, conf->txsrd - 1);
	v = _TV2V(conf->trtp);
	reg = __field_xset(reg, SDTIMR2_TRTP_MASK, v);
	reg = __field_xset(reg, SDTIMR2_TCKE_MASK, conf->tcke - 1);
	dcon->SDTIMR2 = reg;

	// 11. Clear TIMUNLOCK bit in SDCR
	reg = dcon->SDCR;
	reg = FIELD_SET(reg, SDCR_TIMUNLOCK_MASK, SDCR_TIMUNLOCK_none);
	dcon->SDCR = reg;

	// 12. Program the SDRCR
	reg = dcon->SDRCR;
	reg = FIELD_SET(reg, SDRCR_LPMODEN_MASK, SDRCR_LPMODEN_yes);
	reg = FIELD_SET(reg, SDRCR_MCLKSTOPEN_MASK, SDRCR_MCLKSTOPEN_yes);
	reg = FIELD_SET(reg, SDRCR_SRPD_MASK, SDRCR_SRPD_selfrefresh);
	v = _TV2V(conf->trefi);
	reg = FIELD_SET(reg, SDRCR_RR_MASK, SDRCR_RR_VAL(v));
	dcon->SDRCR = reg;

	// 13. Program the PSC to reset the DDR2/mDDR memory controller
	psc_state_transition(PSC_DDR2, PSC_STATE_SYNC_RESET);

	// 14. Program the PSC to re-enable the DDR2/mDDR memory controller
	psc_state_transition(PSC_DDR2, PSC_STATE_ENABLE);

	// 15. Clear LPMODEN and MCLKSTOPEN bits in SDRCR to disable self-refresh
	reg = dcon->SDRCR;
	reg = FIELD_SET(reg, SDRCR_LPMODEN_MASK, SDRCR_LPMODEN_no);
	reg = FIELD_SET(reg, SDRCR_MCLKSTOPEN_MASK, SDRCR_MCLKSTOPEN_no);
	dcon->SDRCR = reg;

	// 16. Configure the PBBPR to a value lower than default value of FFh.
	reg = dcon->PBBPR;
	reg = FIELD_SET(reg, PBBPR_PROLDCOUNT_MASK, PBBPR_PROLDCOUNT_VAL(0x30));
	dcon->PBBPR = reg;

	return AM18X_OK;
}
