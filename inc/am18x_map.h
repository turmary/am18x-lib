// tary, 23:18 2012/12/16

#ifndef __AM18X_MAP_H__
#define __AM18X_MAP_H__

#ifndef _EXTERN
#define _EXTERN		extern
#endif

#include "am18x_type.h"
#include "am18x_conf.h"

/*----------------------------------------------------------------------------*/
// Peripheral register structures
/*----------------------------------------------------------------------------*/

typedef struct {
	vuint32_t	PROGx_MPSAR;
	vuint32_t	PROGx_MPEAR;
	vuint32_t	PROGx_MPPA;
	uint32_t	RESERVED0;
} MPU_range_t;

typedef struct {
	vuint32_t	REVID;
	vuint32_t	CONFIG;
	uint32_t	RESERVED0[2];
	vuint32_t	IRAWSTAT;
	vuint32_t	IENSTAT;
	vuint32_t	IENSET;
	vuint32_t	IENCLR;
	uint32_t	RESERVED1[56];
	MPU_range_t	FXD;
	uint32_t	RESERVED2[60];
	MPU_range_t	range[1];
	uint32_t	RESERVED3[60];
	vuint32_t	FLTADDRR;
	vuint32_t	FLTSTAT;
	vuint32_t	FLTCLR;
} MPU_con_t;

#define MODULE_NR_PER_PSC	32
typedef enum {
	PSC_EDMA3_0_C0 = MODULE_NR_PER_PSC * 0,
	PSC_EDMA3_0_T0,
	PSC_EDMA3_0_T1,
	PSC_EMIFA,
	PSC_SPI0,
	PSC_MMC_SD0,
	PSC_ARM_INTC,
	PSC_ARM_RAM_ROM,
	PSC_RESERVED0,
	PSC_UART0,
	PSC_SCR0,
	PSC_SCR1,
	PSC_SCR2,
	PSC_PRU,
	PSC_ARM,
	PSC_RESERVED1,
	PSC_EDMA3_1_C0 = MODULE_NR_PER_PSC * 1,
	PSC_USB0,
	PSC_USB1,
	PSC_GPIO,
	PSC_HPI,
	PSC_EMAC,
	PSC_DDR2,
	PSC_MCASP0,
	PSC_SATA,
	PSC_VPIF,
	PSC_SPI1,
	PSC_I2C1,
	PSC_UART1,
	PSC_UART2,
	PSC_MCBSP0,
	PSC_MCBSP1,
	PSC_LCDC,
	PSC_EHRPWM,
	PSC_MMC_SD1,
	PSC_UPP,
	PSC_ECAP,
	PSC_EDMA3_1_T0,
	PSC_RESERVED2,
	PSC_RESERVED3,
	PSC_SCR_F0,
	PSC_SCR_F1,
	PSC_SCR_F2,
	PSC_SCR_F6,
	PSC_SCR_F7,
	PSC_SCR_F8,
	PSC_BR_F7,
	PSC_ON_CHIP_RAM,
} psc_module_t;


