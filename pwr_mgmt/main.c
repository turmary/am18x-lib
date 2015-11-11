// tary, 5:40 2013/4/17
#include "am18x_lib.h"
#include "arm920t.h"
#include "systick.h"
#include "tps6507x.h"
#include "auxlib.h"
#include "uart.h"
#include "dvfs.h"
#include "psc_config.h"
#include "tca6416.h"
#include "am1808exp.h"

const uint32_t f_osc = F_OSCIN;

// Page 199, 9.6 ARM Sleep Mode Management
// 9.6.1 ARM Wait-For-Interrupt Sleep Mode
static uint32_t one_second_counter(am18x_bool with_wfi) {
	uint32_t milli_seconds = 1000;
	uint32_t counter;

	counter = 0;
	systick_timeout(0);
	while (systick_timeout(milli_seconds) == 0) {
		counter++;
		if (with_wfi) {
			arm_wfi();
		}
	}
	return counter;
}

static void chipsig0_isr(void) {
	SYSCFG0->CHIPSIG_CLR = FIELD_SET(0, CHIPSIG_X_MASK(0), CHIPSIG_X_clear(0));
	printk("%s()\n", __func__);
	pru_dump_regs(PRU0);
	printk("\n");
	return;
}

/*
static void psc0_isr(void) {
	printk("%s()\n", __func__);
	return;
}
*/

// 9.6.2 ARM Clock OFF
// The following sequence should be executed by the ARM within
// the ARM Clock Stop Request interrupt ISR
static void arm_clock_off_isr(void) {
	/*
	printk("%s()\n", __func__);
	psc_dump_regs(PSC0);
	*/

	// clear pending
	aintc_clear(AINTC_ARMCLKSTOPREQ);
	aintc_sys_disable(AINTC_ARMCLKSTOPREQ);

	// 1. Check for completion of all ARM master requests
	// (the ARM polls transfer completion statuses of all
	// Master peripherals).

	// 2. Enable the interrupt to be used as the wake-up interrupt
	// that will be used to wake-up the ARM during the ARM
	// clock-on sequence.
	isr_set_handler(AINTC_SYSCFG_CHIPINT0, chipsig0_isr);
	aintc_sys_enable(AINTC_SYSCFG_CHIPINT0);

	// 3. Execute the wait-for-interrupt (WFI) ARM instruction.
	#if 1
	arm_wfi();

	#else
	{
	int i;

	for (i = 0; i < 1000; i++) {
		asm volatile("nop");
	}
	}
	
	asm volatile(
	"mov	r0, #0\n"
	"mcr	p15, 0, r0, c7, c0, 4\n"	/* wait for interrupt */
	::: "r0"
	);
	#endif

	puts("&");

	return;
}

