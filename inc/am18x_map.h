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
#define DLL_MASK			0xFFUL
	vuint32_t	DLL;
#define DLH_MASK			0xFFUL
	vuint32_t	DLH;
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
#define UART0_BASE			0x01C42000UL
#define UART1_BASE			0x01D0C000UL
#define UART2_BASE			0x01D0D000UL
#define PSC1_BASE			0x01E27000UL


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