typedef struct {
	vcuint32_t	REVID;
	uint32_t	RESERVED0[5];
	vuint32_t	INTEVAL;
	uint32_t	RESERVED1[9];
	vcuint32_t	MERRPR0;
	uint32_t	RESERVED2[3];
	vuint32_t	MERRCR0;
	uint32_t	RESERVED3[3];
	vcuint32_t	PERRPR;
	uint32_t	RESERVED4;
	vuint32_t	PERRCR;
	uint32_t	RESERVED5[45];
#define PTCMD_GO1			(0x1UL << 1)
#define PTCMD_GO0			(0x1UL << 0)
	vuint32_t	PTCMD;
	uint32_t	RESERVED6;
#define PTSTAT_GO1_MASK			(0x1UL << 1)
#define PTSTAT_GO1_no			(0x0UL << 1)
#define PTSTAT_GO1_yes			(0x1UL << 1)
#define PTSTAT_GO0_MASK			(0x1UL << 0)
#define PTSTAT_GO0_no			(0x0UL << 0)
#define PTSTAT_GO0_yes			(0x1UL << 0)
	vcuint32_t	PTSTAT;
	uint32_t	RESERVED7[53];
#define PDSTATx_EMUIHB_MASK		(0x1UL << 11)
#define PDSTATx_EMUIHB_unactive		(0x0UL << 11)
#define PDSTATx_EMUIHB_active		(0x1UL << 11)
#define PDSTATx_PORDONE_MASK		(0x1UL << 9)
#define PDSTATx_PORDONE_no		(0x0UL << 9)
#define PDSTATx_PORDONE_yes		(0x1UL << 9)
#define PDSTATx_POR_MASK		(0x1UL << 8)
#define PDSTATx_POR_asserted		(0x0UL << 8)
#define PDSTATx_POR_deasserted		(0x1UL << 8)
#define PDSTATx_STATE_MASK		(0x1FUL << 0)
#define PDSTATx_STATE_off		(0x0UL << 0)
#define PDSTATx_STATE_on		(0x1UL << 0)
#define PDSTATx_STATE_in_transition(x)	(0x10UL <= (x) && (x) <= 0x1AUL)
	vcuint32_t	PDSTAT0;
	vcuint32_t	PDSTAT1;
	uint32_t	RESERVED8[62];
#define PDCTLx_WAKECNT_MASK		(0xFFUL << 16)
#define PDCTLx_GOOD2ACCESS_MASK		(0xFUL << 20)
#define PDCTLx_ON2GOOD_MASK		(0xFUL << 16)
#define PDCTLx_PDMODE_MASK		(0xFUL << 12)
#define PDCTLx_PDMODE_on		(0xFUL << 12)
#define PDCTLx_EMUIHBIE_MASK		(0x1UL << 9)
#define PDCTLx_EMUIHBIE_disable		(0x0UL << 9)
#define PDCTLx_EMUIHBIE_enable		(0x1UL << 9)
#define PDCTLx_NEXT_MASK		(0x1UL << 0)
#define PDCTLx_NEXT_off			(0x0UL << 0)
#define PDCTLx_NEXT_on			(0x1UL << 0)
	vuint32_t	PDCTL0;
	vuint32_t	PDCTL1;
	uint32_t	RESERVED9[62];
#define PDCFGx_PD_LOCK_MASK		(0x1UL << 3)
#define PDCFGx_PD_LOCK_locked		(0x0UL << 3)
#define PDCFGx_PD_LOCK_unlocked		(0x1UL << 3)
#define PDCFGx_ICEPICK_MASK		(0x1UL << 2)
#define PDCFGx_ICEPICK_unpresent	(0x0UL << 2)
#define PDCFGx_ICEPICK_present		(0x1UL << 2)
#define PDCFGx_RAM_PSM_MASK		(0x1UL << 1)
#define PDCFGx_RAM_PSM_no		(0x0UL << 1)
#define PDCFGx_RAM_PSM_yes		(0x1UL << 1)
#define PDCFGx_ALWAYSON_MASK		(0x1UL << 0)
#define PDCFGx_ALWAYSON_no		(0x0UL << 0)
#define PDCFGx_ALWAYSON_yes		(0x1UL << 0)
	vcuint32_t	PDCFG0;
	vcuint32_t	PDCFG1;
	uint32_t	RESERVED10[254];
#define MDSTATx_EMUIHB_MASK		(0x1UL << 17)
#define MDSTATx_EMUIHB_no		(0x0UL << 17)
#define MDSTATx_EMUIHB_yes		(0x1UL << 17)
#define MDSTATx_EMURST_MASK		(0x1UL << 16)
#define MDSTATx_EMURST_no		(0x0UL << 16)
#define MDSTATx_EMURST_yes		(0x1UL << 16)
#define MDSTATx_MCKOUT_MASK		(0x1UL << 12)
#define MDSTATx_MCKOUT_off		(0x0UL << 12)
#define MDSTATx_MCKOUT_on		(0x1UL << 12)
#define MDSTATx_MRST_MASK		(0x1UL << 10)
#define MDSTATx_MRST_asserted		(0x0UL << 10)
#define MDSTATx_MRST_deasserted		(0x1UL << 10)
#define MDSTATx_LRSTDONE_MASK		(0x1UL << 9)
#define MDSTATx_LRSTDONE_yes		(0x0UL << 9)
#define MDSTATx_LRSTDONE_no		(0x1UL << 9)
#define MDSTATx_LRST_MASK		(0x1UL << 8)
#define MDSTATx_LRST_asserted		(0x0UL << 8)
#define MDSTATx_LRST_deasserted		(0x1UL << 8)
#define MDSTATx_STATE_MASK		(0x3FUL << 0)
#define MDSTATx_STATE_SwRstDisable	(0x0UL)
#define MDSTATx_STATE_SyncReset		(0x1UL)
#define MDSTATx_STATE_Disable		(0x2UL)
#define MDSTATx_STATE_Enable		(0x3UL)
#define MDSTATx_STATE_in_transition(x)	(0x4UL <= (x) && (x) <= 0x3FUL)
	vcuint32_t	MDSTATx[MODULE_NR_PER_PSC];
	uint32_t	RESERVED11[96];
#define MDCTLx_FORCE_MASK		(0x1UL << 31)
#define MDCTLx_FORCE_disabled		(0x0UL << 31)
#define MDCTLx_FORCE_enabled		(0x1UL << 31)
#define MDCTLx_EMUIHBIE_MASK		(0x1UL << 10)
#define MDCTLx_EMUIHBIE_disable		(0x0UL << 10)
#define MDCTLx_EMUIHBIE_enable		(0x1UL << 10)
#define MDCTLx_EMURSTIE_MASK		(0x1UL << 9)
#define MDCTLx_EMURSTIE_disable		(0x0UL << 9)
#define MDCTLx_EMURSTIE_enable		(0x1UL << 9)
#define MDCTLx_LRST_MASK		(0x1UL << 8)
#define MDCTLx_LRST_assert		(0x0UL << 8)
#define MDCTLx_LRST_deassert		(0x1UL << 8)
#define MDCTLx_STATE_MASK		(0x7UL << 0)
#define MDCTLx_STATE_SwRstDisable	(0x0UL << 0)
#define MDCTLx_STATE_SyncReset		(0x1UL << 0)
#define MDCTLx_STATE_Disable		(0x2UL << 0)
#define MDCTLx_STATE_Enable		(0x3UL << 0)
	vuint32_t	MDCTLx[MODULE_NR_PER_PSC];
} PSC_con_t;

