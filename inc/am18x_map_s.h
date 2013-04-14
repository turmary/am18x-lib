#define __AM18X_MAP_H__
#define _EXTERN		extern
#define _RS(b,a)	(((b) - (a) - 0x4) >> 2)
#define PLL0_REVID			0x44813C00
#define PLL1_REVID			0x44814400
#define RSTYPE_PLLSWRST_MASK		(0x1 << 2)
#define RSTYPE_PLLSWRST_no		(0x0 << 2)
#define RSTYPE_PLLSWRST_yes		(0x1 << 2)
#define RSTYPE_XWRST_MASK		(0x1 << 1)
#define RSTYPE_XWRST_no			(0x0 << 1)
#define RSTYPE_XWRST_yes		(0x1 << 1)
#define RSTYPE_POR_MASK			(0x1 << 0)
#define RSTYPE_POR_no			(0x0 << 0)
#define RSTYPE_POR_yes			(0x1 << 0)
#define RSCTRL_SWRST_MASK		(0x1 << 16)
#define RSCTRL_SWRST_yes		(0x0 << 16)
#define RSCTRL_SWRST_no			(0x1 << 16)
#define RSCTRL_KEY_MASK			(0xFFFF << 0)
#define RSCTRL_KEY_locked		(0x3 << 0)
#define RSCTRL_KEY_unlocked		(0xC << 0)
#define RSCTRL_KEY_unlock		(0x5A69 << 0)
#define PLLCTL_EXTCLKSRC_MASK		(0x1 << 9)
#define PLLCTL_EXTCLKSRC_oscin		(0x0 << 9)
#define PLLCTL_EXTCLKSRC_PLL1sysclk3	(0x1 << 9)
#define PLLCTL_CLKMODE_MASK		(0x1 << 8)
#define PLLCTL_CLKMODE_crystal		(0x0 << 8)
#define PLLCTL_CLKMODE_wave		(0x1 << 8)
#define PLLCTL_PLLENSRC_MASK		(0x1 << 5)
#define PLLCTL_PLLENSRC_none		(0x0 << 5)
#define PLLCTL_PLLENSRC_cleared		(0x1 << 5)
#define PLLCTL_PLLRST_MASK		(0x1 << 3)
#define PLLCTL_PLLRST_asserted		(0x0 << 3)
#define PLLCTL_PLLRST_deasserted	(0x1 << 3)
#define PLLCTL_PLLPWRDN_MASK		(0x1 << 1)
#define PLLCTL_PLLPWRDN_no		(0x0 << 1)
#define PLLCTL_PLLPWRDN_yes		(0x1 << 1)
#define PLLCTL_PLLEN_MASK		(0x1 << 0)
#define PLLCTL_PLLEN_no			(0x0 << 0)
#define PLLCTL_PLLEN_yes		(0x1 << 0)
#define OCSEL_OCSRC_MASK		(0x1F << 0)
#define OCSEL_OCSRC_oscin		(0x14 << 0)
#define OCSEL_OCSRC_PLLsysclkx(x)	((0x16 + (x)) << 0)
#define OCSEL_OCSRC_PLL1obsclk		(0x1E << 0)
#define PLLM_MASK			(0x1F << 0)
#define PLLM_WR(m)			(((m) - 0x1) << 0)
#define XXXDIVx_DxEN_MASK		(0x1 << 15)
#define XXXDIVx_DxEN_disable		(0x0 << 15)
#define XXXDIVx_DxEN_enable		(0x1 << 15)
#define XXXDIVx_RATIO_MASK		(0x1F << 0)
#define XXXDIVx_RATIO_WR(r)		(((r) - 0x1) << 0)
#define PLLDIVxA_IDX_1			0x0
#define PLLDIVxA_IDX_2			0x1
#define PLLDIVxA_IDX_3			0x2
#define PLLCMD_GOSET_MASK		(0x1 << 0)
#define PLLCMD_GOSET_clear		(0x0 << 0)
#define PLLCMD_GOSET_initiate		(0x1 << 0)
#define PLLSTAT_STABLE_MASK		(0x1 << 2)
#define PLLSTAT_STABLE_no		(0x0 << 2)
#define PLLSTAT_STABLE_yes		(0x1 << 2)
#define PLLSTAT_GOSTAT_MASK		(0x1 << 0)
#define PLLSTAT_GOSTAT_done		(0x0 << 1)
#define PLLSTAT_GOSTAT_in_progress	(0x1 << 1)
#define ALNCTL_ALNx_MASK(x)		(0x1 << ((x) - 1))
#define ALNCTL_ALNx_no			(0x0 << ((x) - 1))
#define ALNCTL_ALNx_yes			(0x1 << ((x) - 1))
#define DCHANGE_SYSx_MASK(x)		(0x1 << ((x) - 1))
#define DCHANGE_SYSx_none		(0x0 << ((x) - 1))
#define DCHANGE_SYSx_modified		(0x1 << ((x) - 1))
#define CKEN_OBSEN_MASK			(0x1 << 1)
#define CKEN_OBSEN_disable		(0x0 << 1)
#define CKEN_OBSEN_enable		(0x1 << 1)
#define CKEN_AUXEN_MASK			(0x1 << 0)
#define CKEN_AUXEN_disable		(0x0 << 0)
#define CKEN_AUXEN_enable		(0x1 << 0)
#define CKSTAT_OBSEN_MASK		(0x1 << 1)
#define CKSTAT_OBSEN_off		(0x0 << 1)
#define CKSTAT_OBSEN_on			(0x1 << 1)
#define CKSTAT_AUXEN_MASK		(0x1 << 0)
#define CKSTAT_AUXEN_off		(0x0 << 0)
#define CKSTAT_AUXEN_on			(0x1 << 0)
#define SYSTAT_SYSxON_MASK(X)		(0x1 << ((x) - 1))
#define SYSTAT_SYSxON_off		(0x0 << ((x) - 1))
#define SYSTAT_SYSxON_on		(0x1 << ((x) - 1))
#define PLLDIVxB_IDX_4			0x0
#define PLLDIVxB_IDX_5			0x1
#define PLLDIVxB_IDX_6			0x2
#define PLLDIVxB_IDX_7			0x3
#define MODULE_NR_PER_PSC	32
#define PTCMD_GO1			(0x1 << 1)
#define PTCMD_GO0			(0x1 << 0)
#define PTSTAT_GO1_MASK			(0x1 << 1)
#define PTSTAT_GO1_no			(0x0 << 1)
#define PTSTAT_GO1_yes			(0x1 << 1)
#define PTSTAT_GO0_MASK			(0x1 << 0)
#define PTSTAT_GO0_no			(0x0 << 0)
#define PTSTAT_GO0_yes			(0x1 << 0)
#define PDSTATx_EMUIHB_MASK		(0x1 << 11)
#define PDSTATx_EMUIHB_unactive		(0x0 << 11)
#define PDSTATx_EMUIHB_active		(0x1 << 11)
#define PDSTATx_PORDONE_MASK		(0x1 << 9)
#define PDSTATx_PORDONE_no		(0x0 << 9)
#define PDSTATx_PORDONE_yes		(0x1 << 9)
#define PDSTATx_POR_MASK		(0x1 << 8)
#define PDSTATx_POR_asserted		(0x0 << 8)
#define PDSTATx_POR_deasserted		(0x1 << 8)
#define PDSTATx_STATE_MASK		(0x1F << 0)
#define PDSTATx_STATE_off		(0x0 << 0)
#define PDSTATx_STATE_on		(0x1 << 0)
#define PDSTATx_STATE_in_transition(x)	(0x10 <= (x) && (x) <= 0x1A)
#define PDCTLx_WAKECNT_MASK		(0xFF << 16)
#define PDCTLx_GOOD2ACCESS_MASK		(0xF << 20)
#define PDCTLx_ON2GOOD_MASK		(0xF << 16)
#define PDCTLx_PDMODE_MASK		(0xF << 12)
#define PDCTLx_PDMODE_on		(0xF << 12)
#define PDCTLx_EMUIHBIE_MASK		(0x1 << 9)
#define PDCTLx_EMUIHBIE_disable		(0x0 << 9)
#define PDCTLx_EMUIHBIE_enable		(0x1 << 9)
#define PDCTLx_NEXT_MASK		(0x1 << 0)
#define PDCTLx_NEXT_off			(0x0 << 0)
#define PDCTLx_NEXT_on			(0x1 << 0)
#define PDCFGx_PD_LOCK_MASK		(0x1 << 3)
#define PDCFGx_PD_LOCK_locked		(0x0 << 3)
#define PDCFGx_PD_LOCK_unlocked		(0x1 << 3)
#define PDCFGx_ICEPICK_MASK		(0x1 << 2)
#define PDCFGx_ICEPICK_unpresent	(0x0 << 2)
#define PDCFGx_ICEPICK_present		(0x1 << 2)
#define PDCFGx_RAM_PSM_MASK		(0x1 << 1)
#define PDCFGx_RAM_PSM_no		(0x0 << 1)
#define PDCFGx_RAM_PSM_yes		(0x1 << 1)
#define PDCFGx_ALWAYSON_MASK		(0x1 << 0)
#define PDCFGx_ALWAYSON_no		(0x0 << 0)
#define PDCFGx_ALWAYSON_yes		(0x1 << 0)
#define MDSTATx_EMUIHB_MASK		(0x1 << 17)
#define MDSTATx_EMUIHB_no		(0x0 << 17)
#define MDSTATx_EMUIHB_yes		(0x1 << 17)
#define MDSTATx_EMURST_MASK		(0x1 << 16)
#define MDSTATx_EMURST_no		(0x0 << 16)
#define MDSTATx_EMURST_yes		(0x1 << 16)
#define MDSTATx_MCKOUT_MASK		(0x1 << 12)
#define MDSTATx_MCKOUT_off		(0x0 << 12)
#define MDSTATx_MCKOUT_on		(0x1 << 12)
#define MDSTATx_MRST_MASK		(0x1 << 10)
#define MDSTATx_MRST_asserted		(0x0 << 10)
#define MDSTATx_MRST_deasserted		(0x1 << 10)
#define MDSTATx_LRSTDONE_MASK		(0x1 << 9)
#define MDSTATx_LRSTDONE_yes		(0x0 << 9)
#define MDSTATx_LRSTDONE_no		(0x1 << 9)
#define MDSTATx_LRST_MASK		(0x1 << 8)
#define MDSTATx_LRST_asserted		(0x0 << 8)
#define MDSTATx_LRST_deasserted		(0x1 << 8)
#define MDSTATx_STATE_MASK		(0x3F << 0)
#define MDSTATx_STATE_SwRstDisable	(0x0)
#define MDSTATx_STATE_SyncReset		(0x1)
#define MDSTATx_STATE_Disable		(0x2)
#define MDSTATx_STATE_Enable		(0x3)
#define MDSTATx_STATE_in_transition(x)	(0x4 <= (x) && (x) <= 0x3F)
#define MDCTLx_FORCE_MASK		(0x1 << 31)
#define MDCTLx_FORCE_disabled		(0x0 << 31)
#define MDCTLx_FORCE_enabled		(0x1 << 31)
#define MDCTLx_EMUIHBIE_MASK		(0x1 << 10)
#define MDCTLx_EMUIHBIE_disable		(0x0 << 10)
#define MDCTLx_EMUIHBIE_enable		(0x1 << 10)
#define MDCTLx_EMURSTIE_MASK		(0x1 << 9)
#define MDCTLx_EMURSTIE_disable		(0x0 << 9)
#define MDCTLx_EMURSTIE_enable		(0x1 << 9)
#define MDCTLx_LRST_MASK		(0x1 << 8)
#define MDCTLx_LRST_assert		(0x0 << 8)
#define MDCTLx_LRST_deassert		(0x1 << 8)
#define MDCTLx_STATE_MASK		(0x7 << 0)
#define MDCTLx_STATE_SwRstDisable	(0x0 << 0)
#define MDCTLx_STATE_SyncReset		(0x1 << 0)
#define MDCTLx_STATE_Disable		(0x2 << 0)
#define MDCTLx_STATE_Enable		(0x3 << 0)
#define KICK0R_UNLOCK			0x83E70B13
#define KICK0R_LOCK			0x00000000
#define KICK1R_UNLOCK			0x95A4F1E0
#define KICK1R_LOCK			0x00000000
#define HOST0CFG_BOOTRDY_MASK		(0x1 << 0)
#define HOST0CFG_BOOTRDY_reset		(0x0 << 0)
#define HOST0CFG_BOOTRDY_released	(0x1 << 0)
#define IRAWSTAT_ADDRERR_MASK		(0x1 << 1)
#define IRAWSTAT_ADDRERR_unset		(0x0 << 1)
#define IRAWSTAT_ADDRERR_set		(0x1 << 1)
#define IRAWSTAT_PROTERR_MASK		(0x1 << 0)
#define IRAWSTAT_PROTERR_unset		(0x0 << 0)
#define IRAWSTAT_PROTERR_set		(0x1 << 0)
#define IENSTAT_ADDRERR_MASK		(0x1 << 1)
#define IENSTAT_ADDRERR_unset		(0x0 << 1)
#define IENSTAT_ADDRERR_set		(0x1 << 1)
#define IENSTAT_PROTERR_MASK		(0x1 << 0)
#define IENSTAT_PROTERR_unset		(0x0 << 0)
#define IENSTAT_PROTERR_set		(0x1 << 0)
#define IENSET_ADDRERR_EN_enable	(0x1 << 1)
#define IENSET_PROTERR_EN_enable	(0x1 << 0)
#define IENCLR_ADDRERR_EN_enable	(0x1 << 1)
#define IENCLR_PROTERR_EN_enable	(0x1 << 0)
#define EOI_EOIVECT_MASK		(0xFF << 0)
#define FLTSTAT_ID_MASK			(0xFF << 24)
#define FLTSTAT_MSTID_MASK		(0xFF << 16)
#define FLTSTAT_PRIVID_MASK		(0xF << 9)
#define FLTSTAT_TYPE_MASK		(0x3F << 0)
#define FLTSTAT_TYPE_None		0x0
#define FLTSTAT_TYPE_UserExec		0x1
#define FLTSTAT_TYPE_UserWrite		0x2
#define FLTSTAT_TYPE_UserRead		0x4
#define FLTSTAT_TYPE_SupervisorExec	0x8
#define FLTSTAT_TYPE_SupervisorWrite	0x10
#define FLTSTAT_TYPE_SupervisorRead	0x20
#define CFGCHIP0_PLL_MASTER_LOCK_MASK	(0x1 << 4)
#define CFGCHIP0_PLL_MASTER_LOCK_no	(0x0 << 4)
#define CFGCHIP0_PLL_MASTER_LOCK_yes	(0x1 << 4)
#define CFGCHIP0_EDMA30TCxDBS_MASK(x)	(0x3 << (2*(x)))
#define CFGCHIP0_EDMA30TCxDBS_16B(x)	(0x0 << (2*(x)))
#define CFGCHIP0_EDMA30TCxDBS_32B(x)	(0x1 << (2*(x)))
#define CFGCHIP0_EDMA30TCxDBS_64B(x)	(0x2 << (2*(x)))
#define CFGCHIP3_RMII_SEL_MASK		(0x1 << 8)
#define CFGCHIP3_RMII_SEL_mii		(0x0 << 8)
#define CFGCHIP3_RMII_SEL_rmii		(0x1 << 8)
#define CFGCHIP3_UPP_TX_CLKSRC_MASK	(0x1 << 6)
#define CFGCHIP3_UPP_TX_CLKSRC_asyn3	(0x0 << 6)
#define CFGCHIP3_UPP_TX_CLKSRC_2xTXCLK	(0x1 << 6)
#define CFGCHIP3_PLL1_MASTER_LOCK_MASK	(0x1 << 5)
#define CFGCHIP3_PLL1_MASTER_LOCK_no	(0x0 << 5)
#define CFGCHIP3_PLL1_MASTER_LOCK_yes	(0x1 << 5)
#define CFGCHIP3_ASYNC3_CLKSRC_MASK	(0x1 << 4)
#define CFGCHIP3_ASYNC3_CLKSRC_pll0	(0x0 << 4)
#define CFGCHIP3_ASYNC3_CLKSRC_pll1	(0x1 << 4)
#define CFGCHIP3_PRUEVTSEL_MASK		(0x1 << 3)
#define CFGCHIP3_PRUEVTSEL_normal	(0x0 << 3)
#define CFGCHIP3_PRUEVTSEL_alternate	(0x1 << 3)
#define CFGCHIP3_DIV45PENA_MASK		(0x1 << 2)
#define CFGCHIP3_DIV45PENA_no		(0x0 << 2)
#define CFGCHIP3_DIV45PENA_yes		(0x1 << 2)
#define CFGCHIP3_EMA_CLKSRC_MASK	(0x1 << 1)
#define CFGCHIP3_EMA_CLKSRC_sysclk3	(0x0 << 1)
#define CFGCHIP3_EMA_CLKSRC_pll_out	(0x1 << 1)
#define CFGCHIP4_AMUTECLR0_MASK		(0x1 << 0)
#define CFGCHIP4_AMUTECLR0_none		(0x0 << 0)
#define CFGCHIP4_AMUTECLR0_clr_int	(0x1 << 0)
#define CR_PRHOLDMODE_MASK		(0x1 << 4)
#define CR_PRHOLDMODE_disable		(0x0 << 4)
#define CR_PRHOLDMODE_enable		(0x1 << 4)
#define CR_NESTMODE_MASK		(0x3 << 2)
#define CR_NESTMODE_None		(0x0 << 2)
#define CR_NESTMODE_Individual		(0x1 << 2)
#define CR_NESTMODE_Global		(0x2 << 2)
#define CR_NESTMODE_Manual		(0x3 << 2)
#define GER_ENABLE_MASK			(0x1 << 0)
#define GER_ENABLE_no			(0x0 << 0)
#define GER_ENABLE_yes			(0x1 << 0)
#define GNLR_OVERRIDE_SET		(0x1 << 31)
#define GNLR_NESTLVL_MASK		(0xFF << 0)
#define GNLR_NESTLVL_VAL(x)		((x) << 0)
#define AINTC_IDX_SET			0x00
#define AINTC_IDX_CLR			0x01
#define XIxR_INDEX_MASK			(0x7F << 0)
#define XIxR_INDEX_VAL(x)		((x) << 0)
#define HIEIxR_INDEX_MASK		(0x1 << 0)
#define HIEIxR_INDEX_FIQ		(0x0 << 0)
#define HIEIxR_INDEX_IRQ		(0x1 << 0)
#define VSR_SIZE_MASK			(0xFF << 0)
#define VSR_SIZE_VAL(x)			(((x) >> 2) - 1)
#define GPIR_NONE_MASK			(0x1 << 31)
#define GPIR_NONE_no			(0x0 << 31)
#define GPIR_NONE_yes			(0x1 << 31)
#define GPIR_PRI_INDX_MASK		(0x3FF << 0)
#define SXXRx_WR_X(x)			((x) >> 5)
#define SXXRx_WR_VAL(x)			(0x1 << ((x) & 0x1F))
#define EXRx_WR_X(x)			((x) >> 5)
#define EXRx_WR_VAL(x)			(0x1 << ((x) & 0x1F))
#define CMRx_X(x)			((x) >> 2)
#define CMRx_MASK(x)			(0xFF << (((x) & 0x3) << 3))
#define CMRx_VAL(x,v)			((0xFF & (v)) << (((x) & 0x3) << 3))
#define AINTC_IDX_FIQ			0x00
#define AINTC_IDX_IRQ			0x01
#define HIPIRx_NONE_MASK		(0x1 << 31)
#define HIPIRx_NONE_no			(0x0 << 31)
#define HIPIRx_NONE_yes			(0x1 << 31)
#define HIPIRx_PRI_INDX_MASK		(0x3FF << 0)
#define HINLRx_OVERRIDE_SET		(0x1 << 31)
#define HINLRx_NEST_LVL_MASK		(0x1FF << 0)
#define HIER_IRQ_MASK			(0x1 << 1)
#define HIER_IRQ_disabled		(0x0 << 1)
#define HIER_IRQ_enabled		(0x1 << 1)
#define HIER_FIQ_MASK			(0x1 << 0)
#define HIER_FIQ_disabled		(0x0 << 0)
#define HIER_FIQ_enabled		(0x1 << 0)
#define ICOAR_OADDR_MASK		(0x3FF << 0)
#define ICOAR_OADDR_VAL(x)		((0x3FF & (x)) << 0)
#define ICIMR_AAS_MASK			(0x1 << 6)
#define ICIMR_AAS_disabled		(0x0 << 6)
#define ICIMR_AAS_enabled		(0x1 << 6)
#define ICIMR_SCD_MASK			(0x1 << 5)
#define ICIMR_SCD_disabled		(0x0 << 5)
#define ICIMR_SCD_enabled		(0x1 << 5)
#define ICIMR_ICXRDY_MASK		(0x1 << 4)
#define ICIMR_ICXRDY_disabled		(0x0 << 4)
#define ICIMR_ICXRDY_enabled		(0x1 << 4)
#define ICIMR_ICRRDY_MASK		(0x1 << 3)
#define ICIMR_ICRRDY_disabled		(0x0 << 3)
#define ICIMR_ICRRDY_enabled		(0x1 << 3)
#define ICIMR_ARDY_MASK			(0x1 << 2)
#define ICIMR_ARDY_disabled		(0x0 << 2)
#define ICIMR_ARDY_enabled		(0x1 << 2)
#define ICIMR_NACK_MASK			(0x1 << 1)
#define ICIMR_NACK_disabled		(0x0 << 1)
#define ICIMR_NACK_enabled		(0x1 << 1)
#define ICIMR_AL_MASK			(0x1 << 0)
#define ICIMR_AL_disabled		(0x0 << 0)
#define ICIMR_AL_enabled		(0x1 << 0)
#define ICSTR_SDIR_MASK			(0x1 << 14)
#define ICSTR_SDIR_other		(0x0 << 14)
#define ICSTR_SDIR_slaveTX		(0x1 << 14)
#define ICSTR_SDIR_clear		(0x1 << 14)
#define ICSTR_NACKSNT_MASK		(0x1 << 13)
#define ICSTR_NACKSNT_none		(0x0 << 13)
#define ICSTR_NACKSNT_sent		(0x1 << 13)
#define ICSTR_NACKSNT_clear		(0x1 << 13)
#define ICSTR_BB_MASK			(0x1 << 12)
#define ICSTR_BB_free			(0x0 << 12)
#define ICSTR_BB_busy			(0x1 << 12)
#define ICSTR_BB_clear			(0x1 << 12)
#define ICSTR_RSFULL_MASK		(0x1 << 11)
#define ICSTR_RSFULL_none		(0x0 << 11)
#define ICSTR_RSFULL_overrun		(0x1 << 11)
#define ICSTR_XSMT_MASK			(0x1 << 10)
#define ICSTR_XSMT_underflow		(0x0 << 10)
#define ICSTR_XSMT_none			(0x1 << 10)
#define ICSTR_AAS_MASK			(0x1 << 9)
#define ICSTR_ASS_cleared		(0x0 << 9)
#define ICSTR_ASS_set			(0x1 << 9)
#define ICSTR_AD0_MASK			(0x1 << 8)
#define ICSTR_AD0_cleared		(0x0 << 8)
#define ICSTR_AD0_detected		(0x1 << 8)
#define ICSTR_SCD_MASK			(0x1 << 5)
#define ICSTR_SCD_none			(0x0 << 5)
#define ICSTR_SCD_detected		(0x1 << 5)
#define ICSTR_SCD_clear			(0x1 << 5)
#define ICSTR_ICXRDY_MASK		(0x1 << 4)
#define ICSTR_ICXRDY_none		(0x0 << 4)
#define ICSTR_ICXRDY_ready		(0x1 << 4)
#define ICSTR_ICXRDY_clear		(0x1 << 4)
#define ICSTR_ICRRDY_MASK		(0x1 << 3)
#define ICSTR_ICRRDY_none		(0x0 << 3)
#define ICSTR_ICRRDY_ready		(0x1 << 3)
#define ICSTR_ICRRDY_clear		(0x1 << 3)
#define ICSTR_ARDY_MASK			(0x1 << 2)
#define ICSTR_ARDY_none			(0x0 << 2)
#define ICSTR_ARDY_ready		(0x1 << 2)
#define ICSTR_ARDY_clear		(0x1 << 2)
#define ICSTR_NACK_MASK			(0x1 << 1)
#define ICSTR_NACK_ack			(0x0 << 1)
#define ICSTR_NACK_nack			(0x1 << 1)
#define ICSTR_NACK_clear		(0x1 << 1)
#define ICSTR_AL_MASK			(0x1 << 0)
#define ICSTR_AL_none			(0x0 << 0)
#define ICSTR_AL_lost			(0x1 << 0)
#define ICSTR_AL_clear			(0x1 << 0)
#define ICCLKL_MASK			(0xFFFF << 0)
#define ICCLKH_MASK			(0xFFFF << 0)
#define ICCNT_MASK			(0xFFFF << 0)
#define ICDRR_MASK			(0xFF << 0)
#define ICSAR_SADDR_MASK		(0x3FF << 0)
#define ICSAR_SADDR_VAL(x)		((0x3FF & (x)) << 0)
#define ICDXR_MASK			(0xFF << 0)
#define ICMDR_NACKMOD_MASK		(0x1 << 15)
#define ICMDR_NACKMOD_no		(0x0 << 15)
#define ICMDR_NACKMOD_yes		(0x1 << 15)
#define ICMDR_FREE_MASK			(0x1 << 14)
#define ICMDR_FREE_emu			(0x0 << 14)
#define ICMDR_FREE_run			(0x1 << 14)
#define ICMDR_STT_MASK			(0x1 << 13)
#define ICMDR_STT_no			(0x0 << 13)
#define ICMDR_STT_yes			(0x1 << 13)
#define ICMDR_STP_MASK			(0x1 << 11)
#define ICMDR_STP_no			(0x0 << 11)
#define ICMDR_STP_yes			(0x1 << 11)
#define ICMDR_MST_MASK			(0x1 << 10)
#define ICMDR_MST_slave			(0x0 << 10)
#define ICMDR_MST_master		(0x1 << 10)
#define ICMDR_TRX_MASK			(0x1 << 9)
#define ICMDR_TRX_receiver		(0x0 << 9)
#define ICMDR_TRX_transmitter		(0x1 << 9)
#define ICMDR_XA_MASK			(0x1 << 8)
#define ICMDR_XA_7bit			(0x0 << 8)
#define ICMDR_XA_10bit			(0x1 << 8)
#define ICMDR_RM_MASK			(0x1 << 7)
#define ICMDR_RM_no			(0x0 << 7)
#define ICMDR_RM_yes			(0x1 << 7)
#define ICMDR_DLB_MASK			(0x1 << 6)
#define ICMDR_DLB_disable		(0x0 << 6)
#define ICMDR_DLB_enable		(0x1 << 6)
#define ICMDR_IRS_MASK			(0x1 << 5)
#define ICMDR_IRS_reset			(0x0 << 5)
#define ICMDR_IRS_none			(0x1 << 5)
#define ICMDR_STB_MASK			(0x1 << 4)
#define ICMDR_STB_no			(0x0 << 4)
#define ICMDR_STB_yes			(0x1 << 4)
#define ICMDR_FDF_MASK			(0x1 << 3)
#define ICMDR_FDF_no			(0x0 << 3)
#define ICMDR_FDF_yes			(0x1 << 3)
#define ICMDR_BC_MASK			(0x7 << 0)
#define ICMDR_BC_VAL(x)			((0x7 & (x)) << 0)
#define ICIVR_INTCODE_MASK		(0x7 << 0)
#define ICIVR_INTCODE_none		(0x0 << 0)
#define ICIVR_INTCODE_AL		(0x1 << 0)
#define ICIVR_INTCODE_NACK		(0x2 << 0)
#define ICIVR_INTCODE_ARDY		(0x3 << 0)
#define ICIVR_INTCODE_ICRRDY		(0x4 << 0)
#define ICIVR_INTCODE_ICXRDY		(0x5 << 0)
#define ICIVR_INTCODE_SCD		(0x6 << 0)
#define ICIVR_INTCODE_AAS		(0x7 << 0)
#define ICEMDR_IGNACK_MASK		(0x1 << 1)
#define ICEMDR_IGNACK_no		(0x0 << 1)
#define ICEMDR_IGNACK_yes		(0x1 << 1)
#define ICEMDR_BCM_MASK			(0x1 << 0)
#define ICEMDR_BCM_ack			(0x0 << 0)
#define ICEMDR_BCM_none			(0x1 << 0)
#define ICPSC_IPSC_MASK			(0xFF << 0)
#define ICPSC_IPSC_VAL(x)		((0xFF & (x)) << 0)
#define ICDMAC_TXDMAEN_MASK		(0x1 << 1)
#define ICDMAC_TXDMAEN_disable		(0x0 << 1)
#define ICDMAC_TXDMAEN_enable		(0x1 << 1)
#define ICDMAC_RXDMAEN_MASK		(0x1 << 0)
#define ICDMAC_RXDMAEN_disable		(0x0 << 0)
#define ICDMAC_RXDMAEN_enable		(0x1 << 0)
#define ICPFUNC_PFUNC0_MASK		(0x1 << 0)
#define ICPFUNC_PFUNC0_i2c		(0x0 << 0)
#define ICPFUNC_PFUNC0_gpio		(0x1 << 0)
#define ICPXXX_SCL			0x0
#define ICPXXX_SDA			0x1
#define ICPDIR_PDIRx_MASK(x)		(0x1 << (x))
#define ICPDIR_PDIRx_input(x)		(0x0 << (x))
#define ICPDIR_PDIRx_output(x)		(0x1 << (x))
#define ICPDIO_PDIO_MASK(x)		(0x1 << (x))
#define ICPDIO_PDIO_low(x)		(0x0 << (x))
#define ICPDIO_PDIO_high(x)		(0x1 << (x))
#define ICPDXXX_MASK(x)			(0x1 << (x))
#define ICPDXXX_none(x)			(0x0 << (x))
#define ICPDXXX_assert(x)		(0x1 << (x))
#define EMUMGT_SOFT_MASK		(0x1 << 1)
#define EMUMGT_SOFT_stop		(0x0 << 1)
#define EMUMGT_SOFT_reach		(0x1 << 1)
#define EMUMGT_FREE_MASK		(0x1 << 0)
#define EMUMGT_FREE_soft		(0x0 << 0)
#define EMUMGT_FREE_run			(0x1 << 0)
#define GPINTGPEN_GPENO12_MASK		(0x1 << 17)
#define GPINTGPEN_GPENO12_timer		(0x0 << 17)
#define GPINTGPEN_GPENO12_gpio		(0x1 << 17)
#define GPINTGPEN_GPENI12_MASK		(0x1 << 16)
#define GPINTGPEN_GPENI12_timer		(0x0 << 16)
#define GPINTGPEN_GPENI12_gpio		(0x1 << 16)
#define GPINTGPEN_GPINT12INVO_MASK	(0x1 << 5)
#define GPINTGPEN_GPINT12INVO_rising	(0x0 << 5)
#define GPINTGPEN_GPINT12INVO_falling	(0x1 << 5)
#define GPINTGPEN_GPINT12INVI_MASK	(0x1 << 4)
#define GPINTGPEN_GPINT12INVI_rising	(0x0 << 4)
#define GPINTGPEN_GPINT12INVI_falling	(0x1 << 4)
#define GPINTGPEN_GPINT12ENO_MASK	(0x1 << 1)
#define GPINTGPEN_GPINT12ENO_rising	(0x0 << 1)
#define GPINTGPEN_GPINT12ENO_falling	(0x1 << 1)
#define GPINTGPEN_GPINT12ENI_MASK	(0x1 << 0)
#define GPINTGPEN_GPINT12ENI_rising	(0x0 << 0)
#define GPINTGPEN_GPINT12ENI_falling	(0x1 << 0)
#define GPDATGPDIR_GPDIRO12_MASK	(0x1 << 17)
#define GPDATGPDIR_GPDIRO12_gpio_in	(0x0 << 17)
#define GPDATGPDIR_GPDIRO12_gpio_out	(0x1 << 17)
#define GPDATGPDIR_GPDIRI12_MASK	(0x1 << 16)
#define GPDATGPDIR_GPDIRI12_gpio_in	(0x0 << 16)
#define GPDATGPDIR_GPDIRI12_gpio_out	(0x1 << 16)
#define GPDATGPDIR_GPDATO12_MASK	(0x1 << 1)
#define GPDATGPDIR_GPDATO12_low		(0x0 << 1)
#define GPDATGPDIR_GPDATO12_high	(0x1 << 1)
#define GPDATGPDIR_GPDATI12_MASK	(0x1 << 0)
#define GPDATGPDIR_GPDATI12_low		(0x0 << 0)
#define GPDATGPDIR_GPDATI12_high	(0x1 << 0)
#define TCR_READRSTMODE34_MASK		(0x1 << 26)
#define TCR_READRSTMODE34_none		(0x0 << 26)
#define TCR_READRSTMODE34_reset		(0x1 << 26)
#define TCR_ENAMODE34_MASK		(0x3 << 22)
#define TCR_ENAMODE34_disabled		(0x0 << 22)
#define TCR_ENAMODE34_once		(0x1 << 22)
#define TCR_ENAMODE34_enabled		(0x2 << 22)
#define TCR_ENAMODE34_reload		(0x3 << 22)
#define TCR_CAPEVTMODE12_MASK		(0x3 << 12)
#define TCR_CAPEVTMODE12_rising		(0x0 << 12)
#define TCR_CAPEVTMODE12_falling	(0x1 << 12)
#define TCR_CAPEVTMODE12_both		(0x2 << 12)
#define TCR_CAPMODE12_MASK		(0x1 << 11)
#define TCR_CAPMODE12_none		(0x0 << 11)
#define TCR_CAPMODE12_capture		(0x1 << 11)
#define TCR_READRSTMODE12_MASK		(0x1 << 10)
#define TCR_READRSTMODE12_none		(0x0 << 10)
#define TCR_READRSTMODE12_reset		(0x1 << 10)
#define TCR_TIEN12_MASK			(0x1 << 9)
#define TCR_TIEN12_none			(0x0 << 9)
#define TCR_TIEN12_gated		(0x1 << 9)
#define TCR_CLKSRC12_MASK		(0x1 << 8)
#define TCR_CLKSRC12_internal		(0x0 << 8)
#define TCR_CLKSRC12_external		(0x1 << 8)
#define TCR_ENAMODE12_MASK		(0x3 << 6)
#define TCR_ENAMODE12_disabled		(0x0 << 6)
#define TCR_ENAMODE12_once		(0x1 << 6)
#define TCR_ENAMODE12_enabled		(0x2 << 6)
#define TCR_ENAMODE12_reload		(0x3 << 6)
#define TCR_PWID12_MASK			(0x3 << 4)
#define TCR_PWID12_VAL(x)		((0x3 & (x - 1)) << 4)
#define TCR_CP12_MASK			(0x1 << 3)
#define TCR_CP12_pulse			(0x0 << 3)
#define TCR_CP12_clock			(0x1 << 3)
#define TCR_INVINP12_MASK		(0x1 << 2)
#define TCR_INVINP12_uninverted		(0x0 << 2)
#define TCR_INVINP12_inverted		(0x1 << 2)
#define TCR_INVOUTP12_MASK		(0x1 << 1)
#define TCR_INVOUTP12_uninverted	(0x0 << 1)
#define TCR_INVOUTP12_inverted		(0x1 << 1)
#define TCR_TSTAT12_MASK		(0x1 << 0)
#define TCR_TSTAT12_deasserted		(0x0 << 0)
#define TCR_TSTAT12_asserted		(0x1 << 0)
#define TGCR_TDDR34_MASK		(0xF << 12)
#define TGCR_TDDR34_VAL(x)		((0xF & (x)) << 12)
#define TGCR_PSC34_MASK			(0xF << 8)
#define TGCR_PSC34_VAL(x)		((0xF & (x)) << 8)
#define TGCR_PLUSEN_MASK		(0x1 << 4)
#define TGCR_PLUSEN_unavilable		(0x0 << 4)
#define TGCR_PLUSEN_available		(0x1 << 4)
#define TGCR_TIMMODE_MASK		(0x3 << 2)
#define TGCR_TIMMODE_64bit		(0x0 << 2)
#define TGCR_TIMMODE_unchained		(0x1 << 2)
#define TGCR_TIMMODE_watchdog		(0x2 << 2)
#define TGCR_TIMMODE_chained		(0x3 << 2)
#define TGCR_TIM34RS_MASK		(0x1 << 1)
#define TGCR_TIM34RS_reset		(0x0 << 1)
#define TGCR_TIM34RS_none		(0x1 << 1)
#define TGCR_TIM12RS_MASK		(0x1 << 0)
#define TGCR_TIM12RS_reset		(0x0 << 0)
#define TGCR_TIM12RS_none		(0x1 << 0)
#define WDTCR_WDKEY_MASK		(0xFFFF << 16)
#define WDTCR_WDKEY_VAL(x)		((x) << 16)
#define WDTCR_WDFLAG_MASK		(0x1 << 15)
#define WDTCR_WDFLAG_none		(0x0 << 15)
#define WDTCR_WDFLAG_timeout		(0x1 << 15)
#define WDTCR_WDEN_MASK			(0x1 << 14)
#define WDTCR_WDEN_disable		(0x0 << 14)
#define WDTCR_WDEN_enable		(0x1 << 14)
#define INTCTLSTAT_EVTINTSTAT34_MASK	(0x1 << 19)
#define INTCTLSTAT_EVTINTSTAT34_none	(0x0 << 19)
#define INTCTLSTAT_EVTINTSTAT34_occurred (0x1 << 19)
#define INTCTLSTAT_EVTINTSTAT34_clear	(0x1 << 19)
#define INTCTLSTAT_EVTINTEN34_MASK	(0x1 << 18)
#define INTCTLSTAT_EVTINTEN34_disable	(0x0 << 18)
#define INTCTLSTAT_EVTINTEN34_enable	(0x1 << 18)
#define INTCTLSTAT_PRDINTSTAT34_MASK	(0x1 << 17)
#define INTCTLSTAT_PRDINTSTAT34_none	(0x0 << 17)
#define INTCTLSTAT_PRDINTSTAT34_occurred (0x1 << 17)
#define INTCTLSTAT_PRDINTSTAT34_clear	(0x1 << 17)
#define INTCTLSTAT_PRDINTEN34_MASK	(0x1 << 16)
#define INTCTLSTAT_PRDINTEN34_disable	(0x0 << 16)
#define INTCTLSTAT_PRDINTEN34_enable	(0x1 << 16)
#define INTCTLSTAT_EVTINTSTAT12_MASK	(0x1 << 3)
#define INTCTLSTAT_EVTINTSTAT12_none	(0x0 << 3)
#define INTCTLSTAT_EVTINTSTAT12_occurred (0x1 << 3)
#define INTCTLSTAT_EVTINTSTAT12_clear	(0x1 << 3)
#define INTCTLSTAT_EVTINTEN12_MASK	(0x1 << 2)
#define INTCTLSTAT_EVTINTEN12_disable	(0x0 << 2)
#define INTCTLSTAT_EVTINTEN12_enable	(0x1 << 2)
#define INTCTLSTAT_PRDINTSTAT12_MASK	(0x1 << 1)
#define INTCTLSTAT_PRDINTSTAT12_none	(0x0 << 1)
#define INTCTLSTAT_PRDINTSTAT12_occurred (0x1 << 1)
#define INTCTLSTAT_PRDINTSTAT12_clear	(0x1 << 1)
#define INTCTLSTAT_PRDINTEN12_MASK	(0x1 << 0)
#define INTCTLSTAT_PRDINTEN12_disable	(0x0 << 0)
#define INTCTLSTAT_PRDINTEN12_enable	(0x1 << 0)
#define RBR_DATA_MASK			0xFF
#define THRw				RBRr
#define THR_DATA_MASK			0xFF
#define IER_EDSSI_MASK			(0x1 << 3)
#define IER_EDSSI_disable		(0x0 << 3)
#define IER_EDSSI_enable		(0x1 << 3)
#define IER_ELSI_MASK			(0x1 << 2)
#define IER_ELSI_disable		(0x0 << 2)
#define IER_ELSI_enable			(0x1 << 2)
#define IER_ETBEI_MASK			(0x1 << 1)
#define IER_ETBEI_disable		(0x0 << 1)
#define IER_ETBEI_enable		(0x1 << 1)
#define IER_ERBI_MASK			(0x1 << 0)
#define IER_ERBI_disable		(0x0 << 0)
#define IER_ERBI_enable			(0x1 << 0)
#define IIR_FIFOEN_MASK			(0x3 << 6)
#define IIR_FIFOEN_Non_FIFO		(0x0 << 6)
#define IIR_FIFOEN_enabled		(0x3 << 6)
#define IIR_INTID_MASK			(0x7 << 1)
#define IIR_INTID_thr_empty		(0x1 << 1)
#define IIR_INTID_data_avail		(0x2 << 1)
#define IIR_INTID_line_status		(0x3 << 1)
#define IIR_INTID_timeout		(0x6 << 1)
#define IIR_IPEND_MASK			(0x1 << 0)
#define IIR_IPEND_yes			(0x0 << 0)
#define IIR_IPEND_no			(0x1 << 0)
#define FCRw		IIRr
#define FCR_RXFIFTL_MASK		(0x3 << 6)
#define FCR_RXFIFTL_1byte		(0x0 << 6)
#define FCR_RXFIFTL_4bytes		(0x1 << 6)
#define FCR_RXFIFTL_8bytes		(0x2 << 6)
#define FCR_RXFIFTL_14bytes		(0x3 << 6)
#define FCR_DMAMODE1_MASK		(0x1 << 3)
#define FCR_DMAMODE1_disable		(0x0 << 3)
#define FCR_DMAMODE1_enable		(0x1 << 3)
#define FCR_TXCLR_MASK			(0x1 << 2)
#define FCR_TXCLR_clear			(0x1 << 2)
#define FCR_RXCLR_MASK			(0x1 << 1)
#define FCR_RXCLR_clear			(0x1 << 1)
#define FCR_FIFOEN_MASK			(0x1 << 0)
#define FCR_FIFOEN_No			(0x0 << 0)
#define FCR_FIFOEN_Yes			(0x1 << 0)
#define LCR_DLAB_MASK			(0x1 << 7)
#define LCR_DLAB_rbr_thr_ier		(0x0 << 7)
#define LCR_DLAB_dll_dlh		(0x1 << 7)
#define LCR_BC_MASK			(0x1 << 6)
#define LCR_BC_disabled			(0x0 << 6)
#define LCR_BC_enabled			(0x1 << 6)
#define LCR_SP_MASK			(0x1 << 5)
#define LCR_SP_disabled			(0x0 << 5)
#define LCR_SP_enabled			(0x1 << 5)
#define LCR_EPS_MASK			(0x1 << 4)
#define LCR_EPS_Odd			(0x0 << 4)
#define LCR_EPS_Even			(0x1 << 4)
#define LCR_PEN_MASK			(0x1 << 3)
#define LCR_PEN_No			(0x0 << 3)
#define LCR_PEN_Yes			(0x1 << 3)
#define LCR_STB_MASK			(0x1 << 2)
#define LCR_STB_1STOP			(0x0 << 2)
#define LCR_STB_15_2STOP		(0x1 << 2)
#define LCR_WLS_MASK			(0x3 << 0)
#define LCR_WLS_5bits			(0x0 << 0)
#define LCR_WLS_6bits			(0x1 << 0)
#define LCR_WLS_7bits			(0x2 << 0)
#define LCR_WLS_8bits			(0x3 << 0)
#define MCR_AFE_MASK			(0x1 << 5)
#define MCR_AFE_disabled		(0x0 << 5)
#define MCR_AFE_enabled			(0x1 << 5)
#define MCR_LOOP_MASK			(0x1 << 4)
#define MCR_LOOP_disabled		(0x0 << 4)
#define MCR_LOOP_enabled		(0x1 << 4)
#define MCR_RTS_MASK			(0x1 << 1)
#define MCR_RTS_disabled		(0x0 << 1)
#define MCR_RTS_enabled			(0x1 << 1)
#define LSR_RXFIFOE_MASK		(0x1 << 7)
#define LSR_RXFIFOE_no_error		(0x0 << 7)
#define LSR_RXFIFOE_error		(0x1 << 7)
#define LSR_TEMT_MASK			(0x1 << 6)
#define LSR_TEMT_no			(0x0 << 6)
#define LSR_TEMT_yes			(0x1 << 6)
#define LSR_THRE_MASK			(0x1 << 5)
#define LSR_THRE_no			(0x0 << 5)
#define LSR_THRE_yes			(0x1 << 5)
#define LSR_BI_MASK			(0x1 << 4)
#define LSR_BI_no			(0x0 << 4)
#define LSR_BI_yes			(0x1 << 4)
#define LSR_FE_MASK			(0x1 << 3)
#define LSR_FE_no			(0x0 << 3)
#define LSR_FE_yes			(0x1 << 3)
#define LSR_PE_MASK			(0x1 << 2)
#define LSR_PE_no			(0x0 << 2)
#define LSR_PE_yes			(0x1 << 2)
#define LSR_OE_MASK			(0x1 << 1)
#define LSR_OE_no			(0x0 << 1)
#define LSR_OE_yes			(0x1 << 1)
#define LSR_DR_MASK			(0x1 << 0)
#define LSR_DR_no			(0x0 << 0)
#define LSR_DR_yes			(0x1 << 0)
#define MSR_CD_MASK			(0x1 << 7)
#define MSR_CD_high			(0x0 << 7)
#define MSR_CD_low			(0x1 << 7)
#define MSR_RI_MASK			(0x1 << 6)
#define MSR_RI_high			(0x0 << 6)
#define MSR_RI_low			(0x1 << 6)
#define MSR_DSR_MASK			(0x1 << 5)
#define MSR_DSR_high			(0x0 << 5)
#define MSR_DSR_low			(0x1 << 5)
#define MSR_CTS_MASK			(0x1 << 4)
#define MSR_CTS_high			(0x0 << 4)
#define MSR_CTS_low			(0x1 << 4)
#define MSR_DCD_MASK			(0x1 << 3)
#define MSR_DCD_unchanged		(0x0 << 3)
#define MSR_DCD_changed			(0x1 << 3)
#define MSR_TERI_MASK			(0x1 << 2)
#define MSR_TERI_unchanged		(0x0 << 2)
#define MSR_TERI_changed		(0x1 << 2)
#define MSR_DDSR_MASK			(0x1 << 1)
#define MSR_DDSR_unchanged		(0x0 << 1)
#define MSR_DDSR_changed		(0x1 << 1)
#define MSR_DCTS_MASK			(0x1 << 0)
#define MSR_DCTS_unchanged		(0x0 << 0)
#define MSR_DCTS_changed		(0x1 << 0)
#define SCR_MASK			0xFF
#define PWREMU_UTRST_MASK		(0x1 << 14)
#define PWREMU_UTRST_reset		(0x0 << 14)
#define PWREMU_UTRST_enabled		(0x1 << 14)
#define PWREMU_URRST_MASK		(0x1 << 13)
#define PWREMU_URRST_reset		(0x0 << 13)
#define PWREMU_URRST_enabled		(0x1 << 13)
#define PWREMU_FREE_MASK		(0x1 << 0)
#define PWREMU_FREE_halt		(0x0 << 0)
#define PWREMU_FREE_run			(0x1 << 0)
#define MDR_OSM_SEL_MASK		(0x1 << 0)
#define MDR_OSM_SEL_16x			(0x0 << 0)
#define MDR_OSM_SEL_13x			(0x1 << 0)
#define PSC0_BASE			0x01C10000
#define PLL0_BASE			0x01C11000
#define SYSCFG0_BASE			0x01C14000
#define TIMER0_BASE			0x01C20000
#define TIMER1_BASE			0x01C21000
#define I2C0_BASE			0x01C22000
#define UART0_BASE			0x01C42000
#define UART1_BASE			0x01D0C000
#define UART2_BASE			0x01D0D000
#define PLL1_BASE			0x01E1A000
#define PSC1_BASE			0x01E27000
#define I2C1_BASE			0x01E28000
#define SYSCFG1_BASE			0x01E2C000
#define TIMER2_BASE			0x01F0C000
#define TIMER3_BASE			0x01F0D000
#define AINTC_BASE			0xFFFEE000
#define ARMlocalRAM_BASE		0xFFFF0000
#define ARMLocalRAM_SIZE		0x00002000
