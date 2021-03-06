// tary, 15:46 2015/4/5
#include "am18x_lib.h"
#include "arm920t.h"
#include "tft43.h"
#include "auxlib.h"
#include "uart.h"
#include "systick.h"
#include "dvfs.h"

// AM1808 LCDC pins

// 1012014A_LCD-4.3_Schematic.pdf
// 1015526A_AM1808_Baseboard_Schematic.pdf
// 1015640A_AM1808_SOM-M1_Schematic.pdf

// LCD CONNECTOR,  LCD-4.3, AM1808_Baseboard, AM1808_SOM-M1

// S_R_LCD_VSYNC, R_LCD_VSYNC, LCD_VSYNC, MMCSD1_DAT[4]
// S_R_LCD_HSYNC, R_LCD_HSYNC, LCD_HSYNC, MMCSD1_DAT[5]
// DISP,      R_LCD_PANEL_PWR, GP2[8],    EMA_BA[0]
// S_R_LCD_DCLK,  R_LCD_DCLK,  LCD_PCLK,  MMCSD1_DAT[7]
// ,      R_LCD_BACKLIGHT_PWR, GP2[15],   SPI1_SCS[1]
// ,              R_PWM0,      GP2[14],   SPI1_SCS[0]
// pinmux
uint32_t lcdc_pins[][3] = {
	{19,4,2},	// VSYNC
	{19,0,2},	// HSYNC
	{18,24,2},	// PCLK

	{17,8,2},	// D15
	{17,12,2},	// D14
	{17,16,2},	// D13
	{17,20,2},	// D12
	{17,24,2},	// D11
	{17,28,2},	// D10
	{18,0,2},	// D9
	{18,4,2},	// D8
	{16,8,2},	// D7
	{16,12,2},	// D6
	{16,16,2},	// D5
	{16,20,2},	// D4
	{16,24,2},	// D3
	{16,28,2},	// D2
	{17,0,2},	// D1
	{17,4,2},	// D0
};

// gpio #
#define LCDC_PWR	GPIO_BANK2, GPIO_PIN_8
#define LCDC_BL_PWR	GPIO_BANK2, GPIO_PIN_15
#define LCDC_BL_PWM	GPIO_BANK2, GPIO_PIN_14

#define DDR_RAM_BASE	0xC0000000UL

#define _16BPP_R_MASK	0xF800
#define _16BPP_G_MASK	0x07E0
#define _16BPP_B_MASK	0x001F

#define PALETTE_DATA	0
#define DATA_ONLY	1
#define FRAME_MODE	DATA_ONLY

lcd_conf_t lcd_cf[] = {
{
	.pclk = 480 * 272,
	.width = 480, .height = 272,
	.hfp = 2,
	.hsw = 41,
	.hbp = 2,
	.vfp = 3,
	.vsw = 10,
	.vbp = 3,
	.bpp = LCD_BPP_16,
	.hvsync = LCD_HVSYNC_PCLK,
	.cflag = LCD_CFLAG_BIAS_LOW |
		LCD_CFLAG_PIXEL_RISING |
		LCD_CFLAG_HSYNC_LOW |
		LCD_CFLAG_VSYNC_LOW,
	.fb0_base = DDR_RAM_BASE,
},
};

static uint16_t* palette = (uint16_t*)DDR_RAM_BASE;
static uint16_t* fb0;
static uint16_t colors[] = {
	_16BPP_R_MASK,
	_16BPP_G_MASK,
	_16BPP_B_MASK,
};

#define KV_LCD(x)	{LCD_INTR_##x, #x}
static kv_t intrs_kv[] = {
	KV_LCD(AC),
	KV_LCD(DONE),
	KV_LCD(PL),
	KV_LCD(SL),
	KV_LCD(FUF),
	KV_LCD(EOF),
	KV_LCD(EOF1),
};