typedef struct {
	vcuint32_t	REVID;
	uint32_t	RESERVED0;
	vcuint32_t	DIEIDRx[4];
	vcuint32_t	REVIDR0;
	uint32_t	RESERVED1;
	vcuint32_t	BOOTCFG;
	uint32_t	RESERVED2[5];
#define KICK0R_UNLOCK			0x83E70B13UL
#define KICK0R_LOCK			0x00000000UL
#define KICK1R_UNLOCK			0x95A4F1E0UL
#define KICK1R_LOCK			0x00000000UL
	vuint32_t	KICKxR[2];
#define HOST0CFG_BOOTRDY_MASK		(0x1UL << 0)
#define HOST0CFG_BOOTRDY_reset		(0x0UL << 0)
#define HOST0CFG_BOOTRDY_released	(0x1UL << 0)
	vuint32_t	HOST0CFG;
	uint32_t	RESERVED3[39];
#define IRAWSTAT_ADDRERR_MASK		(0x1UL << 1)
#define IRAWSTAT_ADDRERR_unset		(0x0UL << 1)
#define IRAWSTAT_ADDRERR_set		(0x1UL << 1)
#define IRAWSTAT_PROTERR_MASK		(0x1UL << 0)
#define IRAWSTAT_PROTERR_unset		(0x0UL << 0)
#define IRAWSTAT_PROTERR_set		(0x1UL << 0)
	vuint32_t	IRAWSTAT;
#define IENSTAT_ADDRERR_MASK		(0x1UL << 1)
#define IENSTAT_ADDRERR_unset		(0x0UL << 1)
#define IENSTAT_ADDRERR_set		(0x1UL << 1)
#define IENSTAT_PROTERR_MASK		(0x1UL << 0)
#define IENSTAT_PROTERR_unset		(0x0UL << 0)
#define IENSTAT_PROTERR_set		(0x1UL << 0)
	vcuint32_t	IENSTAT;
#define IENSET_ADDRERR_EN_enable	(0x1UL << 1)
#define IENSET_PROTERR_EN_enable	(0x1UL << 0)
	vuint32_t	IENSET;
#define IENCLR_ADDRERR_EN_enable	(0x1UL << 1)
#define IENCLR_PROTERR_EN_enable	(0x1UL << 0)
	vuint32_t	IENCLR;
#define EOI_EOIVECT_MASK		(0xFFUL << 0)
	vuint32_t	EOI;
	vcuint32_t	FLTADDRR;
#define FLTSTAT_ID_MASK			(0xFFUL << 24)
#define FLTSTAT_MSTID_MASK		(0xFFUL << 16)
#define FLTSTAT_PRIVID_MASK		(0xFUL << 9)
#define FLTSTAT_TYPE_MASK		(0x3FUL << 0)
#define FLTSTAT_TYPE_None		0x0UL
#define FLTSTAT_TYPE_UserExec		0x1UL
#define FLTSTAT_TYPE_UserWrite		0x2UL
#define FLTSTAT_TYPE_UserRead		0x4UL
#define FLTSTAT_TYPE_SupervisorExec	0x8UL
#define FLTSTAT_TYPE_SupervisorWrite	0x10UL
#define FLTSTAT_TYPE_SupervisorRead	0x20UL
	vcuint32_t	FLTSTAT;
	uint32_t	RESERVED4[5];
// TODO, Master Priority X
	vuint32_t	MSTPRIx[3];
	uint32_t	RESERVED5;
	vuint32_t	PINMUXx[20];
	vuint32_t	SUSPSRC;
	vuint32_t	CHIPSIG;
	vuint32_t	CHIPSIG_CLR;
	vuint32_t	CFGCHIPx[5];
} SYSCFG0_con_t;

typedef struct {
	vuint32_t	VTPIO_CTL;
	vuint32_t	DDR_SLEW;
	vuint32_t	DEEPSLEEP;
	vuint32_t	PUPD_ENA;
	vuint32_t	PUPD_SEL;
	vuint32_t	RXACTIVE;
	vuint32_t	PWRDN;
} SYSCFG1_con_t;