// should be executed by other master as dsp, pru, etc.
// 9.6.3 ARM Subsystem Clock ON
static uint32_t arm_clock_off_and_on(void) {
	PRU_con_t* pru = PRU0;
	am18x_rt r;
	uint32_t* pram;

	// 1. The ARM must have the ARM Clock Stop Request interrupt
	// enabled and the associated interrupt serive routine (ISR)
	// set up before the folloing ARM clock shutdown procedure.
	isr_set_handler(AINTC_ARMCLKSTOPREQ, arm_clock_off_isr);
	aintc_sys_enable(AINTC_ARMCLKSTOPREQ);

	/*
	psc_enable_interrupt(PSC_ARM);
	isr_set_handler(AINTC_PSC0_ALLINT, psc0_isr);
	aintc_sys_enable(AINTC_PSC0_ALLINT);
	*/

#if 0
	psc_state_transition(PSC_ARM, PSC_STATE_DISABLE);
	// SYSCFG0->CHIPSIG = FIELD_SET(0, CHIPSIG_X_MASK(0), CHIPSIG_X_assert(0));
	psc_state_transition(PSC_ARM, PSC_STATE_ENABLE);

#else
	psc_state_transition(PSC_PRU, PSC_STATE_ENABLE);

	pru_cmd(pru, PRU_CMD_ENABLE, 0);

	pram = (uint32_t*)PRU_DataRAM0_BASE;
	pram[0] = 2;
	pram[1] = ((0) << 24)	|
		((0) << 16)	|
		((PSC_ARM) << 8)|
		((MDSTATx_STATE_Disable) << 0);
	pram[2] = ((0) << 24)	|
		((0) << 16)	|
		((PSC_ARM) << 8)|
		((MDSTATx_STATE_Enable) << 0);
	pru_load(pru, (const uint32_t*)pru_code, countof(pru_code));

	/*
	// prepare to trigger chipsig0
	isr_set_handler(AINTC_SYSCFG_CHIPINT0, chipsig0_isr);
	aintc_sys_enable(AINTC_SYSCFG_CHIPINT0);
	*/

	printk("Press any key to clock off arm\n");
	getchar();
	pru_cmd(pru, PRU_CMD_RUN, 0);
	while (psc_get_state(PSC_ARM) != PSC_STATE_ENABLE) {
		arm_wfi();
		printk("$");
	}
	/*
##############################&chipsig0_isr()
CONTROL       [0x01C37000] = 0x0000800B
STATUS        [0x01C37004] = 0x00000029
WAKEUP        [0x01C37008] = 0x00000000
CYCLECNT      [0x01C3700C] = 0x039804F6
STALLCNT      [0x01C37010] = 0x00006F95
CONTABBLKIDX0 [0x01C37020] = 0x00000000
CONTABPROPTR  [0x01C37028] = 0x00000000
INTGPR        [0x01C37400] = 0x00000000
INTCTER       [0x01C37480] = 0x00000000

##############################chipsig0_isr()
CONTROL       [0x01C37000] = 0x00000009
STATUS        [0x01C37004] = 0x0000003B
WAKEUP        [0x01C37008] = 0x00000000
CYCLECNT      [0x01C3700C] = 0x07280C7B
STALLCNT      [0x01C37010] = 0x0000DEBD
CONTABBLKIDX0 [0x01C37020] = 0x00000000
CONTABPROPTR  [0x01C37028] = 0x00000000
INTGPR        [0x01C37400] = 0x01C14174
INTCTER       [0x01C37480] = 0x00004000

$arm_clock_off_and_on() complete!

	***** PSC_ARM work normal after twice wfi operations ******
	one in the arm clock off interrupt,
	the other after arm clock on, before PSC_Enable state.
	*/
	do {
		psc_dump_regs(PSC0);
		printk("\n");
	} while ((r = pru_cmd(pru, PRU_CMD_IS_HALT, 0)) != AM18X_OK);
	psc_state_transition(PSC_PRU, PSC_STATE_DISABLE);
#endif

	return 0;
}

#define KV_X(x)		{ PWR_TYPE_##x, #x }
kv_t kv_powers[] = {
	KV_X(DCDC1),
	KV_X(DCDC2),
	KV_X(DCDC3),
	KV_X(LDO1),
	KV_X(LDO2),
};

static int wfi_test(void) {
	pll_conf_t pllconf[1];

	printk("\n******************** %s() ********************\n", __func__);

	printk("one second counter\n");
	pll_get_conf(PLL0, pllconf);
	// pllconf->cflag |= PLL_CFLAG_FROM_POWERON;
	pll_set_conf(PLL0, pllconf);
	clk_node_recalc();
	uart_init();
	printk("pll enabled counter = %d\n", one_second_counter(AM18X_FALSE));
	pll_cmd(PLL0, PLL_CMD_POWER_DOWN, 0);
	clk_node_recalc();
	uart_init();
	printk("pll bypass  counter = %d\n", one_second_counter(AM18X_FALSE));

	printk("one second counter\n");
	printk("without wfi counter = %d\n", one_second_counter(AM18X_FALSE));
	printk("with    wfi counter = %d\n", one_second_counter(AM18X_TRUE));
	return 0;
}

static int poweron_pin_test(void) {
	printk("\n******************** %s() ********************\n", __func__);

	// tps65070 power_on pin don't work
	psc_state_transition(PSC_GPIO, PSC_STATE_ENABLE);
	gpio_set_mux(TPS65070_POWER_ONn, GPIO_DIR_OUTPUT);
	// gpio_set_mux(TPS65070_POWER_ONn, GPIO_DIR_INPUT);
	gpio_set_mux(TPS65070_PB_OUT, GPIO_DIR_INPUT);

	gpio_set_output1(TPS65070_POWER_ONn, GPIO_HIGH);

	printk("SET TPS65070 POWER_ON = LOW\n");
	printk("TPS65070_POWER_ONn = %d\n", gpio_get_input1(TPS65070_POWER_ONn));
	printk("TPS65070_PB_OUT   = %d\n", gpio_get_input1(TPS65070_PB_OUT));

	gpio_set_output1(TPS65070_POWER_ONn, GPIO_LOW);

	printk("SET TPS65070 POWER_ON = HIGH\n");
	printk("TPS65070_POWER_ONn = %d\n", gpio_get_input1(TPS65070_POWER_ONn));
	printk("TPS65070_PB_OUT   = %d\n", gpio_get_input1(TPS65070_PB_OUT));

	return 0;
}