static void lcdc_isr(void) {
	int i, k;

	k = 0;
	for (i = 0; i < countof(intrs_kv); i++) {
		if (lcd_intr_state(LCD0, intrs_kv[i].key) == AM18X_TRUE) {
			printk("*%s ", intrs_kv[i].val);
			k++;
		}
	}
	if (k) {
		printk("\n");
	}

	if (lcd_intr_state(LCD0, LCD_INTR_PL) == AM18X_TRUE) {
#if FRAME_MODE	== DATA_ONLY
		lcd_cmd(LCD0, LCD_CMD_RASTER_DIS, 0);
		lcd_cmd(LCD0, LCD_CMD_DATA, 0);
		lcd_cmd(LCD0, LCD_CMD_FB_SET, (uint32_t)fb0);
		lcd_cmd(LCD0, LCD_CMD_RASTER_EN, 0);
#endif
		lcd_intr_clear(LCD0, LCD_INTR_PL);
	}
	if (lcd_intr_state(LCD0, LCD_INTR_SL) == AM18X_TRUE) {
		lcd_cmd(LCD0, LCD_CMD_RASTER_DIS, 0);
		lcd_intr_clear(LCD0, LCD_INTR_SL);
		lcd_cmd(LCD0, LCD_CMD_RASTER_EN, 0);
		// for (;;);
	}
	if (lcd_intr_state(LCD0, LCD_INTR_EOF) == AM18X_TRUE) {
		lcd_intr_clear(LCD0, LCD_INTR_EOF);
	}
	return;
}

int lcd_intr_init(void) {
	lcd_intr_enable(LCD0, LCD_INTR_AC);
	lcd_intr_enable(LCD0, LCD_INTR_DONE);
	lcd_intr_enable(LCD0, LCD_INTR_PL);
	lcd_intr_enable(LCD0, LCD_INTR_SL);
	lcd_intr_enable(LCD0, LCD_INTR_FUF);
	lcd_intr_enable(LCD0, LCD_INTR_EOF);

	isr_set_handler(AINTC_LCDC_INT, lcdc_isr);

	aintc_sys_enable(AINTC_LCDC_INT);
	return 0;
}

int tft43_init(void) {
	int i;

	dvfs_set_opp(OPP_OSC);

	psc_state_transition(PSC_GPIO, PSC_STATE_ENABLE);
	psc_state_transition(PSC_LCDC, PSC_STATE_ENABLE);

	for (i = 0; i < countof(lcdc_pins); i++) {
		syscfg_pinmux(lcdc_pins[i][0], lcdc_pins[i][1], lcdc_pins[i][2]);
	}

	gpio_set_mux(LCDC_PWR, GPIO_DIR_OUTPUT);
	gpio_set_output1(LCDC_PWR, GPIO_HIGH);
	gpio_set_mux(LCDC_BL_PWR, GPIO_DIR_OUTPUT);
	gpio_set_output1(LCDC_BL_PWR, GPIO_HIGH);
	gpio_set_mux(LCDC_BL_PWM, GPIO_DIR_OUTPUT);
	gpio_set_output1(LCDC_BL_PWM, GPIO_HIGH);

	lcd_conf(LCD0, lcd_cf);

	// 23.2.5.2 Frame Buffer
	palette[0] = 0x4000;
	for (i = 1; i < 16; i++) {
		palette[i] = 0x0;
	}
	fb0 = &palette[16];

	lcd_intr_init();

#if FRAME_MODE == DATA_ONLY
	lcd_cmd(LCD0, LCD_CMD_PALETTE, 0);
#endif
	dump_regs_word("FB0", palette, 64);
	arm_intr_enable();
	lcd_cmd(LCD0, LCD_CMD_RASTER_EN, 0);

	return 0;
}

int set_color(uint16_t color) {
	int i;

	for (i = 0; i < lcd_cf->width * lcd_cf->height; i++) {
		fb0[i] = color;
	}
	return 0;
}

int switch_colors(void) {
	int i, c, n = countof(colors);

	c = colors[0];
	for (i = 0; i < n - 1; i++) {
		colors[i] = colors[i + 1];
	}
	colors[i] = c;
	return 0;
}

int paint_quadrangle(void) {
	uint16_t color;
	int x, y;

	for (x = 0; x < lcd_cf->width; x++) {
		for (y = 0; y < lcd_cf->height; y++) {
			if (x < lcd_cf->width / 3 || x >= lcd_cf->width * 2 / 3) {
				color = colors[0];
			} else if (y < lcd_cf->height / 3 || y >= lcd_cf->height * 2 / 3) {
				color = colors[1];
			} else {
				color = colors[2];
			}
			fb0[y * lcd_cf->width + x] = color;
		}
	}
	return 0;
}

int tft43_colors(void) {
	uint16_t color;

	color = 0;
	for (;;) {
#if 0
		switch(color) {
		case _16BPP_R_MASK:
			color = _16BPP_G_MASK;
			break;
		case _16BPP_G_MASK:
			color = _16BPP_B_MASK;
			break;
		case _16BPP_B_MASK:
		default:
			color = _16BPP_R_MASK;
			break;
		}
		set_color(color);
#else
		paint_quadrangle();
		switch_colors();
#endif
		systick_sleep(1000);
	}
	return 0;
}
