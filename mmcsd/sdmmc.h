// tary, 21:25 2011/7/15
#ifndef __SDMMC_H__
#define __SDMMC_H__

typedef enum {
	SDMMC_OK = 0,
	SDMMC_NO_RSP = -1,
	SDMMC_CRC_ERR = -2,
	SDMMC_UNSUP = -3,
	SDMMC_ERR = -4,
} sdmmc_rt;

sdmmc_rt sdmmc_init(void);
sdmmc_rt sdmmc_read_block(uint32_t blk_nr, uint32_t blk_cnt, uint32_t* buf);
sdmmc_rt sdmmc_write_block(uint32_t blk_nr, uint32_t blk_cnt, const uint32_t* buf);
const char* sdmmc_err_string(int rt);

#endif//__SDMMC_H__