static int arm_clock_off_test(void) {
	printk("\n******************** %s() ********************\n", __func__);

	// arm clock off worked
	aintc_sys_disable(AINTC_T64P0_TINT12);
	arm_clock_off_and_on();
	printk("%s() complete!\n", "arm_clock_off_and_on");
	aintc_sys_enable(AINTC_T64P0_TINT12);
	return 0;
}

static int pmu_init(void) {
	int i, r;

	// tps6507x_conf();
	tps6507x_dump_regs();

	for (i = 0; i < 4; i++) {
		if (i & 0x01) {
			r = tps6507x_get_adc(PWR_TYPE_AC);
			printk("power ac  ");
		} else {
			r = tps6507x_get_adc(PWR_TYPE_SYS);
			printk("power sys ");
		}
		r = r * 1000 * 6 / 0x400UL;
		printk(" voltage: %.4d mV\n", r);
		systick_sleep(100);
	}

	for (i = 0; i < countof(kv_powers); i++) {
		r = tps6507x_get_output(kv_powers[i].key);
		printk("%-5s voltage: %.4d mV\n", kv_powers[i].val, r);
	}

	printk("Setting output voltages\n");
	// tps6507x_set_output(PWR_TYPE_DCDC3, 1300);
	// tps6507x_set_output(PWR_TYPE_LDO1, 1600);

	// am1808.pdf
	// 4.2 Recommanded Operating Conditions
	// Internal RAM Supply Voltage
	// 456MHz versions 1.3V
	tps6507x_set_output(PWR_TYPE_LDO2, 1300);
	for (i = 0; i < countof(kv_powers); i++) {
		r = tps6507x_get_output(kv_powers[i].key);
		printk("%-5s voltage: %.4d mV\n", kv_powers[i].val, r);
	}
	return 0;
}

// Page 201, 9.8 Dynamic Voltage and Frequency Scaling(DVFS)
static int dvfs_test(void) {
	int cnt = -1;

	printk("\n******************** %s() ********************\n", __func__);
	while (cnt++ < 5 * 5 / 2) {
		dvfs_set_opp(cnt % OPP_CNT);
		printk("Current OPerating Point: %5d mV\n", dvfs_get_volt(dvfs_get_opp()));
		printk("Current Frequency:   %9d Hz\n", dev_get_freq(DCLK_ID_ARM));
		#if 0
		if (dvfs_get_opp() == OPP_CNT - 1) {
			clk_node_tree();
			break;
		}
		#endif
		systick_sleep(200);
	}
	while (cnt-- > 0) {
		dvfs_set_opp(cnt % OPP_CNT);
		printk("Current OPerating Point: %5d mV\n", dvfs_get_volt(dvfs_get_opp()));
		printk("Current Frequency:   %9d Hz\n", dev_get_freq(DCLK_ID_ARM));
		systick_sleep(200);
		if (cnt <= 5) getchar();
	}

	return cnt;
}

// Page 202, 9.9 Deep Sleep Mode
// This device supports a Deep Sleep mode where all device clocks
// are stopped and the on-chip oscillator is
// shutdown to save power.
// Registers and memory are preserved, thus, upon recovery, the
// program may continue from where it left off with minimal overhead involved.