typedef struct {
	vcuint32_t	REVID;
	vuint32_t	CR;
	uint32_t	RESERVED0[2];
	vuint32_t	GER;
	uint32_t	RESERVED1[2];
	vuint32_t	GNLR;
#define AINTC_IDX_SET	0x00
#define AINTC_IDX_CLR	0x01
	vuint32_t	SIxR[2];
	vuint32_t	EIxR[2];
	uint32_t	RESERVED2;
	vuint32_t	HIEIxR[2];
	uint32_t	RESERVED3[5];
	vuint32_t	VBR;
	vuint32_t	VSR;
	vuint32_t	VNR;
	uint32_t	RESERVED4[9];
	vuint32_t	GPIR;
	vuint32_t	GPVR;
	uint32_t	RESERVED5[94];
	vuint32_t	SPSRx[4];
	uint32_t	RESERVED6[28];
	vuint32_t	SPCRx[4];
	uint32_t	RESERVED7[28];
	vuint32_t	ESRx[4];
	uint32_t	RESERVED8[28];
	vuint32_t	ECRx[4];
	uint32_t	RESERVED9[28];
	vuint32_t	CMRx[26];
	uint32_t	RESERVED10[294];
	vuint32_t	HIPIRx[2];
	uint32_t	RESERVED11[510];
	vuint32_t	HINLRx[2];
	uint32_t	RESERVED12[254];
	vuint32_t	HIER;
	uint32_t	RESERVED13[63];
	vuint32_t	HIPVRx[2];
} AINTC_con_t;


