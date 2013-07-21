// tary, 21:05 2013/6/23
#include "am18x_lib.h"
#include "arm920t.h"
#include "systick.h"
#include "auxlib.h"
#include "sdmmc.h"

const uint32_t f_osc = F_OSCIN;

uint32_t buf[MMCSD_BLOCK_SIZE * 2];

int prepare_txbuf(uint8_t* p, uint32_t size, uint8_t start) {
	int i;

	for (i = 0; i < size; i++) {
		p[i] = start + i;
	}
	return 0;
}

int sdmmc_dbg(unsigned blk, unsigned cnt, unsigned start) {
	sdmmc_rt r;

	r = sdmmc_init();
	if (r != SDMMC_OK) {
		printk("SDMMC init %s\n", sdmmc_err_string(r));
		return -1;
	}

	prepare_txbuf((uint8_t*)buf, cnt * MMCSD_BLOCK_SIZE, start);
	r = sdmmc_write_block(blk, cnt, buf);
	if (r != SDMMC_OK) {
		printk("SDMMC write block %s\n", sdmmc_err_string(r));
		return -2;
	}

	r = sdmmc_read_block(blk, cnt, buf);
	if (r != SDMMC_OK) {
		printk("SDMMC read block %s\n", sdmmc_err_string(r));
		return -3;
	}
	debug_buf("rxbuf", (char*)buf, cnt * MMCSD_BLOCK_SIZE);
	return 0;
}

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for mmc/sd!\n";

	arm_intr_enable();
	systick_start();

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	sdmmc_dbg(4, 1, 0x55);

	return 0;
}
