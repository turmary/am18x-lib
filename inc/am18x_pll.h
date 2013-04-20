// tary, 17:27 2013/4/14

#ifndef __AM18X_PLL_H__
#define __AM18X_PLL_H__

#include "am18x_map.h"

typedef enum {
	CLK_NODE_INVALID,

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

	CLK_NODE_PLL0_PLLEN,
	CLK_NODE_PLL_EXTSRC,
	CLK_NODE_POSTDIV0,
	CLK_NODE_PLLM0,
	CLK_NODE_PREDIV0,
	CLK_NODE_PLL_CLKMODE,

	CLK_NODE_DIV4_5X,
	CLK_NODE_DIV4_5,

	CLK_NODE_OSCDIV0,
	CLK_NODE_OCSEL0_OCSRC,

	CLK_NODE_PLL1_PLLEN,
	CLK_NODE_POSTDIV1,
	CLK_NODE_PLLM1,

	CLK_NODE_OSCDIV1,
	CLK_NODE_OCSEL1_OCSRC,

	CLK_NODE_OSCIN,
	CLK_NODE_CNT,
} clk_node_id_t;

typedef uint32_t (*pll_calc_freq_t) (uint32_t parent);

typedef struct {
	cuint32_t	id;
	const char*	name;
	uint32_t	parent;
#define CN_FLAG_DIV			0x00000001UL
#define CN_FLAG_MULT			0x00000002UL
#define CN_FLAG_MULTI_DIV		0x00000003UL
#define CN_FLAG_MUX			0x00000004UL
#define CN_FLAG_REREAD			0x00000008UL
#define CN_FLAG_RECALC			0x00000010UL
#define CN_FLAG_VISITED			0x00000020UL
	uint32_t	flag;
	uint32_t	multiplier;
	uint32_t	divider;
	pll_calc_freq_t	calc_freq;
	pll_calc_freq_t do_change;
	uint32_t*	parent_list;
	uint32_t	freq;
} clk_node_t;

extern clk_node_t clk_nodes[];

am18x_rt clk_node_init(void);
am18x_rt clk_node_output(void);
am18x_rt clk_node_tree(void);
am18x_rt clk_node_recalc_freq(void);
uint32_t clk_node_get_freq(uint32_t id);
am18x_rt clk_node_change_parent(uint32_t id, uint32_t parent);

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

uint32_t dev_get_freq(uint32_t dclk_id);

typedef enum {
	PLL_CFLAG_EXT_CLK_OSCIN = 0x0,
	PLL_CFLAG_EXT_CLK_PLL1  = BIT(0),
	PLL_CFLAG_REF_CRYSTAL = 0x0,
	PLL_CFLAG_REF_SQUARE  = BIT(1),
	PLL_CFLAG_FROM_NORMAL = 0x0,
	PLL_CFLAG_FROM_POWER_DOWN = BIT(2),
} PLL_CFLAG_flag_t;

typedef enum {
	PLL_CMD_SOFT_RESET,
	PLL_CMD_ENABLE_PLL1_DIVS,
} pll_cmd_t;

typedef enum {
	PLL_RESET_SOFTWARE,
	PLL_RESET_EXTERNAL,
	PLL_RESET_POWER_ON,
} pll_reset_t;

typedef struct {
	uint8_t		prediv;
	uint8_t		pllm;
	uint8_t		postdiv;
	uint8_t		plldiv[7];
	uint16_t	cflag;
} pll_conf_t;

am18x_rt pll_changing_sysclk_dividers(PLL_con_t* pcon, uint32_t plldivn, uint32_t divider);
am18x_rt pll_conf(PLL_con_t* pcon, const pll_conf_t* conf);
am18x_rt pll_cmd(PLL_con_t* pcon, uint32_t cmd, uint32_t arg);
pll_reset_t pll_get_reset(void);

#endif//__AM18X_PLL_H__