typedef struct {
	vcuint32_t	REVID;
#define EMUMGT_SOFT_MASK		(0x1UL << 1)
#define EMUMGT_SOFT_stop		(0x0UL << 1)
#define EMUMGT_SOFT_reach		(0x1UL << 1)
#define EMUMGT_FREE_MASK		(0x1UL << 0)
#define EMUMGT_FREE_soft		(0x0UL << 0)
#define EMUMGT_FREE_run			(0x1UL << 0)
	vuint32_t	EMUMGT;
#define GPINTGPEN_GPENO12_MASK		(0x1UL << 17)
#define GPINTGPEN_GPENO12_timer		(0x0UL << 17)
#define GPINTGPEN_GPENO12_gpio		(0x1UL << 17)
#define GPINTGPEN_GPENI12_MASK		(0x1UL << 16)
#define GPINTGPEN_GPENI12_timer		(0x0UL << 16)
#define GPINTGPEN_GPENI12_gpio		(0x1UL << 16)
#define GPINTGPEN_GPINT12INVO_MASK	(0x1UL << 5)
#define GPINTGPEN_GPINT12INVO_rising	(0x0UL << 5)
#define GPINTGPEN_GPINT12INVO_falling	(0x1UL << 5)
#define GPINTGPEN_GPINT12INVI_MASK	(0x1UL << 4)
#define GPINTGPEN_GPINT12INVI_rising	(0x0UL << 4)
#define GPINTGPEN_GPINT12INVI_falling	(0x1UL << 4)
#define GPINTGPEN_GPINT12ENO_MASK	(0x1UL << 1)
#define GPINTGPEN_GPINT12ENO_rising	(0x0UL << 1)
#define GPINTGPEN_GPINT12ENO_falling	(0x1UL << 1)
#define GPINTGPEN_GPINT12ENI_MASK	(0x1UL << 0)
#define GPINTGPEN_GPINT12ENI_rising	(0x0UL << 0)
#define GPINTGPEN_GPINT12ENI_falling	(0x1UL << 0)
	vuint32_t	GPINTGPEN;
#define GPDATGPDIR_GPDIRO12_MASK	(0x1UL << 17)
#define GPDATGPDIR_GPDIRO12_gpio_in	(0x0UL << 17)
#define GPDATGPDIR_GPDIRO12_gpio_out	(0x1UL << 17)
#define GPDATGPDIR_GPDIRI12_MASK	(0x1UL << 16)
#define GPDATGPDIR_GPDIRI12_gpio_in	(0x0UL << 16)
#define GPDATGPDIR_GPDIRI12_gpio_out	(0x1UL << 16)
#define GPDATGPDIR_GPDATO12_MASK	(0x1UL << 1)
#define GPDATGPDIR_GPDATO12_low		(0x0UL << 1)
#define GPDATGPDIR_GPDATO12_high	(0x1UL << 1)
#define GPDATGPDIR_GPDATI12_MASK	(0x1UL << 0)
#define GPDATGPDIR_GPDATI12_low		(0x0UL << 0)
#define GPDATGPDIR_GPDATI12_high	(0x1UL << 0)
	vuint32_t	GPDATGPDIR;
	vuint32_t	TIMx[2];
	vuint32_t	PRDx[2];
#define TCR_READRSTMODE34_MASK		(0x1UL << 26)
#define TCR_READRSTMODE34_none		(0x0UL << 26)
#define TCR_READRSTMODE34_reset		(0x1UL << 26)
#define TCR_ENAMODE34_MASK		(0x3UL << 22)
#define TCR_ENAMODE34_disabled		(0x0UL << 22)
#define TCR_ENAMODE34_once		(0x1UL << 22)
#define TCR_ENAMODE34_enabled		(0x2UL << 22)
#define TCR_ENAMODE34_reload		(0x3UL << 22)
#define TCR_CAPEVTMODE12_MASK		(0x3UL << 12)
#define TCR_CAPEVTMODE12_rising		(0x0UL << 12)
#define TCR_CAPEVTMODE12_falling	(0x1UL << 12)
#define TCR_CAPEVTMODE12_both		(0x2UL << 12)
#define TCR_CAPMODE12_MASK		(0x1UL << 11)
#define TCR_CAPMODE12_none		(0x0UL << 11)
#define TCR_CAPMODE12_capture		(0x1UL << 11)
#define TCR_READRSTMODE12_MASK		(0x1UL << 10)
#define TCR_READRSTMODE12_none		(0x0UL << 10)
#define TCR_READRSTMODE12_reset		(0x1UL << 10)
#define TCR_TIEN12_MASK			(0x1UL << 9)
#define TCR_TIEN12_none			(0x0UL << 9)
#define TCR_TIEN12_gated		(0x1UL << 9)
#define TCR_CLKSRC12_MASK		(0x1UL << 8)
#define TCR_CLKSRC12_internal		(0x0UL << 8)
#define TCR_CLKSRC12_external		(0x1UL << 8)
#define TCR_ENAMODE12_MASK		(0x3UL << 6)
#define TCR_ENAMODE12_disabled		(0x0UL << 6)
#define TCR_ENAMODE12_once		(0x1UL << 6)
#define TCR_ENAMODE12_enabled		(0x2UL << 6)
#define TCR_ENAMODE12_reload		(0x3UL << 6)
#define TCR_PWID12_MASK			(0x3UL << 4)
#define TCR_PWID12_VAL(x)		((0x3UL & (x - 1)) << 4)
#define TCR_CP12_MASK			(0x1UL << 3)
#define TCR_CP12_pulse			(0x0UL << 3)
#define TCR_CP12_clock			(0x1UL << 3)
#define TCR_INVINP12_MASK		(0x1UL << 2)
#define TCR_INVINP12_uninverted		(0x0UL << 2)
#define TCR_INVINP12_inverted		(0x1UL << 2)
#define TCR_INVOUTP12_MASK		(0x1UL << 1)
#define TCR_INVOUTP12_uninverted	(0x0UL << 1)
#define TCR_INVOUTP12_inverted		(0x1UL << 1)
#define TCR_TSTAT12_MASK		(0x1UL << 0)
#define TCR_TSTAT12_unasserted		(0x0UL << 0)
#define TCR_TSTAT12_asserted		(0x1UL << 0)
	vuint32_t	TCR;
#define TGCR_TDDR34_MASK		(0xFUL << 12)
#define TGCR_TDDR34_VAL(x)		((0xFUL & (x)) << 12)
#define TGCR_PSC34_MASK			(0xFUL << 8)
#define TGCR_PSC34_VAL(x)		((0xFUL & (x)) << 8)
#define TGCR_PLUSEN_MASK		(0x1UL << 4)
#define TGCR_PLUSEN_unavilable		(0x0UL << 4)
#define TGCR_PLUSEN_available		(0x1UL << 4)
#define TGCR_TIMMODE_MASK		(0x3UL << 2)
#define TGCR_TIMMODE_64bit		(0x0UL << 2)
#define TGCR_TIMMODE_unchained		(0x1UL << 2)
#define TGCR_TIMMODE_watchdog		(0x2UL << 2)
#define TGCR_TIMMODE_chained		(0x3UL << 2)
#define TGCR_TIM34RS_MASK		(0x1UL << 1)
#define TGCR_TIM34RS_reset		(0x0UL << 1)
#define TGCR_TIM34RS_none		(0x1UL << 1)
#define TGCR_TIM12RS_MASK		(0x1UL << 0)
#define TGCR_TIM12RS_reset		(0x0UL << 0)
#define TGCR_TIM12RS_none		(0x1UL << 0)
	vuint32_t	TGCR;
#define WDTCR_WDKEY_MASK		(0xFFFFUL << 16)
#define WDTCR_WDKEY_VAL(x)		((x) << 16)
#define WDTCR_WDFLAG_MASK		(0x1UL << 15)
#define WDTCR_WDFLAG_none		(0x0UL << 15)
#define WDTCR_WDFLAG_timeout		(0x1UL << 15)
#define WDTCR_WDEN_MASK			(0x1UL << 14)
#define WDTCR_WDEN_disable		(0x0UL << 14)
#define WDTCR_WDEN_enable		(0x1UL << 14)
	vuint32_t	WDTCR;
	uint32_t	RESERVED0[2];
	vuint32_t	RELx[2];
	vuint32_t	CAPx[2];
#define INTCTLSTAT_EVTINTSTAT34_MASK	(0x1UL << 19)
#define INTCTLSTAT_EVTINTSTAT34_none	(0x0UL << 19)
#define INTCTLSTAT_EVTINTSTAT34_occurred (0x1UL << 19)
#define INTCTLSTAT_EVTINTSTAT34_clear	(0x1UL << 19)
#define INTCTLSTAT_EVTINTEN34_MASK	(0x1UL << 18)
#define INTCTLSTAT_EVTINTEN34_disable	(0x0UL << 18)
#define INTCTLSTAT_EVTINTEN34_enable	(0x1UL << 18)
#define INTCTLSTAT_PRDINTSTAT34_MASK	(0x1UL << 17)
#define INTCTLSTAT_PRDINTSTAT34_none	(0x0UL << 17)
#define INTCTLSTAT_PRDINTSTAT34_occurred (0x1UL << 17)
#define INTCTLSTAT_PRDINTSTAT34_clear	(0x1UL << 17)
#define INTCTLSTAT_PRDINTEN34_MASK	(0x1UL << 16)
#define INTCTLSTAT_PRDINTEN34_disable	(0x0UL << 16)
#define INTCTLSTAT_PRDINTEN34_enable	(0x1UL << 16)
#define INTCTLSTAT_EVTINTSTAT12_MASK	(0x1UL << 3)
#define INTCTLSTAT_EVTINTSTAT12_none	(0x0UL << 3)
#define INTCTLSTAT_EVTINTSTAT12_occurred (0x1UL << 3)
#define INTCTLSTAT_EVTINTSTAT12_clear	(0x1UL << 3)
#define INTCTLSTAT_EVTINTEN12_MASK	(0x1UL << 2)
#define INTCTLSTAT_EVTINTEN12_disable	(0x0UL << 2)
#define INTCTLSTAT_EVTINTEN12_enable	(0x1UL << 2)
#define INTCTLSTAT_PRDINTSTAT12_MASK	(0x1UL << 1)
#define INTCTLSTAT_PRDINTSTAT12_none	(0x0UL << 1)
#define INTCTLSTAT_PRDINTSTAT12_occurred (0x1UL << 1)
#define INTCTLSTAT_PRDINTSTAT12_clear	(0x1UL << 1)
#define INTCTLSTAT_PRDINTEN12_MASK	(0x1UL << 0)
#define INTCTLSTAT_PRDINTEN12_disable	(0x0UL << 0)
#define INTCTLSTAT_PRDINTEN12_enable	(0x1UL << 0)
	vuint32_t	INTCTLSTAT;
	uint32_t	RESERVED1[6];
	vuint32_t	CMPx[8];
} TIMER_con_t;

