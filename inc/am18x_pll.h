// tary, 17:27 2013/4/14

#ifndef __AM18X_PLL_H__
#define __AM18X_PLL_H__

#include "am18x_map.h"

typedef enum {
	CLK_NODE_PLL0_SYSCLK1,
	CLK_NODE_PLL0_SYSCLK2,
	CLK_NODE_PLL0_SYSCLK3,
	CLK_NODE_PLL0_SYSCLK4,
	CLK_NODE_PLL0_SYSCLK5,
	CLK_NODE_PLL0_SYSCLK6,
	CLK_NODE_PLL0_SYSCLK7,
	CLK_NODE_EMA_CLKSRC,
	CLK_NODE_PLL0_AUXCLK,
	CLK_NODE_PLL0_OBSCLK,
	CLK_NODE_PLL1_SYSCLK1,
	CLK_NODE_PLL1_SYSCLK2,
	CLK_NODE_PLL1_SYSCLK3,
	CLK_NODE_PLL1_OBSCLK,

	CLK_NODE_ASYNC3,

	CLK_NODE_PLLCTL0_PLLEN,
	CLK_NODE_PLLCTL0_EXTCLKSRC,
	CLK_NODE_POSTDIV0,
	CLK_NODE_PLLM0,
	CLK_NODE_PREDIV0,
	CLK_NODE_PLLCTL_CLKMODE,
	CLK_NODE_OSCIN,

	CLK_NODE_DIV4_5,

	CLK_NODE_OSCDIV0,
	CLK_NODE_OCSEL0_OCSRC,

	CLK_NODE_PLLCTL1_PLLEN,
	CLK_NODE_POSTDIV1,
	CLK_NODE_PLLM1,

	CLK_NODE_OSCDIV1,
	CLK_NODE_OCSEL1_OCSRC,

	CLK_NODE_CNT,
} clk_node_id_t;

typedef struct {
	cuint32_t	id;
	uint32_t	parent;
	uint32_t	multiplier;
	uint32_t	divider;
	uint8_t		recalc;
} clk_node_t;

#define DCLK_ID_GRP_SZ			0x100
typedef enum {
	DCLK_ID_ARM_RAM_ROM = CLK_NODE_PLL0_SYSCLK2 * DCLK_ID_GRP_SZ,
	DCLK_ID_ON_CHIP_RAM,
	DCLK_ID_UART0,
	DCLK_ID_EDMA,
	DCLK_ID_SPI0,
	DCLK_ID_MMC_SDS,
	DCLK_ID_VPIF,
	DCLK_ID_LCDC,
	DCLK_ID_SATA,
	DCLK_ID_UPP,
	DCLK_ID_DDR2_MDDR,
	DCLK_ID_USB2_0,
	DCLK_ID_HPI,
	DCLK_ID_PRUSS,

	DCLK_ID_EMIFA = CLK_NODE_EMA_CLKSRC * DCLK_ID_GRP_SZ,

	DCLK_ID_SYSCFG = CLK_NODE_PLL0_SYSCLK4 * DCLK_ID_GRP_SZ,
	DCLK_ID_GPIO,
	DCLK_ID_PLLCS,
	DCLK_ID_PSCS,
	DCLK_ID_I2C1,
	DCLK_ID_EMAC_MDIO,
	DCLK_ID_USB1_1,
	DCLK_ID_ARM_INTC,

	DCLK_ID_ARM = CLK_NODE_PLL0_SYSCLK6 * DCLK_ID_GRP_SZ,

	DCLK_ID_EMAC_RMII = CLK_NODE_PLL0_SYSCLK7 * DCLK_ID_GRP_SZ,

	DCLK_ID_I2C0 = CLK_NODE_PLL0_AUXCLK * DCLK_ID_GRP_SZ,
	DCLK_ID_TIMER64P0,
	DCLK_ID_TIMER64P1,
	DCLK_ID_RTC,
	DCLK_ID_USB2_0_PHY,
	DCLK_ID_MCASP0_SCLK,

	DCLK_ID_DDR2_MDDR_PHY = CLK_NODE_PLL1_SYSCLK1 * DCLK_ID_GRP_SZ,

	DCLK_ID_ECAPS = CLK_NODE_ASYNC3 * DCLK_ID_GRP_SZ,
	DCLK_ID_UART1,
	DCLK_ID_UART2,
	DCLK_ID_TIMER64P2,
	DCLK_ID_TIMER64P3,
	DCLK_ID_EHRPWMS,
	DCLK_ID_MCBSPS,
	DCLK_ID_MCASP0,
	DCLK_ID_SPI1,
} dev_clk_id_t;

#endif//__AM18X_PLL_H__