// tary, 23:47 2013/10/27
#include "am18x_lib.h"
#include "arm920t.h"
#include "systick.h"
#include "auxlib.h"

const uint32_t f_osc = F_OSCIN;

/* static const ddr_conf_t mt46h64m16_6 = {
	.ddr2_not_mddr = AM18X_FALSE,
	.page_size = 10,
	.row_size  = 14,
	.bank_cnt  = 4,

	.freq_ck = 166000000,
	.trefi   = 7812, // ns

	.cl   = 3,
	.trfc = 100,
	.trp  = 18,
	.trcd = 18,

	.twr  = 15,
	.tras = 42,
	.trc  = 60,
	.trrd = 12,

	.twtr = 6,
	.todt = 0,
	.txsnr = 132,
	.trtp = 18,

	.txp   = 2,
	.txsrd = 22,
	.tcke  = 1,

	.trasmax = 70000,
	.pasr = 0,
}; */

static unsigned long* ddr_mem = (unsigned long*)0xC0000000UL;

static int ddr_mem_test(void) {
	int i;

	/*for (i = 0; i < 16; i++) {
		ddr_mem[i] = i;
	}
	dump_regs_word("CLOSE DDR", (unsigned)ddr_mem, 64);

	ddr_initialize(DDR0, &mt46h64m16_6);
	// dump_regs_word("DDR0.i", DDR0, 0xE8);
	*/

	for (i = 0; i < 16; i++) {
		ddr_mem[i] = i;
	}
	dump_regs_word("OPEN  DDR", (unsigned)ddr_mem, 64);

	ddr_clock_off(DDR0);
	dump_regs_word("OFF   DDR", (unsigned)ddr_mem, 64);

	ddr_clock_on(DDR0);
	// dump_regs_word("DDR0.o", DDR0, 0xE8);
	dump_regs_word("ON    DDR", (unsigned)ddr_mem, 64);

	return 0;
}

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for DDR2/mDDR!\n";

	arm_intr_enable();
	systick_start();

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	ddr_mem_test();

	return 0;
}