typedef struct {
#define RBR_DATA_MASK			0xFFUL
#define THRw				RBRr
#define THR_DATA_MASK			0xFFUL
	vuint32_t	RBRr;
#define IER_EDSSI_MASK			(0x1UL << 3)
#define IER_EDSSI_disable		(0x0UL << 3)
#define IER_EDSSI_enable		(0x1UL << 3)
#define IER_ELSI_MASK			(0x1UL << 2)
#define IER_ELSI_disable		(0x0UL << 2)
#define IER_ELSI_enable			(0x1UL << 2)
#define IER_ETBEI_MASK			(0x1UL << 1)
#define IER_ETBEI_disable		(0x0UL << 1)
#define IER_ETBEI_enable		(0x1UL << 1)
#define IER_ERBI_MASK			(0x1UL << 0)
#define IER_ERBI_disable		(0x0UL << 0)
#define IER_ERBI_enable			(0x1UL << 0)
	vuint32_t	IER;
#define IIR_FIFOEN_MASK			(0x3UL << 6)
#define IIR_FIFOEN_Non_FIFO		(0x0UL << 6)
#define IIR_FIFOEN_enabled		(0x3UL << 6)
#define IIR_INTID_MASK			(0x7UL << 1)
#define IIR_INTID_thr_empty		(0x1UL << 1)
#define IIR_INTID_data_avail		(0x2UL << 1)
#define IIR_INTID_line_status		(0x3UL << 1)
#define IIR_INTID_timeout		(0x6UL << 1)
#define IIR_IPEND_MASK			(0x1UL << 0)
#define IIR_IPEND_yes			(0x0UL << 0)
#define IIR_IPEND_no			(0x1UL << 0)
#define FCRw		IIRr
#define FCR_RXFIFTL_MASK		(0x3UL << 6)
#define FCR_RXFIFTL_1byte		(0x0UL << 6)
#define FCR_RXFIFTL_4bytes		(0x1UL << 6)
#define FCR_RXFIFTL_8bytes		(0x2UL << 6)
#define FCR_RXFIFTL_14bytes		(0x3UL << 6)
#define FCR_DMAMODE1_MASK		(0x1UL << 3)
#define FCR_DMAMODE1_disable		(0x0UL << 3)
#define FCR_DMAMODE1_enable		(0x1UL << 3)
#define FCR_TXCLR_MASK			(0x1UL << 2)
#define FCR_TXCLR_clear			(0x1UL << 2)
#define FCR_RXCLR_MASK			(0x1UL << 1)
#define FCR_RXCLR_clear			(0x1UL << 1)
#define FCR_FIFOEN_MASK			(0x1UL << 0)
#define FCR_FIFOEN_No			(0x0UL << 0)
#define FCR_FIFOEN_Yes			(0x1UL << 0)
	vuint32_t	IIRr;
#define LCR_DLAB_MASK			(0x1UL << 7)
#define LCR_DLAB_rbr_thr_ier		(0x0UL << 7)
#define LCR_DLAB_dll_dlh		(0x1UL << 7)
#define LCR_BC_MASK			(0x1UL << 6)
#define LCR_BC_disabled			(0x0UL << 6)
#define LCR_BC_enabled			(0x1UL << 6)
#define LCR_SP_MASK			(0x1UL << 5)
#define LCR_SP_disabled			(0x0UL << 5)
#define LCR_SP_enabled			(0x1UL << 5)
#define LCR_EPS_MASK			(0x1UL << 4)
#define LCR_EPS_Odd			(0x0UL << 4)
#define LCR_EPS_Even			(0x1UL << 4)
#define LCR_PEN_MASK			(0x1UL << 3)
#define LCR_PEN_No			(0x0UL << 3)
#define LCR_PEN_Yes			(0x1UL << 3)
#define LCR_STB_MASK			(0x1UL << 2)
#define LCR_STB_1STOP			(0x0UL << 2)
#define LCR_STB_15_2STOP		(0x1UL << 2)
#define LCR_WLS_MASK			(0x3UL << 0)
#define LCR_WLS_5bits			(0x0UL << 0)
#define LCR_WLS_6bits			(0x1UL << 0)
#define LCR_WLS_7bits			(0x2UL << 0)
#define LCR_WLS_8bits			(0x3UL << 0)
	vuint32_t	LCR;
#define MCR_AFE_MASK			(0x1UL << 5)
#define MCR_AFE_disabled		(0x0UL << 5)
#define MCR_AFE_enabled			(0x1UL << 5)
#define MCR_LOOP_MASK			(0x1UL << 4)
#define MCR_LOOP_disabled		(0x0UL << 4)
#define MCR_LOOP_enabled		(0x1UL << 4)
#define MCR_RTS_MASK			(0x1UL << 1)
#define MCR_RTS_disabled		(0x0UL << 1)
#define MCR_RTS_enabled			(0x1UL << 1)
	vuint32_t	MCR;
#define LSR_RXFIFOE_MASK		(0x1UL << 7)
#define LSR_RXFIFOE_no_error		(0x0UL << 7)
#define LSR_RXFIFOE_error		(0x1UL << 7)
#define LSR_TEMT_MASK			(0x1UL << 6)
#define LSR_TEMT_no			(0x0UL << 6)
#define LSR_TEMT_yes			(0x1UL << 6)
#define LSR_THRE_MASK			(0x1UL << 5)
#define LSR_THRE_no			(0x0UL << 5)
#define LSR_THRE_yes			(0x1UL << 5)
#define LSR_BI_MASK			(0x1UL << 4)
#define LSR_BI_no			(0x0UL << 4)
#define LSR_BI_yes			(0x1UL << 4)
#define LSR_FE_MASK			(0x1UL << 3)
#define LSR_FE_no			(0x0UL << 3)
#define LSR_FE_yes			(0x1UL << 3)
#define LSR_PE_MASK			(0x1UL << 2)
#define LSR_PE_no			(0x0UL << 2)
#define LSR_PE_yes			(0x1UL << 2)
#define LSR_OE_MASK			(0x1UL << 1)
#define LSR_OE_no			(0x0UL << 1)
#define LSR_OE_yes			(0x1UL << 1)
#define LSR_DR_MASK			(0x1UL << 0)
#define LSR_DR_no			(0x0UL << 0)
#define LSR_DR_yes			(0x1UL << 0)
	vuint32_t	LSR;
#define MSR_CD_MASK			(0x1UL << 7)
#define MSR_CD_high			(0x0UL << 7)
#define MSR_CD_low			(0x1UL << 7)
#define MSR_RI_MASK			(0x1UL << 6)
#define MSR_RI_high			(0x0UL << 6)
#define MSR_RI_low			(0x1UL << 6)
#define MSR_DSR_MASK			(0x1UL << 5)
#define MSR_DSR_high			(0x0UL << 5)
#define MSR_DSR_low			(0x1UL << 5)
#define MSR_CTS_MASK			(0x1UL << 4)
#define MSR_CTS_high			(0x0UL << 4)
#define MSR_CTS_low			(0x1UL << 4)
#define MSR_DCD_MASK			(0x1UL << 3)
#define MSR_DCD_unchanged		(0x0UL << 3)
#define MSR_DCD_changed			(0x1UL << 3)
#define MSR_TERI_MASK			(0x1UL << 2)
#define MSR_TERI_unchanged		(0x0UL << 2)
#define MSR_TERI_changed		(0x1UL << 2)
#define MSR_DDSR_MASK			(0x1UL << 1)
#define MSR_DDSR_unchanged		(0x0UL << 1)
#define MSR_DDSR_changed		(0x1UL << 1)
#define MSR_DCTS_MASK			(0x1UL << 0)
#define MSR_DCTS_unchanged		(0x0UL << 0)
#define MSR_DCTS_changed		(0x1UL << 0)
	vuint32_t	MSR;
#define SCR_MASK			0xFFUL
	vuint32_t	SCR;
	vuint8_t	DLL;
	uint8_t		RESERVED0[3];
	vuint8_t	DLH;
	uint8_t		RESERVED1[3];
	vuint32_t	REVID[2];
#define PWREMU_UTRST_MASK		(0x1UL << 14)
#define PWREMU_UTRST_reset		(0x0UL << 14)
#define PWREMU_UTRST_enabled		(0x1UL << 14)
#define PWREMU_URRST_MASK		(0x1UL << 13)
#define PWREMU_URRST_reset		(0x0UL << 13)
#define PWREMU_URRST_enabled		(0x1UL << 13)
#define PWREMU_FREE_MASK		(0x1UL << 0)
#define PWREMU_FREE_halt		(0x0UL << 0)
#define PWREMU_FREE_run			(0x1UL << 0)
	vuint32_t	PWREMU_MGMT;
#define MDR_OSM_SEL_MASK		(0x1UL << 0)
#define MDR_OSM_SEL_16x			(0x0UL << 0)
#define MDR_OSM_SEL_13x			(0x1UL << 0)
	vuint32_t	MDR;
} UART_con_t;


