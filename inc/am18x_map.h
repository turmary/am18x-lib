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

#define _RS(b,a)	(((b) - (a) - 0x4UL) >> 2)

typedef struct {
#define MPU1_PROGxMPxAR_MASK		0xFFFFFC00UL
#define MPU2_PROGxMPxAR_MASK		0xFFFF0000UL
	vuint32_t	MPSAR;
	vuint32_t	MPEAR;
// n = 0..11
#define PROGxMPPA_AIDn_MASK(n)		(0x1UL << (10 + (n)))
#define PROGxMPPA_AIDn_denied(n)	(0x1UL << (10 + (n)))
#define PROGxMPPA_AIDn_granted(n)	(0x1UL << (10 + (n)))
	vuint32_t	MPPA;
	uint32_t	RESERVED0;
} MPU_range_t;

typedef struct {
#define MPU_REVID			0x4E810101UL
	vcuint32_t	REVID;
#define CONFIG_ADDR_WIDTH_MASK		(0xFFUL << 24)
#define CONFIG_NUM_FIXED_MASK		(0xFUL << 20)
#define CONFIG_NUM_PROG_MASK		(0xFUL << 16)
#define CONFIG_NUM_AIDS_MASK		(0xFUL << 12)
#define CONFIG_ASSUME_ALLOWED_MASK	(0x1UL << 0)
#define CONFIG_ASSUME_ALLOWED_no	(0x0UL << 0)
#define CONFIG_ASSUME_ALLOWED_yes	(0x1UL << 0)
	vcuint32_t	CONFIG;
	uint32_t	RESERVED0[_RS(0x010,0x004)];
	vuint32_t	IRAWSTAT;
	vuint32_t	IENSTAT;
	vuint32_t	IENSET;
	vuint32_t	IENCLR;
	uint32_t	RESERVED1[_RS(0x100,0x01C)];
	// only valid in MPU2
#define FXD_MPSAR_VAL			0xB0000000UL
#define FXD_MPEAR_VAL			0xB0007FFFUL
	MPU_range_t	FXD;
	uint32_t	RESERVED2[_RS(0x200,0x10C)];
	MPU_range_t	PROGx[1];
	uint32_t	RESERVED3[_RS(0x300,0x20C)];
	vcuint32_t	FLTADDRR;
#define FLTSTAT_MSTID_MASK		(0xFFUL << 16)
#define FLTSTAT_PRIVID_MASK		(0xFUL << 9)
#define FLTSTAT_TYPE_MASK		(0x3FUL << 0)
#define FLTSTAT_TYPE_NoFault		(0x0UL << 0)
#define FLTSTAT_TYPE_UserExecute	(0x1UL << 0)
#define FLTSTAT_TYPE_UserWrite		(0x2UL << 0)
#define FLTSTAT_TYPE_UserRead		(0x4UL << 0)
#define FLTSTAT_TYPE_SupervisorExecute	(0x8UL << 0)
#define FLTSTAT_TYPE_SupervisorWrite	(0x10UL << 0)
#define FLTSTAT_TYPE_CacheWriteBack	(0x12UL << 0)
#define FLTSTAT_TYPE_SupervisorRead	(0x20UL << 0)
#define FLTSTAT_TYPE_CacheLineFill	(0x3FUL << 0)
	vcuint32_t	FLTSTAT;
	vcuint32_t	FLTCLR;
} MPU_con_t;

enum {
	BIT_DEF(PROGxMPPA,9,AIDX,denied,granted),
	BIT_DEF(PROGxMPPA,5,SR,denied,allowed),
	BIT_DEF(PROGxMPPA,4,SW,denied,allowed),
	BIT_DEF(PROGxMPPA,3,SX,denied,allowed),
	BIT_DEF(PROGxMPPA,2,UR,denied,allowed),
	BIT_DEF(PROGxMPPA,1,UW,denied,allowed),
	BIT_DEF(PROGxMPPA,0,UX,denied,allowed),
	BIT_DEF(FLTCLR,0,CLEAR,none,fault),
};

typedef struct {
#define PLL0_REVID			0x44813C00UL
#define PLL1_REVID			0x44814400UL
	vcuint32_t	REVID;
	uint32_t	RESERVED0[_RS(0xE4,0x0)];
#define RSTYPE_PLLSWRST_MASK		(0x1UL << 2)
#define RSTYPE_PLLSWRST_no		(0x0UL << 2)
#define RSTYPE_PLLSWRST_yes		(0x1UL << 2)
#define RSTYPE_XWRST_MASK		(0x1UL << 1)
#define RSTYPE_XWRST_no			(0x0UL << 1)
#define RSTYPE_XWRST_yes		(0x1UL << 1)
#define RSTYPE_POR_MASK			(0x1UL << 0)
#define RSTYPE_POR_no			(0x0UL << 0)
#define RSTYPE_POR_yes			(0x1UL << 0)
	vcuint32_t	RSTYPE;
#define RSCTRL_SWRST_MASK		(0x1UL << 16)
#define RSCTRL_SWRST_yes		(0x0UL << 16)
#define RSCTRL_SWRST_no			(0x1UL << 16)
#define RSCTRL_KEY_MASK			(0xFFFFUL << 0)
#define RSCTRL_KEY_locked		(0x3UL << 0)
#define RSCTRL_KEY_unlocked		(0xCUL << 0)
#define RSCTRL_KEY_unlock		(0x5A69UL << 0)
	vuint32_t	RSCTRL;
	uint32_t	RESERVED1[_RS(0x100,0xE8)];
#define PLLCTL_EXTCLKSRC_MASK		(0x1UL << 9)
#define PLLCTL_EXTCLKSRC_oscin		(0x0UL << 9)
#define PLLCTL_EXTCLKSRC_PLL1sysclk3	(0x1UL << 9)
#define PLLCTL_CLKMODE_MASK		(0x1UL << 8)
#define PLLCTL_CLKMODE_crystal		(0x0UL << 8)
#define PLLCTL_CLKMODE_wave		(0x1UL << 8)
#define PLLCTL_PLLENSRC_MASK		(0x1UL << 5)
#define PLLCTL_PLLENSRC_cleared		(0x0UL << 5)
#define PLLCTL_PLLENSRC_none		(0x1UL << 5)
#define PLLCTL_PLLRST_MASK		(0x1UL << 3)
#define PLLCTL_PLLRST_asserted		(0x0UL << 3)
#define PLLCTL_PLLRST_deasserted	(0x1UL << 3)
#define PLLCTL_PLLPWRDN_MASK		(0x1UL << 1)
#define PLLCTL_PLLPWRDN_no		(0x0UL << 1)
#define PLLCTL_PLLPWRDN_yes		(0x1UL << 1)
#define PLLCTL_PLLEN_MASK		(0x1UL << 0)
#define PLLCTL_PLLEN_no			(0x0UL << 0)
#define PLLCTL_PLLEN_yes		(0x1UL << 0)
	vuint32_t	PLLCTL;
#define OCSEL_OCSRC_MASK		(0x1FUL << 0)
#define OCSEL_OCSRC_oscin		(0x14UL << 0)
// PLL0 x = 1..7
// PLL1 x = 1..3
#define OCSEL_OCSRC_PLLsysclkx(x)	((0x16UL + (x)) << 0)
#define OCSEL_OCSRC_PLL1obsclk		(0x1EUL << 0)
#define OCSEL_OCSRC_Disabled		(0x1FUL << 0)
	vuint32_t	OCSEL;
	uint32_t	RESERVED2[_RS(0x110,0x104)];
#define PLLM_MASK			(0x1FUL << 0)
#define PLLM_WR(m)			(((m) - 0x1UL) << 0)
	vuint32_t	PLLM;
// XXXDIVx include PREDIV, PLLDIV1, PLLDIV2, PLLDIV3,
//		PLLDIV4, PLLDIV5, PLLDIV6, PLLDIV7,
//		OSCDIV, POSTDIV
#define XXXDIVx_DxEN_MASK		(0x1UL << 15)
#define XXXDIVx_DxEN_disable		(0x0UL << 15)
#define XXXDIVx_DxEN_enable		(0x1UL << 15)
#define XXXDIVx_RATIO_MASK		(0x1FUL << 0)
#define XXXDIVx_RATIO_WR(r)		(((r) - 0x1UL) << 0)
	vuint32_t	PREDIV;
// PLLDIVxA_IDX include PLLDIV1, PLLDIV2, PLLDIV3
#define PLLDIVxA_IDX_1			0x0
#define PLLDIVxA_IDX_2			0x1
#define PLLDIVxA_IDX_3			0x2
	vuint32_t	PLLDIVxA[3];
	vuint32_t	OSCDIV;
	vuint32_t	POSTDIV;
	uint32_t	RESERVED3[_RS(0x138,0x128)];
#define PLLCMD_GOSET_MASK		(0x1UL << 0)
#define PLLCMD_GOSET_clear		(0x0UL << 0)
#define PLLCMD_GOSET_initiate		(0x1UL << 0)
	vuint32_t	PLLCMD;
#define PLLSTAT_STABLE_MASK		(0x1UL << 2)
#define PLLSTAT_STABLE_no		(0x0UL << 2)
#define PLLSTAT_STABLE_yes		(0x1UL << 2)
#define PLLSTAT_GOSTAT_MASK		(0x1UL << 0)
#define PLLSTAT_GOSTAT_done		(0x0UL << 0)
#define PLLSTAT_GOSTAT_in_progress	(0x1UL << 0)
	vcuint32_t	PLLSTAT;
// PLL0 x = 1..7
// PLL1 x = 1..3
#define ALNCTL_ALNx_MASK(x)		(0x1UL << ((x) - 1))
#define ALNCTL_ALNx_no			(0x0UL << ((x) - 1))
#define ALNCTL_ALNx_yes			(0x1UL << ((x) - 1))
	vuint32_t	ALNCTL;
// PLL0 x = 1..7
// PLL1 x = 1..3
#define DCHANGE_SYSx_MASK(x)		(0x1UL << ((x) - 1))
#define DCHANGE_SYSx_none		(0x0UL << ((x) - 1))
#define DCHANGE_SYSx_modified		(0x1UL << ((x) - 1))
	vcuint32_t	DCHANGE;
#define CKEN_OBSEN_MASK			(0x1UL << 1)
#define CKEN_OBSEN_disable		(0x0UL << 1)
#define CKEN_OBSEN_enable		(0x1UL << 1)
#define CKEN_AUXEN_MASK			(0x1UL << 0)
#define CKEN_AUXEN_disable		(0x0UL << 0)
#define CKEN_AUXEN_enable		(0x1UL << 0)
	vuint32_t	CKEN;
#define CKSTAT_OBSEN_MASK		(0x1UL << 1)
#define CKSTAT_OBSEN_off		(0x0UL << 1)
#define CKSTAT_OBSEN_on			(0x1UL << 1)
#define CKSTAT_AUXEN_MASK		(0x1UL << 0)
#define CKSTAT_AUXEN_off		(0x0UL << 0)
#define CKSTAT_AUXEN_on			(0x1UL << 0)
	vcuint32_t	CKSTAT;
// PLL0 x = 1..7
// PLL1 x = 1..3
#define SYSTAT_SYSxON_MASK(X)		(0x1UL << ((x) - 1))
#define SYSTAT_SYSxON_off		(0x0UL << ((x) - 1))
#define SYSTAT_SYSxON_on		(0x1UL << ((x) - 1))
	vcuint32_t	SYSTAT;
	uint32_t	RESERVED4[_RS(0x160,0x150)];
// PLLDIVxB_IDX include PLLDIV4, PLLDIV5, PLLDIV6, PLLDIV7
#define PLLDIVxB_IDX_4			0x0
#define PLLDIVxB_IDX_5			0x1
#define PLLDIVxB_IDX_6			0x2
#define PLLDIVxB_IDX_7			0x3
	vuint32_t	PLLDIVxB[4];
	uint32_t	RESERVED5[_RS(0x1F0,0x16C)];
	vuint32_t	EMUCNTx[2];
} PLL_con_t;

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
#define PSC_REVID			0x44825A00UL
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