// 9.9.1.1 Entering Deep Sleep Mode
static int deepsleep_externally_enter(void) {
	uint32_t reg, msk;

	// 1. To preserve DDR2/mDDR memory contents, activate the self-refresh mode
	// and gate the clocks to the DDR2/mDDR memory controller.
	// You can use partial array self-refresh(PARS) for additional power
	// savings for mDDR memory.
	printk("Press any key to clock off ddr\n");
	getchar();
	ddr_clock_off(DDR0);

	// 2. The SATA PHY should be disabled.
	// 3. The USB2.0(USB0) PHY should be disabled, if this interface is used and
	// internal clocks are selected.
	// 4. The USB1.1(USB1) PHY should be disabled, if this interface is used and
	// internal clocks are selected.
	printk("Press any key to adjust dcdc2 output with 2.4V\n");
	getchar();
	tps6507x_set_output(PWR_TYPE_DCDC2, 2400);

	printk("Press any key to continue\n");
	getchar();

	// 5. PLL/PLLC0 and PLL/PLLC1 should be placed in bypass mode(clear the PLLEN
	// bit in the PLL control register(PLLCTL) of each PLLC to 0).
	pll_cmd(PLL0, PLL_CMD_BYPASS, 0);
	pll_cmd(PLL1, PLL_CMD_BYPASS, 0);

	// 6. PLL/PLLC0 and PLL/PLLC1 should be powered down(set the PLLPWRDN
	// bit in PLLCTL of each PLLC to 1).
	pll_cmd(PLL0, PLL_CMD_POWER_DOWN, 0);
	pll_cmd(PLL1, PLL_CMD_POWER_DOWN, 0);
	clk_node_recalc();
	uart_init();

	// 7. Configure the nDEEPSLEEP pin as input-only using the PINMUX0_31_28 bits
	// in the PINMUX0 register in the System Configuration(SYSCFG) Module chapter.
	syscfg_pinmux(0, 28, 0);

	// 8. The external controller should drive nDEEPSLEEP pin high(not in Deep Sleep).

	// 9. Configure the desired delay in the SLEEPCOUNT bit field in the
	// deep sleep register(DEEPSLEEP) in the System Configuration(SYSCFG) Module
	// chapter. This count determines the delay before the
	// Deep Sleep logic releases the clocks to the device during wake up
	// (allowing the oscillator to stabilize).
	reg = SYSCFG1->DEEPSLEEP;
	msk = DEEPSLEEP_SLEEPCOUNT_MASK;
	reg = FIELD_SET(reg, msk, DEEPSLEEP_SLEEPCOUNT_VAL(0x8000));
	SYSCFG1->DEEPSLEEP = reg;

	// 10. Set the SLEEPENABLE bit in DEEPSLEEP to 1.
	// This automatically clears the SLEEPCOMPLETE bit.
	msk = DEEPSLEEP_ENABLE_MASK;
	reg = FIELD_SET(reg, msk, DEEPSLEEP_ENABLE_yes);
	SYSCFG1->DEEPSLEEP = reg;

	// 11. Begin polling the SLEEPCOMPLETE bit until it is set to 1.
	// This bit set once the device is woken up from Deep Sleep mode.
	printk("Drives nDEEPSLEEP pin (RSA_CTS of UART P1) low to enter Deep Sleep\n"
		"And then drives it high to exit\n", __func__);
	msk = DEEPSLEEP_COMPLETE_MASK;
	do {
		delay(100000);
		printk("&");
		// 12. The external controller drives the nDEEPSLEEP pin low to initiate
		// Deep Sleep mode.
		reg = FIELD_GET(SYSCFG1->DEEPSLEEP, msk);
	} while (reg != DEEPSLEEP_COMPLETE_yes);

	printk("\n");
	printk("%s() Wakeup from Deep Sleep\n", __func__);
	
	return 0;
}

// 9.9.1.2 Exiting Deep Sleep Mode
static int deepsleep_externally_exit(void) {
	uint32_t reg, msk;

	// 1. The external controller drives the nDEEPSLEEP pin high.

	// 2. When the SLEEPCOUNT delay is complete, the Deep Sleep logic releases
	// the clock to the device and sets the SLEEPCOMPLETE bit in the deep sleep
	// register(DEEPSLEEP) in the System Configuration(SYSCFG) Module chapter.

	// 3. Clear the SLEEPENABLE bit in the DEEPSLEEP to 0.
	// This automatically clears the SLEEPCOMPLETE bit.
	reg = SYSCFG1->DEEPSLEEP;
	msk = DEEPSLEEP_ENABLE_MASK;
	reg = FIELD_SET(reg, msk, DEEPSLEEP_ENABLE_no);
	SYSCFG1->DEEPSLEEP = reg;

	// 4. Initialize the PLL controllers as described in Section 7.2.2.2.
	// Note that the state of the PLL controller registers is preserved
	// during Deep Sleep mode.
	// Therefore, it is not necessary to reprogram all the PLL controller
	// registers unless a new setting is desired. At minimum, steps 3,4,
	// and 7-10 of the PLL initialization procedure must be followed.

	// 5. Enable the clocks to the DDR2/mDDR memory controller,
	// reset the DDR PHY, and then take the DDR2/mDDR out of self-refresh mode
	ddr_clock_on(DDR0);

	// 6. Configure the desired states to the peripherals and enable as required.
	printk("%s() all configurations recovered from Deep Sleep!\n", __func__);
	return 0;
}