/*----------------------------------------------------------------------------*/
// periheral addresses
/*----------------------------------------------------------------------------*/
// AM1808 ARM Microprocessor
// 2.4 Memory Map Summary
#define PSC0_BASE			0x01C10000UL
#define SYSCFG0_BASE			0x01C14000UL
#define TIMER0_BASE			0x01C20000UL
#define TIMER1_BASE			0x01C21000UL
#define UART0_BASE			0x01C42000UL
#define UART1_BASE			0x01D0C000UL
#define UART2_BASE			0x01D0D000UL
#define PSC1_BASE			0x01E27000UL
#define SYSCFG1_BASE			0x01E2C000UL
#define TIMER2_BASE			0x01F0C000UL
#define TIMER3_BASE			0x01F0D000UL


/*----------------------------------------------------------------------------*/
// peripheral names
/*----------------------------------------------------------------------------*/

#ifndef __MEM_REMAP
#ifdef _PSC0
	#define PSC0			((PSC_con_t*)PSC0_BASE)
#endif
#ifdef _PSC1
	#define PSC1			((PSC_con_t*)PSC1_BASE)
#endif
#ifdef _SYSCFG0
	#define SYSCFG0			((SYSCFG0_con_t*)SYSCFG0_BASE)
#endif
#ifdef _SYSCFG1
	#define SYSCFG1			((SYSCFG1_con_t*)SYSCFG1_BASE)
