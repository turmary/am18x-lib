// tary, 15:46 2015/4/5
#include "am18x_lib.h"
#include "tft43.h"
#include "auxlib.h"
#include "am18x_lcd.h"

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

lcd_conf_t lcd_cf[] = {
{
	.pclk = 480*720*45,
	.width = 480, .height = 272,
	.hfp = 2, 41, 2,
	.vfp = 3, 10, 3,
	.bpp = LCD_BPP_16,
	.hvsync = LCD_HVSYNC_PCLK,
	.cflag = LCD_CFLAG_BIAS_HIGH |
		LCD_CFLAG_PIXEL_RISING |
		LCD_CFLAG_HSYNC_HIGH |
		LCD_CFLAG_VSYNC_HIGH,
	.fb0_base = DDR_RAM_BASE,	
},
};

int tft43_init(void) {
	int i, r;

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

	lcd_cmd(LCD0, LCD_CMD_RASTER_EN, 0);

	return 0;
}