enum {
	MSTPRI_ARM_I,
	MSTPRI_ARM_D,
	MSTPRI_Reserved0,
	MSTPRI_Reserved1,

	MSTPRI_UPP,
	MSTPRI_STAT,
	MSTPRI_Reserved2,
	MSTPRI_Reserved3,

	MSTPRI_PRU0,
	MSTPRI_PRU1,
	MSTPRI_EDMA30TC0,
	MSTPRI_EDMA30TC1,

	MSTPRI_EDMA31TC0,
	MSTPRI_Reserved4,
	MSTPRI_VPIF_DMA_0,
	MSTPRI_VPIF_DMA_1,

	MSTPRI_EMAC,
	MSTPRI_Reserved5,
	MSTPRI_USB0CFG,
	MSTPRI_USB0CDMA,

	MSTPRI_Reserved6,
	MSTPRI_UHPI,
	MSTPRI_USB1,
	MSTPRI_LCDC,
};

typedef struct {
#define SYSCFG0_REVID			0x4E840102UL
	vcuint32_t	REVID;
	uint32_t	RESERVED0;
	vcuint32_t	DIEIDRx[4];
	vcuint32_t	REVIDR0;
	uint32_t	RESERVED1;
#define BOOTCFG_BOOTMODE_MASK		0x001FUL
#define BOOTCFG_BOOTMODE_I2C0EEPROM	0x00UL
#define BOOTCFG_BOOTMODE_I2C0SLAVE	0x01UL
#define BOOTCFG_BOOTMODE_NOR		0x02UL
#define BOOTCFG_BOOTMODE_HPI		0x04UL
#define BOOTCFG_BOOTMODE_I2C1EEPROM	0x06UL
#define BOOTCFG_BOOTMODE_I2C1SLAVE	0x07UL
#define BOOTCFG_BOOTMODE_SPI0EEPROM	0x08UL
#define BOOTCFG_BOOTMODE_SPI1EEPROM	0x09UL
#define BOOTCFG_BOOTMODE_SPI0FLASH	0x0AUL
#define BOOTCFG_BOOTMODE_SPI1FLASH	0x0CUL
#define BOOTCFG_BOOTMODE_NAND8		0x0EUL
#define BOOTCFG_BOOTMODE_NAND16		0x10UL
#define BOOTCFG_BOOTMODE_SPI0SLAVE	0x12UL
#define BOOTCFG_BOOTMODE_SPI1SLAVE	0x13UL
#define BOOTCFG_BOOTMODE_UART2		0x14UL
#define BOOTCFG_BOOTMODE_UART0		0x16UL
#define BOOTCFG_BOOTMODE_UART1		0x17UL
#define BOOTCFG_BOOTMODE_EMU		0x1EUL
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
	vcuint32_t	FLTSTAT;
	uint32_t	RESERVED4[5];
// Master Priority X
// x = 0..23
#define MSTPRIx_IDX(x)			((x) >> 3)
#define MSTPRIx_MASK(x)			(0x7UL << (((x) & 0x7UL) << 2))
	vuint32_t	MSTPRIx[3];
	uint32_t	RESERVED5;
	vuint32_t	PINMUXx[20];
	vuint32_t	SUSPSRC;
#define CHIPSIG_X_MASK(i)		(0x1UL << (i))
#define CHIPSIG_X_assert(i)		(0x1UL << (i))
#define CHIPSIG_X_clear(i)		(0x1UL << (i))
	vuint32_t	CHIPSIG;
	vuint32_t	CHIPSIG_CLR;
#define CFGCHIP0_PLL_MASTER_LOCK_MASK	(0x1UL << 4)
#define CFGCHIP0_PLL_MASTER_LOCK_no	(0x0UL << 4)
#define CFGCHIP0_PLL_MASTER_LOCK_yes	(0x1UL << 4)
// x = 0..1
#define CFGCHIP0_EDMA30TCxDBS_MASK(x)	(0x3UL << (2*(x)))
#define CFGCHIP0_EDMA30TCxDBS_16B(x)	(0x0UL << (2*(x)))
#define CFGCHIP0_EDMA30TCxDBS_32B(x)	(0x1UL << (2*(x)))
#define CFGCHIP0_EDMA30TCxDBS_64B(x)	(0x2UL << (2*(x)))
	vuint32_t	CFGCHIP0;
#define CFGCHIP1_EDMA31TC0DBS_MASK	(0x3UL << 13)
#define CFGCHIP1_EDMA31TC0DBS_16B	(0x0UL << 13)
#define CFGCHIP1_EDMA31TC0DBS_32B	(0x1UL << 13)
#define CFGCHIP1_EDMA31TC0DBS_64B	(0x2UL << 13)
	vuint32_t	CFGCHIP1;
	vuint32_t	CFGCHIP2;
#define CFGCHIP3_RMII_SEL_MASK		(0x1UL << 8)
#define CFGCHIP3_RMII_SEL_mii		(0x0UL << 8)
#define CFGCHIP3_RMII_SEL_rmii		(0x1UL << 8)
#define CFGCHIP3_UPP_TX_CLKSRC_MASK	(0x1UL << 6)
#define CFGCHIP3_UPP_TX_CLKSRC_asyn3	(0x0UL << 6)
#define CFGCHIP3_UPP_TX_CLKSRC_2xTXCLK	(0x1UL << 6)
#define CFGCHIP3_PLL1_MASTER_LOCK_MASK	(0x1UL << 5)
#define CFGCHIP3_PLL1_MASTER_LOCK_no	(0x0UL << 5)
#define CFGCHIP3_PLL1_MASTER_LOCK_yes	(0x1UL << 5)
#define CFGCHIP3_ASYNC3_CLKSRC_MASK	(0x1UL << 4)
#define CFGCHIP3_ASYNC3_CLKSRC_pll0	(0x0UL << 4)
#define CFGCHIP3_ASYNC3_CLKSRC_pll1	(0x1UL << 4)
#define CFGCHIP3_PRUEVTSEL_MASK		(0x1UL << 3)
#define CFGCHIP3_PRUEVTSEL_normal	(0x0UL << 3)
#define CFGCHIP3_PRUEVTSEL_alternate	(0x1UL << 3)
#define CFGCHIP3_DIV45PENA_MASK		(0x1UL << 2)
#define CFGCHIP3_DIV45PENA_no		(0x0UL << 2)
#define CFGCHIP3_DIV45PENA_yes		(0x1UL << 2)
#define CFGCHIP3_EMA_CLKSRC_MASK	(0x1UL << 1)
#define CFGCHIP3_EMA_CLKSRC_sysclk3	(0x0UL << 1)
#define CFGCHIP3_EMA_CLKSRC_pll_out	(0x1UL << 1)
	vuint32_t	CFGCHIP3;
#define CFGCHIP4_AMUTECLR0_MASK		(0x1UL << 0)
#define CFGCHIP4_AMUTECLR0_none		(0x0UL << 0)
#define CFGCHIP4_AMUTECLR0_clr_int	(0x1UL << 0)
	vuint32_t	CFGCHIP4;
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

typedef enum {
	AINTC_COMMTX = 0,		// 0
	AINTC_COMMRX,
	AINTC_NINT,
	AINTC_PRU_EVTOUT0,
	AINTC_PRU_EVTOUT1,

	AINTC_PRU_EVTOUT2,
	AINTC_PRU_EVTOUT3,
	AINTC_PRU_EVTOUT4,
	AINTC_PRU_EVTOUT5,
	AINTC_PRU_EVTOUT6,

	AINTC_PRU_EVTOUT7,		// 10
	AINTC_EDMA3_0_CC0_INT0,
	AINTC_EDMA3_0_CC0_ERRINT,
	AINTC_EDMA3_0_TC0_ERRINT,
	AINTC_EMIFA_INT,

	AINTC_IIC0_INT,
	AINTC_MMCSD0_INT0,
	AINTC_MMCSD0_INT1,
	AINTC_PSC0_ALLINT,
	AINTC_RTC_IRQS_1_0,

	AINTC_SPI0_INT,			// 20
	AINTC_T64P0_TINT12,
	AINTC_T64P0_TINT32,
	AINTC_T64P1_TINT12,
	AINTC_T64P1_TINT34,

	AINTC_UART0_INT,
	AINTC_RESERVED0,
	AINTC_PROTERR,
	AINTC_SYSCFG_CHIPINT0,
	AINTC_SYSCFG_CHIPINT1,

	AINTC_SYSCFG_CHIPINT2,		// 30
	AINTC_SYSCFG_CHIPINT3,
	AINTC_EDMA3_0_TC1_ERRINT,
	AINTC_EMAC_C0RXTHRESH,
	AINTC_EMAC_C0RX,

	AINTC_EMAC_C0TX,
	AINTC_EMAC_C0MISC,
	AINTC_EMAC_C1RXTHRESH,
	AINTC_EMAC_C1RX,
	AINTC_EMAC_C1TX,

	AINTC_EMAC_C1MISC,		// 40
	AINTC_DDR2_MEMERR,
	AINTC_GPIO_B0INT,
	AINTC_GPIO_B1INT,
	AINTC_GPIO_B2INT,

	AINTC_GPIO_B3INT,
	AINTC_GPIO_B4INT,
	AINTC_GPIO_B5INT,
	AINTC_GPIO_B6INT,
	AINTC_GPIO_B7INT,

	AINTC_GPIO_B8INT,		// 50
	AINTC_IIC1_INT,
	AINTC_LCDC_INT,
	AINTC_UART_INT1,
	AINTC_MCASP_INT,

	AINTC_PSC1_ALLINT,
	AINTC_SPI1_INT,
	AINTC_UHPI_ARMINT,
	AINTC_USB0_INT,
	AINTC_USB1_HCINT,

	AINTC_USB1_R_WAKEUP,		// 60
	AINTC_UART2_INT,
	AINTC_RESERVED1,
	AINTC_EHRPWM0,
	AINTC_EHRPWM0TZ,

	AINTC_EHRPWM1,
	AINTC_EHRPWM1TZ,
	AINTC_SATA_INT,
	AINTC_T64P2_ALL,
	AINTC_ECAP0,

	AINTC_ECAP1,			// 70
	AINTC_ECAP2,
	AINTC_MMCSD1_INT0,
	AINTC_MMCSD1_INT1,
	AINTC_T64P2_CMPINT0,

	AINTC_T64P2_CMPINT1,
	AINTC_T64P2_CMPINT2,
	AINTC_T64P2_CMPINT3,
	AINTC_T64P2_CMPINT4,
	AINTC_T64P2_CMPINT5,

	AINTC_T64P2_CMPINT6,		// 80
	AINTC_T64P2_CMPINT7,
	AINTC_T64P3_CMPINT0,
	AINTC_T64P3_CMPINT1,
	AINTC_T64P3_CMPINT2,

	AINTC_T64P3_CMPINT3,
	AINTC_T64P3_CMPINT4,
	AINTC_T64P3_CMPINT5,
	AINTC_T64P3_CMPINT6,
	AINTC_T64P3_CMPINT7,

	AINTC_ARMCLKSTOPREQ,		// 90
	AINTC_uPP_AlLINT,
	AINTC_VPIF_ALLINT,
	AINTC_EDMA3_1_CC0_INT0,
	AINTC_EDMA3_1_CC0_ERRINT,

	AINTC_EDMA3_1_TC0_ERRINT,
	AINTC_T64P3_ALL,
	AINTC_MCBSP0_RINT,
	AINTC_MCBSP0_XINT,
	AINTC_MCBSP1_RINT,

	AINTC_MCBSP1_XINT,		// 100
	AINTC_ASSIGN_CNT,
} AINTC_assign_t;

typedef struct {
	vcuint32_t	REVID;
#define CR_PRHOLDMODE_MASK		(0x1UL << 4)
#define CR_PRHOLDMODE_disable		(0x0UL << 4)
#define CR_PRHOLDMODE_enable		(0x1UL << 4)
#define CR_NESTMODE_MASK		(0x3UL << 2)
#define CR_NESTMODE_None		(0x0UL << 2)
#define CR_NESTMODE_Individual		(0x1UL << 2)
#define CR_NESTMODE_Global		(0x2UL << 2)
#define CR_NESTMODE_Manual		(0x3UL << 2)
	vuint32_t	CR;
	uint32_t	RESERVED0[2];
#define GER_ENABLE_MASK			(0x1UL << 0)
#define GER_ENABLE_no			(0x0UL << 0)
#define GER_ENABLE_yes			(0x1UL << 0)
	vuint32_t	GER;
	uint32_t	RESERVED1[2];
#define GNLR_OVERRIDE_SET		(0x1UL << 31)
#define GNLR_NESTLVL_MASK		(0xFFUL << 0)
#define GNLR_NESTLVL_VAL(x)		((x) << 0)
	vuint32_t	GNLR;
// AINTC_IDX_XX include SIxR, EIxR, HIEIxR
#define AINTC_IDX_SET			0x00
#define AINTC_IDX_CLR			0x01
#define XIxR_INDEX_MASK			(0x7FUL << 0)
#define XIxR_INDEX_VAL(x)		((x) << 0)
	vuint32_t	SIxR[2];
	vuint32_t	EIxR[2];
	uint32_t	RESERVED2;
#define HIEIxR_INDEX_MASK		(0x1UL << 0)
#define HIEIxR_INDEX_FIQ		(0x0UL << 0)
#define HIEIxR_INDEX_IRQ		(0x1UL << 0)
	vuint32_t	HIEIxR[2];
	uint32_t	RESERVED3[5];
	vuint32_t	VBR;
#define VSR_SIZE_MASK			(0xFFUL << 0)
#define VSR_SIZE_VAL(x)			(((x) >> 2) - 1)
	vuint32_t	VSR;
	vuint32_t	VNR;
	uint32_t	RESERVED4[9];
#define GPIR_NONE_MASK			(0x1UL << 31)
#define GPIR_NONE_no			(0x0UL << 31)
#define GPIR_NONE_yes			(0x1UL << 31)
#define GPIR_PRI_INDX_MASK		(0x3FFUL << 0)
	vcint32_t	GPIR;
	vuint32_t	GPVR;
	uint32_t	RESERVED5[94];
#define SXXRx_WR_X(x)			((x) >> 5)
#define SXXRx_WR_VAL(x)			(0x1UL << ((x) & 0x1F))
	vuint32_t	SRSRx[4];
	uint32_t	RESERVED6[28];
	vuint32_t	SECRx[4];
	uint32_t	RESERVED7[28];
#define EXRx_WR_X(x)			((x) >> 5)
#define EXRx_WR_VAL(x)			(0x1UL << ((x) & 0x1F))
	vuint32_t	ESRx[4];
	uint32_t	RESERVED8[28];
	vuint32_t	ECRx[4];
	uint32_t	RESERVED9[28];
#define CMRx_X(x)			((x) >> 2)
#define CMRx_MASK(x)			(0xFFUL << (((x) & 0x3UL) << 3))
#define CMRx_VAL(x,v)			((0xFFUL & (v)) << (((x) & 0x3UL) << 3))
	vuint32_t	CMRx[26];
	uint32_t	RESERVED10[294];
// AINTC_IDX_XXX include HIPIRx, HINLRx, HIPVRx
#define AINTC_IDX_FIQ			0x00
#define AINTC_IDX_IRQ			0x01
#define HIPIRx_NONE_MASK		(0x1UL << 31)
#define HIPIRx_NONE_no			(0x0UL << 31)
#define HIPIRx_NONE_yes			(0x1UL << 31)
#define HIPIRx_PRI_INDX_MASK		(0x3FFUL << 0)
	vuint32_t	HIPIRx[2];
	uint32_t	RESERVED11[510];
#define HINLRx_OVERRIDE_SET		(0x1UL << 31)
#define HINLRx_NEST_LVL_MASK		(0x1FFUL << 0)
	vuint32_t	HINLRx[2];
	uint32_t	RESERVED12[254];
#define HIER_IRQ_MASK			(0x1UL << 1)
#define HIER_IRQ_disabled		(0x0UL << 1)
#define HIER_IRQ_enabled		(0x1UL << 1)
#define HIER_FIQ_MASK			(0x1UL << 0)
#define HIER_FIQ_disabled		(0x0UL << 0)
#define HIER_FIQ_enabled		(0x1UL << 0)
	vuint32_t	HIER;
	uint32_t	RESERVED13[63];
	vcuint32_t	HIPVRx[2];
} AINTC_con_t;

// refer to 
// http://processors.wiki.ti.com/index.php/Programmable_Realtime_Unit
typedef struct {
#define CONTROL_PCRESETVAL_MASK		(0xFFFFUL << 16)
	vuint32_t	CONTROL;
#define STATUS_PCOUNTER_MASK		0x0000FFFFUL
	vcuint32_t	STATUS;
#define WAKEUP_ENABLES_MASK(x)		(0x1UL << (x))
#define WAKEUP_ENABLES_no(x)		(0x0UL << (x))
#define WAKEUP_ENABLES_yes(x)		(0x1UL << (x))
	vuint32_t	WAKEUP;
	vuint32_t	CYCLECNT;
	vcuint32_t	STALLCNT;
	uint32_t	RESERVED0[_RS(0x020, 0x010)];
// C25[8 - 11]
#define CONTABBLKIDX0_C25_MASK		(0xFUL << 16)
// C24[8 - 11]
#define CONTABBLKIDX0_C24_MASK		(0xFUL << 0)
	vuint32_t	CONTABBLKIDX0;
	uint32_t	RESERVED1;
#define CONTABPROPTR_C29_MASK		(0xFFFFUL << 16)
#define CONTABPROPTR_C28_MASK		(0xFFFFUL << 0)
#define CONTABPROPTR_C31_MASK		(0xFFFFUL << 16)
#define CONTABPROPTR_C30_MASK		(0xFFFFUL << 0)
	vuint32_t	CONTABPROPTR[2];
	uint32_t	RESERVED2[_RS(0x400, 0x02C)];
	vuint32_t	INTGPR[32];
	vcuint32_t	INTCTER[32];
} PRU_con_t;

enum {
	BIT_DEF(CONTROL,15,RUNSTATE,halted,running),
	BIT_DEF(CONTROL,8,SINGLESTEP,no,yes),
	BIT_DEF(CONTROL,3,COUNTENABLE,no,yes),
	BIT_DEF(CONTROL,2,SLEEPING,no,yes),
	BIT_DEF(CONTROL,1,ENABLE,no,yes),
	BIT_DEF(CONTROL,0,SOFTRESET,yes,no),
};

// am1808.pdf, Page 52
// 5.9.1 EDMA3 Channel Synchronization Events
typedef enum {
	// EDMA Channel Controller 0
	EDMA_McASP0_Receive,
	EDMA_McASP0_Transmit,
	EDMA_McBSP0_Receive,
	EDMA_McBSP0_Transmit,

	EDMA_McBSP1_Receive,
	EDMA_McBSP1_Transmit,
	EDMA_GPIO_Bank0_Interrupt,
	EDMA_GPIO_Bank1_Interrupt,

	EDMA_UART0_Receive,
	EDMA_UART0_Transmit,
	EDMA_Timer64P0_EventOut12,
	EDMA_Timer64P0_EventOut34,

	EDMA_UART1_Receive,
	EDMA_UART1_Transmit,
	EDMA_SPI0_Receive,
	EDMA_SPI0_Transmit,

	EDMA_MMCSD0_Receive,
	EDMA_MMCSD0_Transmit,
	EDMA_SPI1_Receive,
	EDMA_SPI1_Transmit,

	EDMA_PRU_EVTOUT6,
	EDMA_PRU_EVTOUT7,
	EDMA_GPIO_Bank2_Interrupt,
	EDMA_GPIO_Bank3_Interrupt,

	EDMA_I2C0_Receive,
	EDMA_I2C0_Transmit,
	EDMA_I2C1_Receive,
	EDMA_I2C1_Transmit,

	EDMA_GPIO_Bank4_Interrupt,
	EDMA_GPIO_Bank5_Interrupt,
	EDMA_UART2_Receive,
	EDMA_UART2_Transmit,

	// EDMA Channel Controller 1
	EDMA_Timer64P2_CompareEvent0,
	EDMA_Timer64P2_CompareEvent1,
	EDMA_Timer64P2_CompareEvent2,
	EDMA_Timer64P2_CompareEvent3,

	EDMA_Timer64P2_CompareEvent4,
	EDMA_Timer64P2_CompareEvent5,
	EDMA_Timer64P2_CompareEvent6,
	EDMA_Timer64P2_CompareEvent7,

	EDMA_Timer64P3_CompareEvent0,
	EDMA_Timer64P3_CompareEvent1,
	EDMA_Timer64P3_CompareEvent2,
	EDMA_Timer64P3_CompareEvent3,

	EDMA_Timer64P3_CompareEvent4,
	EDMA_Timer64P3_CompareEvent5,
	EDMA_Timer64P3_CompareEvent6,
	EDMA_Timer64P3_CompareEvent7,

	EDMA_GPIO_Bank6_Interrupt,
	EDMA_GPIO_Bank7_Interrupt,
	EDMA_GPIO_Bank8_Interrupt,
	EDMA_Reserved0,

	EDMA_Reserved1,
	EDMA_Reserved2,
	EDMA_Reserved3,
	EDMA_Reserved4,

	EDMA_Timer64P2_EventOut12,
	EDMA_Timer64P2_EventOut34,
	EDMA_Timer64P3_EventOut12,
	EDMA_Timer64P3_EventOut34,

	EDMA_MMCSD1_Receive,
	EDMA_MMCSD1_Transmit,
	EDMA_Reserved5,
	EDMA_Reserved6,
} EDMA_event_t;

typedef struct {
#define OPT_PRIVID_MASK			(0xFUL << 24)
#define OPT_PRIVID_X(x)			(((x) & 0xFUL) << 24)
#define OPT_TCC_MASK			(0x3FUL << 12)
#define OPT_TCC_X(x)			(((x) & 0x3FUL) << 12)
#define OPT_FWID_MASK			(0x7UL << 8)
#define OPT_FWID_8b			(0x0UL << 8)
#define OPT_FWID_16b			(0x1UL << 8)
#define OPT_FWID_32b			(0x2UL << 8)
#define OPT_FWID_64b			(0x3UL << 8)
#define OPT_FWID_128b			(0x4UL << 8)
#define OPT_FWID_256b			(0x5UL << 8)
#define OPT_PRI_MASK			(0x7UL << 4)
	vuint32_t	OPT;
	vuint32_t	SRC;
#define PARAM_BCNT_MASK			(0xFFFFUL << 16)
#define PARAM_ACNT_MASK			(0xFFFFUL << 0)
	vuint32_t	A_B_CNT;
	vuint32_t	DST;
#define PARAM_DSTBIDX_MASK		(0xFFFFUL << 16)
#define PARAM_SRCBIDX_MASK		(0xFFFFUL << 0)
	vuint32_t	SRC_DST_BIDX;
#define PARAM_BCNTRLD_MASK		(0xFFFFUL << 16)
#define PARAM_LINK_MASK			(0xFFFFUL << 0)
	vuint32_t	LINK_BCNTRLD;
#define PARAM_DSTCIDX_MASK		(0xFFFFUL << 16)
#define PARAM_SRCCIDX_MASK		(0xFFFFUL << 0)
	vuint32_t	SRC_DST_CIDX;
#define PARAM_CCNT_MASK			(0xFFFFUL << 0)
	vuint32_t	CCNT;
} PaRAM_entry_t;

enum {
	BIT_DEF(OPT,23,ITCCHEN,no,yes),
	BIT_DEF(OPT,22,TCCHEN,no,yes),
	BIT_DEF(OPT,21,ITCINTEN,no,yes),
	BIT_DEF(OPT,20,TCINTEN,no,yes),
	BIT_DEF(OPT,11,TCCMODE,Normal,Early),
	BIT_DEF(OPT,3,STATIC,no,yes),
	BIT_DEF(OPT,2,SYNCDIM,Async,ABsync),
	BIT_DEF(OPT,1,DAM,INCR,CONST),
	BIT_DEF(OPT,0,SAM,INCR,CONST),
};

typedef struct {
// n = 0..31
#define ExR_En_MASK(n)			(0x1UL << (n))
#define ExR_En_none(n)			(0x0UL << (n))
#define ExR_En_asserted(n)		(0x1UL << (n))
#define ExR_En_clear(n)			(0x1UL << (n))
#define ExR_En_set(n)			(0x1UL << (n))
	vcuint32_t	ER;
	uint32_t	RESERVED0;
	vuint32_t	ECR;
	uint32_t	RESERVED1;
	vuint32_t	ESR;
	uint32_t	RESERVED2;
// n = 0..31
#define CER_En_MASK(n)			(0x1UL << (n))
#define CER_En_none(n)			(0x0UL << (n))
#define CER_En_prioritized(n)		(0x1UL << (n))
	vcuint32_t	CER;
	uint32_t	RESERVED3;
// n = 0..31
#define EExR_En_MASK(n)			(0x1UL << (n))
#define EExR_En_no(n)			(0x0UL << (n))
#define EExR_En_yes(n)			(0x1UL << (n))
#define EExR_En_clear(n)		(0x1UL << (n))
#define EExR_En_set(n)			(0x1UL << (n))
	vcuint32_t	EER;
	uint32_t	RESERVED4;
	vuint32_t	EECR;
	uint32_t	RESERVED5;
	vuint32_t	EESR;
	uint32_t	RESERVED6;
// n = 0..31
#define SExR_En_MASK(n)			(0x1UL << (n))
#define SExR_En_none(n)			(0x0UL << (n))
#define SExR_En_stored(n)		(0x1UL << (n))
#define SExR_En_clear(n)		(0x1UL << (n))
	vcuint32_t	SER;
	uint32_t	RESERVED7;
	vuint32_t	SECR;
	uint32_t	RESERVED8[_RS(0x50,0x40)];
// n = 0..31
#define IExR_En_MASK(n)			(0x1UL << (n))
#define IExR_En_no(n)			(0x0UL << (n))
#define IExR_En_yes(n)			(0x1UL << (n))
#define IExR_En_clear(n)		(0x1UL << (n))
#define IExR_En_set(n)			(0x1UL << (n))
	vcuint32_t	IER;
	uint32_t	RESERVED9;
	vuint32_t	IECR;
	uint32_t	RESERVED10;
	vuint32_t	IESR;
	uint32_t	RESERVED11;
// n = 0..31
#define IxR_En_MASK(n)			(0x1UL << (n))
#define IxR_En_none(n)			(0x0UL << (n))
#define IxR_En_pending(n)		(0x1UL << (n))
#define IxR_En_clear(n)			(0x1UL << (n))
	vcuint32_t	IPR;
	uint32_t	RESERVED12;
	vuint32_t	ICR;
	uint32_t	RESERVED13;
	vuint32_t	IEVAL;
	uint32_t	RESERVED14;
// n = 0..7
#define QER_En_MASK(n)			(0x1UL << (n))
#define QER_En_none(n)			(0x0UL << (n))
#define QER_En_prioritized(n)		(0x1UL << (n))
	vcuint32_t	QER;
// n = 0..7
#define QEExR_En_MASK(n)		(0x1UL << (n))
#define QEExR_En_no(n)			(0x0UL << (n))
#define QEExR_En_yes(n)			(0x1UL << (n))
#define QEExR_En_clear(n)		(0x1UL << (n))
#define QEExR_En_set(n)			(0x1UL << (n))
	vcuint32_t	QEER;
	vuint32_t	QEECR;
	vuint32_t	QEESR;
// n = 0..7
#define QSExR_En_MASK(n)		(0x1UL << (n))
#define QSExR_En_none(n)		(0x0UL << (n))
#define QSExR_En_stored(n)		(0x1UL << (n))
#define QSExR_En_clear(n)		(0x1UL << (n))
	vcuint32_t	QSER;
	vuint32_t	QSECR;
} EDMA3CC_rgn_t;

typedef struct {
#define EDMA3CC_REVID			0x40015300UL
	vcuint32_t	REVID;
#define CCCFG_NUM_REGN_MASK		(0x3UL << 20)
#define CCCFG_NUM_EVQUE_MASK		(0x7UL << 16)
#define CCCFG_NUM_PAENTRY_MASK		(0x7UL << 12)
#define CCCFG_NUM_INTCH_MASK		(0x7UL << 8)
#define CCCFG_NUM_QDMACH_MASK		(0x7UL << 4)
#define CCCFG_NUM_DMACH_MASK		(0x7UL << 0)
	vcuint32_t	CCCFG;
	uint32_t	RESERVED0[_RS(0x200,0x004)];
#define QCHMAP_PAENTRY_MASK		(0x7FUL << 5)
#define QCHMAP_TRWORD_MASK		(0x7UL << 2)
	vuint32_t	QCHMAPx[8];
	uint32_t	RESERVED1[_RS(0x240,0x21C)];
// n = 0..31
#define DMAQNUM_IDX(n)			((n) >> 3)
#define DMAQNUM_En_MASK(n)		(0x7UL << (((n) & 0x7UL) << 2))
	vuint32_t	DMAQNUMx[4];
	uint32_t	RESERVED2[_RS(0x260,0x24C)];
// n = 0..7
#define QDMAQNUM_En_MASK(n)		(0x7UL << (((n) & 0x7UL) << 2))
	vuint32_t	QDMAQNUM;
	uint32_t	RESERVED3[_RS(0x284,0x260)];
	vuint32_t	QUEPRI;
	uint32_t	RESERVED4[_RS(0x300,0x284)];
// n = 0..31
#define EMxR_En_MASK(n)			(0x1UL << (n))
#define EMxR_En_none(n)			(0x0UL << (n))
#define EMxR_En_missed(n)		(0x1UL << (n))
#define EMxR_En_clear(n)		(0x1UL << (n))
	vcuint32_t	EMR;
	uint32_t	RESERVED5;
	vuint32_t	EMCR;
	uint32_t	RESERVED6;
// n = 0..7
#define QEMxR_En_MASK(n)		(0x1UL << (n))
#define QEMxR_En_none(n)		(0x0UL << (n))
#define QEMxR_En_missed(n)		(0x1UL << (n))
#define QEMxR_En_clear(n)		(0x1UL << (n))
	vcuint32_t	QEMR;
	vuint32_t	QEMCR;
	vcuint32_t	CCERR;
	vuint32_t	CCERRCLR;
	vuint32_t	EEVAL;
	uint32_t	RESERVED7[_RS(0x340,0x320)];
#define DRAE_IDX(r)			((r) << 1)
// n = 0..31
#define DRAE_En_MASK(n)			(0x1UL << (n))
#define DRAE_En_none(n)			(0x0UL << (n))
#define DRAE_En_allow(n)		(0x1UL << (n))
	vuint32_t	DRAEx[8];
	uint32_t	RESERVED8[_RS(0x380,0x35C)];
// n = 0..7
#define QRAE_En_MASK(n)			(0x1UL << (n))
#define QRAE_En_none(n)			(0x0UL << (n))
#define QRAE_En_allow(n)		(0x1UL << (n))
	vuint32_t	QRAEx[4];
	uint32_t	RESERVED9[_RS(0x400,0x38C)];
#define QyEx_ETYPE_MASK			(0x3UL << 6)
#define QyEx_ETYPE_ER			(0x0UL << 6)
#define QyEx_ETYPE_ESR			(0x1UL << 6)
#define QyEx_ETYPE_CER			(0x2UL << 6)
#define QyEx_ETYPE_QER			(0x3UL << 6)
#define QyEx_ENUM_MASK			(0x1FUL << 0)
	vcuint32_t	Q0Ex[16];
	vcuint32_t	Q1Ex[16];
	uint32_t	RESERVED10[_RS(0x600,0x47C)];
#define QSTAT_WM_MASK			(0x1FUL << 16)
#define QSTAT_WM_isLegal(x)		(0 <= (x) && (x) <= 10)
#define QSTAT_NUMVAL_MASK		(0x1FUL << 8)
#define QSTAT_NUMVAL_isLegal(x)		(0 <= (x) && (x) <= 10)
#define QSTAT_STRTPTR_MASK		(0xFUL << 0)
	vcuint32_t	QSTATx[2];
	uint32_t	RESERVED11[_RS(0x620,0x604)];
#define QWMTHRA_Q1_MASK			(0x1FUL << 8)
#define QWMTHRA_Q0_MASK			(0x1FUL << 0)
	vuint32_t	QWMTHRA;
	uint32_t	RESERVED12[_RS(0x640,0x620)];
#define CCSTAT_COMPACTV_MASK		(0x3FUL << 8)
	vcuint32_t	CCSTAT;
	uint32_t	RESERVED13[_RS(0x1000,0x640)];
	EDMA3CC_rgn_t	Global;
	uint32_t	RESERVED14[_RS(0x2000,0x1094)];
	EDMA3CC_rgn_t	Region0;
	uint32_t	RESERVED15[_RS(0x2200,0x2094)];
	EDMA3CC_rgn_t	Region1;
	uint32_t	RESERVED16[_RS(0x4000,0x2294)];
#define PAEntry_CNT			128
	PaRAM_entry_t	PAEntry[PAEntry_CNT];
} EDMA3CC_con_t;

enum {
	BIT_DEF(CCCFG,25,MP_EXIST,no,yes),
	BIT_DEF(CCCFG,24,CHMAP_EXIST,no,yes),
	BIT_DEF(CCERR,16,TCCERR,none,reached),
	BIT_DEF(CCERR,1,QTHRXCD1,none,exceed),
	BIT_DEF(CCERR,0,QTHRXCD0,none,exceed),
	BIT_DEF(CCERRCLR,16,TCCERR,none,clear),
	BIT_DEF(CCERRCLR,1,QTHRXCD1,none,clear),
	BIT_DEF(CCERRCLR,0,QTHRXCD0,none,clear),
	BIT_DEF(EEVAL,0,EVAL,none,pulsed),
	BIT_DEF(QSTAT,24,THRXCD,no,yes),
	BIT_DEF(CCSTAT,17,QUEACTV1,no,yes),
	BIT_DEF(CCSTAT,16,QUEACTV0,no,yes),
	BIT_DEF(CCSTAT,4,ACTV,no,yes),
	BIT_DEF(CCSTAT,3,WSTATACTV,no,yes),
	BIT_DEF(CCSTAT,2,TRACTV,no,yes),
	BIT_DEF(CCSTAT,1,QEVTACTV,no,yes),
	BIT_DEF(CCSTAT,0,EVTACTV,no,yes),
	BIT_DEF(IEVAL,0,EVAL,none,pulsed),
};

typedef struct {
	vuint32_t	OPT;
	vcuint32_t	SRC;
	vcuint32_t	CNT;
	vcuint32_t	DST;
	vcuint32_t	BIDX;
#define MPPRXY_PRIVID_MASK		(0xFUL << 0)
	vcuint32_t	MPPRXY;
	// only valid for Source Active (SA)
	vcuint32_t	SACNTRLD;
	vcuint32_t	SASRCBREF;
	vcuint32_t	SADSTBREF;
	uint32_t	RESERVED0[_RS(0x40,0x20)];
} EDMA3TC_fifo_t;

enum {
	BIT_DEF(MPPRXY,8,PRIV,user,supervisor),
};

typedef struct {
#define EDMA3TC_REVID			0x40003B00UL
	vcuint32_t	REVID;
#define TCCFG_DREGDEPTH_MASK		(0x3UL << 8)
#define TCCFG_BUSWIDTH_MASK		(0x3UL << 4)
#define TCCFG_FIFOSIZE_MASK		(0x7UL << 0)
	vcuint32_t	TCCFG;
	uint32_t	RESERVED0[_RS(0x100,0x004)];
#define TCSTAT_DFSTRTPTR_MASK		(0x3UL << 11)
#define TCSTAT_DSTACTV_MASK		(0x7UL << 4)
	vcuint32_t	TCSTAT;
	uint32_t	RESERVED1[_RS(0x120,0x100)];
	vcuint32_t	ERRSTAT;
	vuint32_t	ERREN;
	vuint32_t	ERRCLR;
#define ERRDET_TCC_MASK			(0x3FUL << 8)
#define ERRDET_STAT_MASK		(0xFUL << 0)
#define ERRDET_STAT_NoError		(0x0UL << 0)
#define ERRDET_STAT_ReadAddressing	(0x1UL << 0)
#define ERRDET_STAT_ReadPrivilege	(0x2UL << 0)
#define ERRDET_STAT_ReadTimeout		(0x3UL << 0)
#define ERRDET_STAT_ReadData		(0x4UL << 0)
#define ERRDET_STAT_ReadExclusive	(0x7UL << 0)
#define ERRDET_STAT_WriteAddressing	(0x9UL << 0)
#define ERRDET_STAT_WritePrivilege	(0xAUL << 0)
#define ERRDET_STAT_WriteTimeout	(0xBUL << 0)
#define ERRDET_STAT_WriteData		(0xCUL << 0)
#define ERRDET_STAT_WriteExclusive	(0xFUL << 0)
	vcuint32_t	ERRDET;
	vuint32_t	ERRCMD;
	uint32_t	RESERVED2[_RS(0x140,0x130)];
#define RDRATE_X_MASK			(0x7UL << 0)
#define RDRATE_X_AsFast			(0x0UL << 0)
#define RDRATE_X_4cycles		(0x1UL << 0)
#define RDRATE_X_8cycles		(0x2UL << 0)
#define RDRATE_X_16cycles		(0x3UL << 0)
#define RDRATE_X_32cycles		(0x4UL << 0)
	vuint32_t	RDRATE;
	uint32_t	RESERVED3[_RS(0x240,0x140)];
	EDMA3TC_fifo_t	SAx[1];
	vcuint32_t	DFCNTRLD;
	vcuint32_t	DFSRCBREF;
	vcuint32_t	DFDSTBREF;
	uint32_t	RESERVED5[_RS(0x300,0x288)];
	EDMA3TC_fifo_t	DFx[4];
} EDMA3TC_con_t;

enum {
	BIT_DEF(TCSTAT,2,WSACTV,none,pending),
	BIT_DEF(TCSTAT,1,SRCACTV,idle,busy),
	BIT_DEF(TCSTAT,0,PROGBUSY,idle,busy),
	BIT_DEF(ERRSTAT,3,MMRAERR,no,yes),
	BIT_DEF(ERRSTAT,2,THERR,no,yes),
	BIT_DEF(ERRSTAT,0,BUSERR,no,yes),
	BIT_DEF(ERREN,3,MMRAERR,no,yes),
	BIT_DEF(ERREN,2,THERR,no,yes),
	BIT_DEF(ERREN,0,BUSERR,no,yes),
	BIT_DEF(ERRCLR,3,MMRAERR,none,clear),
	BIT_DEF(ERRCLR,2,THERR,none,clear),
	BIT_DEF(ERRCLR,0,BUSERR,none,clear),
	BIT_DEF(ERRDET,17,TCCHEN,no,yes),
	BIT_DEF(ERRDET,16,TCINTEN,no,yes),
	BIT_DEF(ERRCMD,0,EVAL,none,pulsed),
};

typedef struct {
	EDMA3CC_con_t		CC;
	uint32_t		RESERVED0[_RS(0x8000,0x4FFC)];
	EDMA3TC_con_t		TC[2];
} EDMA_con_t;

typedef struct {
#define XXX_GPkPj_MASK(j)		(0x1UL << (j))
#define DIR_GPkPj_output(j)		(0x0UL << (j))
#define DIR_GPkPj_input(j)		(0x1UL << (j))
	vuint32_t	DIR;
#define OUT_DATA_GPkPj_low(j)		(0x0UL << (j))
#define OUT_DATA_GPkPj_high(j)		(0x1UL << (j))
	vuint32_t	OUT_DATA;
#define SET_DATA_GPkPj_none(j)		(0x0UL << (j))
#define SET_DATA_GPkPj_high(j)		(0x1UL << (j))
	vuint32_t	SET_DATA;
#define CLR_DATA_GPkPj_none(j)		(0x0UL << (j))
#define CLR_DATA_GPkPj_low(j)		(0x1UL << (j))
	vuint32_t	CLR_DATA;
#define IN_DATA_GPkPj_low(j)		(0x0UL << (j))
#define IN_DATA_GPkPj_high(j)		(0x1UL << (j))
	vuint32_t	IN_DATA;
#define SET_RIS_TRIG_none(j)		(0x0UL << (j))
#define SET_RIS_TRIG_enable(j)		(0x1UL << (j))
	vuint32_t	SET_RIS_TRIG;
#define CLR_RIS_TRIG_none(j)		(0x0UL << (j))
#define CLR_RIS_TRIG_disable(j)		(0x1UL << (j))
	vuint32_t	CLR_RIS_TRIG;
#define SET_FAL_TRIG_none(j)		(0x0UL << (j))
#define SET_FAL_TRIG_disable(j)		(0x1UL << (j))
	vuint32_t	SET_FAL_TRIG;
#define CLR_FAL_TRIG_none(j)		(0x0UL << (j))
#define CLR_FAL_TRIG_disable(j)		(0x1UL << (j))
	vuint32_t	CLR_FAL_TRIG;
#define INTSTAT_none(j)			(0x0UL << (j))
#define INTSTAT_pending(j)		(0x1UL << (j))
	vuint32_t	INTSTAT;
} GPIO_pair_t;

typedef struct {
#define GPIO_REVID			0x44830105UL
	vcuint32_t	REVID;
	uint32_t	RESERVED0;
#define BIT_ENx_MASK(x)			(0x1UL << (x))
#define BIT_ENx_no(x)			(0x0UL << (x))
#define BIT_ENx_yes(x)			(0x1UL << (x))
	vuint32_t	BINTEN;
	uint32_t	RESERVED1;
#define GPIO_BANKS_0_1			0
#define GPIO_BANKS_2_3			1
#define GPIO_BANKS_4_5			2
#define GPIO_BANKS_6_7			3
#define GPIO_BANKS_8			4
	GPIO_pair_t	BANKS[5];
} GPIO_con_t;

typedef struct {
#define ICOAR_OADDR_MASK		(0x3FFUL << 0)
#define ICOAR_OADDR_VAL(x)		((0x3FFUL & (x)) << 0)
	vuint32_t	ICOAR;
#define ICIMR_AAS_MASK			(0x1UL << 6)
#define ICIMR_AAS_disabled		(0x0UL << 6)
#define ICIMR_AAS_enabled		(0x1UL << 6)
#define ICIMR_SCD_MASK			(0x1UL << 5)
#define ICIMR_SCD_disabled		(0x0UL << 5)
#define ICIMR_SCD_enabled		(0x1UL << 5)
#define ICIMR_ICXRDY_MASK		(0x1UL << 4)
#define ICIMR_ICXRDY_disabled		(0x0UL << 4)
#define ICIMR_ICXRDY_enabled		(0x1UL << 4)
#define ICIMR_ICRRDY_MASK		(0x1UL << 3)
#define ICIMR_ICRRDY_disabled		(0x0UL << 3)
#define ICIMR_ICRRDY_enabled		(0x1UL << 3)
#define ICIMR_ARDY_MASK			(0x1UL << 2)
#define ICIMR_ARDY_disabled		(0x0UL << 2)
#define ICIMR_ARDY_enabled		(0x1UL << 2)
#define ICIMR_NACK_MASK			(0x1UL << 1)
#define ICIMR_NACK_disabled		(0x0UL << 1)
#define ICIMR_NACK_enabled		(0x1UL << 1)
#define ICIMR_AL_MASK			(0x1UL << 0)
#define ICIMR_AL_disabled		(0x0UL << 0)
#define ICIMR_AL_enabled		(0x1UL << 0)
	vuint32_t	ICIMR;
#define ICSTR_SDIR_MASK			(0x1UL << 14)
#define ICSTR_SDIR_other		(0x0UL << 14)
#define ICSTR_SDIR_slaveTX		(0x1UL << 14)
#define ICSTR_SDIR_clear		(0x1UL << 14)
#define ICSTR_NACKSNT_MASK		(0x1UL << 13)
#define ICSTR_NACKSNT_none		(0x0UL << 13)
#define ICSTR_NACKSNT_sent		(0x1UL << 13)
#define ICSTR_NACKSNT_clear		(0x1UL << 13)
#define ICSTR_BB_MASK			(0x1UL << 12)
#define ICSTR_BB_free			(0x0UL << 12)
#define ICSTR_BB_busy			(0x1UL << 12)
#define ICSTR_BB_clear			(0x1UL << 12)
#define ICSTR_RSFULL_MASK		(0x1UL << 11)
#define ICSTR_RSFULL_none		(0x0UL << 11)
#define ICSTR_RSFULL_overrun		(0x1UL << 11)
#define ICSTR_XSMT_MASK			(0x1UL << 10)
#define ICSTR_XSMT_underflow		(0x0UL << 10)
#define ICSTR_XSMT_none			(0x1UL << 10)
#define ICSTR_AAS_MASK			(0x1UL << 9)
#define ICSTR_ASS_cleared		(0x0UL << 9)
#define ICSTR_ASS_set			(0x1UL << 9)
#define ICSTR_AD0_MASK			(0x1UL << 8)
#define ICSTR_AD0_cleared		(0x0UL << 8)
#define ICSTR_AD0_detected		(0x1UL << 8)
#define ICSTR_SCD_MASK			(0x1UL << 5)
#define ICSTR_SCD_none			(0x0UL << 5)
#define ICSTR_SCD_detected		(0x1UL << 5)
#define ICSTR_SCD_clear			(0x1UL << 5)
#define ICSTR_ICXRDY_MASK		(0x1UL << 4)
#define ICSTR_ICXRDY_none		(0x0UL << 4)
#define ICSTR_ICXRDY_ready		(0x1UL << 4)
#define ICSTR_ICXRDY_clear		(0x1UL << 4)
#define ICSTR_ICRRDY_MASK		(0x1UL << 3)
#define ICSTR_ICRRDY_none		(0x0UL << 3)
#define ICSTR_ICRRDY_ready		(0x1UL << 3)
#define ICSTR_ICRRDY_clear		(0x1UL << 3)
#define ICSTR_ARDY_MASK			(0x1UL << 2)
#define ICSTR_ARDY_none			(0x0UL << 2)
#define ICSTR_ARDY_ready		(0x1UL << 2)
#define ICSTR_ARDY_clear		(0x1UL << 2)
#define ICSTR_NACK_MASK			(0x1UL << 1)
#define ICSTR_NACK_ack			(0x0UL << 1)
#define ICSTR_NACK_nack			(0x1UL << 1)
#define ICSTR_NACK_clear		(0x1UL << 1)
#define ICSTR_AL_MASK			(0x1UL << 0)
#define ICSTR_AL_none			(0x0UL << 0)
#define ICSTR_AL_lost			(0x1UL << 0)
#define ICSTR_AL_clear			(0x1UL << 0)
	vuint32_t	ICSTR;
#define ICCLKL_MASK			(0xFFFFUL << 0)
	vuint32_t	ICCLKL;
#define ICCLKH_MASK			(0xFFFFUL << 0)
	vuint32_t	ICCLKH;
#define ICCNT_MASK			(0xFFFFUL << 0)
	vuint32_t	ICCNT;
#define ICDRR_MASK			(0xFFUL << 0)
	vuint32_t	ICDRR;
#define ICSAR_SADDR_MASK		(0x3FFUL << 0)
#define ICSAR_SADDR_VAL(x)		((0x3FFUL & (x)) << 0)
	vuint32_t	ICSAR;
#define ICDXR_MASK			(0xFFUL << 0)
	vuint32_t	ICDXR;
#define ICMDR_NACKMOD_MASK		(0x1UL << 15)
#define ICMDR_NACKMOD_no		(0x0UL << 15)
#define ICMDR_NACKMOD_yes		(0x1UL << 15)
#define ICMDR_FREE_MASK			(0x1UL << 14)
#define ICMDR_FREE_emu			(0x0UL << 14)
#define ICMDR_FREE_run			(0x1UL << 14)
#define ICMDR_STT_MASK			(0x1UL << 13)
#define ICMDR_STT_no			(0x0UL << 13)
#define ICMDR_STT_yes			(0x1UL << 13)
#define ICMDR_STP_MASK			(0x1UL << 11)
#define ICMDR_STP_no			(0x0UL << 11)
#define ICMDR_STP_yes			(0x1UL << 11)
#define ICMDR_MST_MASK			(0x1UL << 10)
#define ICMDR_MST_slave			(0x0UL << 10)
#define ICMDR_MST_master		(0x1UL << 10)
#define ICMDR_TRX_MASK			(0x1UL << 9)
#define ICMDR_TRX_receiver		(0x0UL << 9)
#define ICMDR_TRX_transmitter		(0x1UL << 9)
#define ICMDR_XA_MASK			(0x1UL << 8)
#define ICMDR_XA_7bit			(0x0UL << 8)
#define ICMDR_XA_10bit			(0x1UL << 8)
#define ICMDR_RM_MASK			(0x1UL << 7)
#define ICMDR_RM_no			(0x0UL << 7)
#define ICMDR_RM_yes			(0x1UL << 7)
#define ICMDR_DLB_MASK			(0x1UL << 6)
#define ICMDR_DLB_disable		(0x0UL << 6)
#define ICMDR_DLB_enable		(0x1UL << 6)
#define ICMDR_IRS_MASK			(0x1UL << 5)
#define ICMDR_IRS_reset			(0x0UL << 5)
#define ICMDR_IRS_none			(0x1UL << 5)
#define ICMDR_STB_MASK			(0x1UL << 4)
#define ICMDR_STB_no			(0x0UL << 4)
#define ICMDR_STB_yes			(0x1UL << 4)
#define ICMDR_FDF_MASK			(0x1UL << 3)
#define ICMDR_FDF_no			(0x0UL << 3)
#define ICMDR_FDF_yes			(0x1UL << 3)
#define ICMDR_BC_MASK			(0x7UL << 0)
#define ICMDR_BC_VAL(x)			((0x7UL & (x)) << 0)
	vuint32_t	ICMDR;
#define ICIVR_INTCODE_MASK		(0x7UL << 0)
#define ICIVR_INTCODE_none		(0x0UL << 0)
#define ICIVR_INTCODE_AL		(0x1UL << 0)
#define ICIVR_INTCODE_NACK		(0x2UL << 0)
#define ICIVR_INTCODE_ARDY		(0x3UL << 0)
#define ICIVR_INTCODE_ICRRDY		(0x4UL << 0)
#define ICIVR_INTCODE_ICXRDY		(0x5UL << 0)
#define ICIVR_INTCODE_SCD		(0x6UL << 0)
#define ICIVR_INTCODE_AAS		(0x7UL << 0)
	vuint32_t	ICIVR;
#define ICEMDR_IGNACK_MASK		(0x1UL << 1)
#define ICEMDR_IGNACK_no		(0x0UL << 1)
#define ICEMDR_IGNACK_yes		(0x1UL << 1)
#define ICEMDR_BCM_MASK			(0x1UL << 0)
#define ICEMDR_BCM_ack			(0x0UL << 0)
#define ICEMDR_BCM_none			(0x1UL << 0)
	vuint32_t	ICEMDR;
#define ICPSC_IPSC_MASK			(0xFFUL << 0)
#define ICPSC_IPSC_VAL(x)		((0xFFUL & (x)) << 0)
	vuint32_t	ICPSC;
	vcuint32_t	REVID[2];
#define ICDMAC_TXDMAEN_MASK		(0x1UL << 1)
#define ICDMAC_TXDMAEN_disable		(0x0UL << 1)
#define ICDMAC_TXDMAEN_enable		(0x1UL << 1)
#define ICDMAC_RXDMAEN_MASK		(0x1UL << 0)
#define ICDMAC_RXDMAEN_disable		(0x0UL << 0)
#define ICDMAC_RXDMAEN_enable		(0x1UL << 0)
	vuint32_t	ICDMAC;
	uint32_t	RESERVED0[2];
#define ICPFUNC_PFUNC0_MASK		(0x1UL << 0)
#define ICPFUNC_PFUNC0_i2c		(0x0UL << 0)
#define ICPFUNC_PFUNC0_gpio		(0x1UL << 0)
	vuint32_t	ICPFUNC;
#define ICPXXX_SCL			0x0
#define ICPXXX_SDA			0x1
#define ICPDIR_PDIRx_MASK(x)		(0x1UL << (x))
#define ICPDIR_PDIRx_input(x)		(0x0UL << (x))
#define ICPDIR_PDIRx_output(x)		(0x1UL << (x))
	vuint32_t	ICPDIR;
#define ICPDIO_PDIO_MASK(x)		(0x1UL << (x))
#define ICPDIO_PDIO_low(x)		(0x0UL << (x))
#define ICPDIO_PDIO_high(x)		(0x1UL << (x))
	vuint32_t	ICPDIN;
	vuint32_t	ICPDOUT;
#define ICPDXXX_MASK(x)			(0x1UL << (x))
#define ICPDXXX_none(x)			(0x0UL << (x))
#define ICPDXXX_assert(x)		(0x1UL << (x))
	vuint32_t	ICPDSET;
	vuint32_t	ICPDCLR;
} I2C_con_t;

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
#define TCR_TSTAT12_deasserted		(0x0UL << 0)
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

#undef _RS

/*----------------------------------------------------------------------------*/
// periheral addresses
/*----------------------------------------------------------------------------*/
// AM1808 ARM Microprocessor
// 2.4 Memory Map Summary
#define EDMA3_0CC0_BASE			0x01C00000UL
#define EDMA3_0TC0_BASE			0x01C08000UL
#define EDMA3_0TC1_BASE			0x01C08400UL
#define PSC0_BASE			0x01C10000UL
#define PLL0_BASE			0x01C11000UL
#define SYSCFG0_BASE			0x01C14000UL
#define TIMER0_BASE			0x01C20000UL
#define TIMER1_BASE			0x01C21000UL
#define I2C0_BASE			0x01C22000UL
#define PRU_DataRAM0_BASE		0x01C30000UL
#define PRU_DataRAM0_SIZE		0x00000200UL
#define PRU_DataRAM1_BASE		0x01C32000UL
#define PRU_DataRAM1_SIZE		0x00000200UL
#define PRU_INTC_BASE			0x01C34000UL
#define PRU0_BASE			0x01C37000UL
#define PRU1_BASE			0x01C37800UL
#define PRU_InstRAM0_BASE		0x01C38000UL
#define PRU_InstRAM0_SIZE		0x00001000UL
#define PRU_InstRAM1_BASE		0x01C3C000UL
#define PRU_InstRAM1_SIZE		0x00001000UL
#define UART0_BASE			0x01C42000UL
#define UART1_BASE			0x01D0C000UL
#define UART2_BASE			0x01D0D000UL
#define MPU1_BASE			0x01E14000UL
#define MPU2_BASE			0x01E15000UL
#define PLL1_BASE			0x01E1A000UL
#define GPIOCON_BASE			0x01E26000UL
#define PSC1_BASE			0x01E27000UL
#define I2C1_BASE			0x01E28000UL
#define SYSCFG1_BASE			0x01E2C000UL
#define EDMA3_1CC0_BASE			0x01E30000UL
#define EDMA3_1TC0_BASE			0x01E38000UL
#define TIMER2_BASE			0x01F0C000UL
#define TIMER3_BASE			0x01F0D000UL
#define ARMLocalROM_BASE		0xFFFD0000UL
#define ARMLocalROM_SIZE		0x00010000UL
#define AINTC_BASE			0xFFFEE000UL
#define ARMLocalRAM_BASE		0xFFFF0000UL
#define ARMLocalRAM_SIZE		0x00002000UL



/*----------------------------------------------------------------------------*/
// peripheral names
/*----------------------------------------------------------------------------*/

#ifndef __MEM_REMAP
#ifdef _MPU1
	#define MPU1			((MPU_con_t*)MPU1_BASE)
#endif
#ifdef _MPU2
	#define MPU2			((MPU_con_t*)MPU2_BASE)
#endif
#ifdef _PLL0
	#define PLL0			((PLL_con_t*)PLL0_BASE)
#endif
#ifdef _PLL1
	#define PLL1			((PLL_con_t*)PLL1_BASE)
#endif
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
#ifdef _AINTC
	#define AINTC			((AINTC_con_t*)AINTC_BASE)
#endif
#ifdef _PRU0
	#define PRU0			((PRU_con_t*)PRU0_BASE)
#endif
#ifdef _PRU1
	#define PRU1			((PRU_con_t*)PRU1_BASE)
#endif
#ifdef _EDMA0
	#define EDMA0			((EDMA_con_t*)EDMA3_0CC0_BASE)
#endif
#ifdef _EDMA1
	#define EDMA1			((EDMA_con_t*)EDMA3_1CC0_BASE)
#endif
#ifdef _GPIO
	#define GPIOCON			((GPIO_con_t*)GPIOCON_BASE)
#endif
#ifdef _I2C0
	#define I2C0 			((I2C_con_t*)I2C0_BASE)
#endif
#ifdef _I2C1
	#define I2C1			((I2C_con_t*)I2C1_BASE)
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
#ifdef _MPU1
	_EXTERN MPU_con_t		*MPU1;
#endif
#ifdef _MPU2
	_EXTERN MPU_con_t		*MPU2;
#endif
#ifdef _PLL0
	_EXTERN PLL_con_t		*PLL0;
#endif
#ifdef _PLL1
	_EXTERN PLL_con_t		*PLL1;
#endif
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
#ifdef _AINTC
	_EXTERN AINTC_con_t		*AINTC;
#endif
#ifdef _PRU0
	_EXTERN PRU_con_t		*PRU0;
#endif
#ifdef _PRU1
	_EXTERN PRU_con_t		*PRU1;
#endif
#ifdef _EDMA0
	_EXTERN EDMA_con_t		*EDMA0;
#endif
#ifdef _EDMA1
	_EXTERN EDMA_con_t		*EDMA1;
#endif
#ifdef _GPIO
	_EXTERN GPIO_con_t		*GPIOCON;
#endif
#ifdef _I2C0
	_EXTERN I2C_con_t		*I2C0;
#endif
#ifdef _I2C1
	_EXTERN I2C_con_t		*I2C1;
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
// sed -n -e "/^#define/{ s/\([^0]0x[0-9a-fA-F]\+\)UL/\1/g;p; }" am18x_map.h >am18x_map_s.h