// 9.9.1 Entering/Exiting Deep Sleep Mode Using Externally Controlled Wake-Up
static int deepsleep_externally_test(void) {
	printk("\n******************** %s() ********************\n", __func__);
	// 1015643A_AM1808_Baseboard_BOM.pdf
	// Set DEEPSLEEP_EN = H, DEEPSLEEP_nEN = L
	// RSA_CTS control DEEPSLEEP pin of AM1808
	tca6416_conf (0xFF22UL);
	tca6416_write(0x0001UL);

	deepsleep_externally_enter();
	deepsleep_externally_exit();
	return 0;
}

static int pmu_power_off_test(void) {
	int i;

	printk("\n******************** %s() ********************\n", __func__);

	// DCDC1 power off will cause reboot failed!
	printk("power off DCDC1\n");
	systick_sleep(100);
	tps6507x_power_switch(PWR_TYPE_DCDC1, AM18X_FALSE);

	// DCDC2 can't power off since it's all I/O power supply
	// power off DCDC2 will shutdown all voltage supply on Baseboard
	// and 1.8V_LDO (shadow of LDO1, by gate off PMOS Q1)
	// and DCDC1 (by shutdown TPS3805H33,U23)
	for (i = 3300; i > 500; i -= 100) {
		int r;

		tps6507x_set_output(PWR_TYPE_DCDC2, i);
		r = tps6507x_get_output(PWR_TYPE_DCDC2);
		printk("%-5s voltage: %.4d mV\n", "DCDC2", r);
		systick_sleep(3000);
	}
	printk("power off DCDC2\n");
	systick_sleep(100);
	tps6507x_power_switch(PWR_TYPE_DCDC2, AM18X_FALSE);
	/*
	systick_sleep(10 * 1000);
	tps6507x_power_switch(PWR_TYPE_DCDC2, AM18X_TRUE);
	*/

	// DCDC3 can't power off since it's am1808 core logic power supply

	// LDO1 can't power off since it's I/O power supply
	/*
	printk("power off LDO1\n");
	systick_sleep(100);
	tps6507x_power_switch(PWR_TYPE_LDO1, AM18X_FALSE);
	*/

	// LDO2 can't power off since it's internal ram power supply

	/*
	printk("power off DCDC3\n");
	systick_sleep(100);
	tps6507x_power_switch(PWR_TYPE_DCDC3, AM18X_FALSE);
	*/

	#if 0
	// power off worked, will reset the system.
	printk("power off usb\n");
	tps6507x_power_switch(PWR_TYPE_USB, AM18X_FALSE);
	printk("power off ac\n");
	tps6507x_power_switch(PWR_TYPE_AC, AM18X_FALSE);
	#endif

	tps6507x_dump_regs();
	return 0;
}

kv_t kv_pscs[] = {
	KV(PSC_PRU),
	KV(PSC_RESERVED0),
	KV(PSC_SCR0),
	KV(PSC_SCR1),
	KV(PSC_SCR2),
	KV(PSC_SPI1),
	KV(PSC_SCR_F0),
	KV(PSC_SCR_F1),
	KV(PSC_SCR_F2),
	KV(PSC_SCR_F6),
	KV(PSC_SCR_F7),
	KV(PSC_SCR_F8),
	KV(PSC_BR_F7),
};

static int psc_pwr_test(void) {
	int i;

	printk("\n******************** %s() ********************\n", __func__);

	for (i = 0; i < countof(kv_pscs); i++) {
		printk("%s clock off\n", kv_pscs[i].val);
		getchar();
		psc_state_transition(kv_pscs[i].key, PSC_STATE_DISABLE);
	};

	printk("%s() psc power test complete!\n", __func__);

	return 0;
}

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for power management!\n";
	int i;

	for (i = 0; i < countof(kv_powers); i++) {
		kv_powers[i].val += get_exec_base();
	}

	for (i = 0; i < countof(kv_pscs); i++) {
		kv_pscs[i].val += get_exec_base();
	}

	arm_intr_enable();
	systick_start();

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	arm_clock_off_test();

	pmu_init();

	dvfs_test();

	wfi_test();

	deepsleep_externally_test();

	poweron_pin_test();

	pmu_power_off_test();

	psc_pwr_test();

	return 0;
}
