// tary, 20:51 2017/6/20
#include "am18x_lib.h"
#include "systick.h"
#include "auxlib.h"
#include "arm920t.h"

const uint32_t f_osc = F_OSCIN;

// AM1808 LCDC pins
// 1018107A_4-3_LCD_Schematic.pdf
// 1016572B_AM1808_OMAP-L138_Baseboard_Schematic.pdf
// 1015115C_AM1808_SOM-M1_Schematic.pdf

// LCD CONNECTOR,  LCD-4.3, AM1808_Baseboard, AM1808_SOM-M1
// ,      R_LCD_BACKLIGHT_PWR, GP2[15],   SPI1_SCS[1]
// ,              R_PWM0,      GP0[7],    AXR15

// gpio #
#define LCDC_BL_PWR	GPIO_BANK2, GPIO_PIN_15
// #define LCDC_BL_PWM	GPIO_BANK0, GPIO_PIN_7

// AXR15/EPWM0TZ[0]/ECAP2_APWM2/GP0[7] as ECAP2_APWM2
#define LCDC_BL_PWM_PINMUX	1,0,4

ecap_conf_t ecap_conf[1] = {
	{
		1000,
		50,
		ECAP_ENABLE | ECAP_ACTIVE_HIGH,
	}
};

#define ECAP_HW		ECAP2

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for ecap!\n";
	int i;

	arm_intr_enable();
	systick_start();

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	psc_state_transition(PSC_GPIO, PSC_STATE_ENABLE);
	psc_state_transition(PSC_ECAP, PSC_STATE_ENABLE);

	syscfg_pinmux(LCDC_BL_PWM_PINMUX);

	gpio_set_mux(LCDC_BL_PWR, GPIO_DIR_OUTPUT);
	gpio_set_output1(LCDC_BL_PWR, GPIO_HIGH);
	#if 0
	gpio_set_mux(LCDC_BL_PWM, GPIO_DIR_OUTPUT);
	gpio_set_output1(LCDC_BL_PWM, GPIO_HIGH);
	#endif

	ecap_init(ECAP_HW);

	for (i = 0;; i += 5) {
		if (i > 100) {
			i = 0;
		}
		ecap_conf->duty = i;
		ecap_set_conf(ECAP_HW, ecap_conf);

		systick_sleep(1000);
	}

	return 0;
}
