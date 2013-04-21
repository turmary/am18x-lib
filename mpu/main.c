// tary, 1:57 2013/4/22
#include "am18x_lib.h"
#include "auxlib.h"

const uint32_t f_osc = F_OSCIN;

static am18x_rt mpu_print(const char* name, MPU_con_t* mcon) {
	MPU_range_t* rng;
	int fn, pn;
	int i;

	printk("%s\n", name);
	printk("CONFIG = 0x%.8X\n", mcon->CONFIG);

	i = __field_xget(mcon->CONFIG, CONFIG_ADDR_WIDTH_MASK);
	printk("Addr width = %d\n", i);

	i = __field_xget(mcon->CONFIG, CONFIG_NUM_AIDS_MASK);
	printk("AIDs count = %d\n", i);

	i = __field_xget(mcon->CONFIG, CONFIG_ASSUME_ALLOWED_MASK);
	printk("Assume allowed %s\n", i? "yes": "no");

	fn = __field_xget(mcon->CONFIG, CONFIG_NUM_FIXED_MASK);
	rng = &mcon->FXD;
	for (i = 0; i < fn; i++) {
		printk("Fixed range %.2d ", i);
		printk("[ 0x%.8X - 0x%.8X ]\n", rng->MPSAR, rng->MPEAR);
		rng++;
	}

	pn = __field_xget(mcon->CONFIG, CONFIG_NUM_PROG_MASK);
	rng = &mcon->PROGx[0];
	for (i = 0; i < pn; i++) {
		printk("Prog  range %.2d ", i);
		printk("[ 0x%.8X - 0x%.8X ]\n", rng->MPSAR, rng->MPEAR);
		rng++;
	}
	return AM18X_OK;
}

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for am1808 mpu!\n";

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	mpu_print("MPU1 Setting", MPU1);
	psc_state_transition(PSC_DDR2, PSC_STATE_ENABLE);
	mpu_print("MPU2 Setting", MPU2);
	return 0;
}