#endif
#ifdef _TIMER0
	#define TIMER0			((TIMER_con_t*)TIMER0_BASE)
#endif
#ifdef _TIMER1
	#define TIMER1			((TIMER_con_t*)TIMER1_BASE)
#endif
#ifdef _TIMER2
	#define TIMER2			((TIMER_con_t*)TIMER2_BASE)
#endif
#ifdef _TIMER3
	#define TIMER3			((TIMER_con_t*)TIMER3_BASE)
#endif
#ifdef _UART0
	#define UART0			((UART_con_t*)UART0_BASE)
#endif
#ifdef _UART1
	#define UART1			((UART_con_t*)UART1_BASE)
#endif
#ifdef _UART2
	#define UART2			((UART_con_t*)UART2_BASE)
#endif

#else//__MEM_REMAP
#ifdef _PSC0
	_EXTERN PSC_con_t		*PSC0;
#endif
#ifdef _PSC1
	_EXTERN PSC_con_t		*PSC1;
#endif
#ifdef _SYSCFG0
	_EXTERN SYSCFG0_con_t		*SYSCFG0;
#endif
#ifdef _SYSCFG1
	_EXTERN SYSCFG1_con_t		*SYSCFG1;
#endif
#ifdef _TIMER0
	_EXTERN TIMER_con_t		*TIMER0
#endif
#ifdef _TIMER1
	_EXTERN TIMER_con_t		*TIMER1
#endif
#ifdef _TIMER2
	_EXTERN TIMER_con_t		*TIMER2
#endif
#ifdef _TIMER3
	_EXTERN TIMER_con_t		*TIMER3
#endif
#ifdef _UART0
	_EXTERN UART_con_t		*UART0;
#endif
#ifdef _UART1
	_EXTERN UART_con_t		*UART1;
#endif
#ifdef _UART2
	_EXTERN UART_con_t		*UART2;
#endif
#endif//__MEM_REMAP


#endif//__AM18X_MAP_H__
// to generate am18x_map_s.h, run the command
// cat am18x_map.h | sed -e "s/\([^0]0x[0-9a-fA-F]\+\)UL/\1/g" | egrep "^#define " >am18x_map_s.h
