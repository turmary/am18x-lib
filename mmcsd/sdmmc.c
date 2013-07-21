// tary, 21:25 2011/7/15
#include "am18x_lib.h"
#include "sd_protocol.h"
#include "mmc_protocol.h"
#include "sdmmc.h"
#include "systick.h"
#include "auxlib.h"

#define MMCSDCON		MMCSD0

#define MMCSD_CLK		10,0,2
#define MMCSD_CMD		10,4,2
#define MMCSD_DAT0		10,8,2
#define MMCSD_DAT1		10,12,2
#define MMCSD_DAT2		10,16,2
#define MMCSD_DAT3		10,20,2
#define MMCSD_WP		10,24,2
#define MMCSD_INS		10,28,2

#define BUS_POWER_VOLTAGE	3300		//mV

#define LOW_CLK			400000		//Hz

#define MMC_RCA			0x1234

#define SDMMC_REG_RETRY		100000
#define SDMMC_CMD_RETRY		20
#define SDMMC_ARG_NULL		0


typedef struct {
	uint16_t	rca;
	uint8_t		is_mmc:1;
	uint8_t		is_hc:1;
	uint8_t		is_bus4bit:1;
	sdp_cur_stat_t	ci_stat;
	sdp_r1_stat_t	r1_stat;
	CID_t		cid;
	CSD_t		csd;
} sd_sm_t;

typedef struct {
	int rt;
	const char* estr;
} sdmmc_estr_t;

sd_sm_t sd_sm[1];

#define RT_ESTR_PAIR(X)	{ X, #X }

sdmmc_estr_t sdmmc_estr[] = {
	RT_ESTR_PAIR(SDMMC_OK),
	RT_ESTR_PAIR(SDMMC_NO_RSP),
	RT_ESTR_PAIR(SDMMC_CRC_ERR),
	RT_ESTR_PAIR(SDMMC_UNSUP),
	RT_ESTR_PAIR(SDMMC_ERR),
};

const char* sdmmc_err_string(int rt) {
	return sdmmc_estr[-rt].estr;
}

static int sdmmc_inf_init(void) {
	mmcsd_conf_t conf[1];
	uint32_t freq;
	int i;

	syscfg_pinmux(MMCSD_CLK);
	syscfg_pinmux(MMCSD_CMD);
	syscfg_pinmux(MMCSD_DAT0);
	syscfg_pinmux(MMCSD_DAT1);
	syscfg_pinmux(MMCSD_DAT2);
	syscfg_pinmux(MMCSD_DAT3);
	syscfg_pinmux(MMCSD_WP);
	syscfg_pinmux(MMCSD_INS);

	psc_state_transition(PSC_MMC_SD0, PSC_STATE_ENABLE);

	conf->freq = LOW_CLK;
	conf->timeout_rsp = TIMEOUT_RSP_MAX;
	conf->timeout_dat = TIMEOUT_DAT_MAX;
	mmcsd_con_init(MMCSDCON, conf);

	freq = mmcsd_xet_freq(MMCSDCON, LOW_CLK);
	printk("SDMMC freq in %s(): %d Hz\n", __func__, freq);

	for (i = 0; i < countof(sdmmc_estr); i++) {
		sdmmc_estr[i].estr += get_exec_base();
	}

	return 0;
}

static inline uint32_t sdmmc_resp(void) {
	mmcsd_resp_t resp;

	mmcsd_get_resp(MMCSDCON, MMCSD_RESP_SHORT, &resp);
	return resp.v[0];
}

static sdmmc_rt sdmmc_print_r1(void) {
	union {
		uint32_t i;
		sdp_r1_stat_t r1_stat;
	}u;

	u.i = sdmmc_resp();
	sd_sm->r1_stat = u.r1_stat;

	sdprot_print_r1_stat(&sd_sm->r1_stat);

	return SDMMC_OK;
}

static sdmmc_rt sdmmc_get_cid(void) {
	mmcsd_resp_t resp;

	mmcsd_get_resp(MMCSDCON, MMCSD_RESP_LONG, &resp);

	sdprot_get_cid(&sd_sm->cid, resp.v);

	return SDMMC_OK;
}

static uint32_t sdmmc_cmd_stat(int nr) {
	uint32_t stat;

	if (sdprot_resp_crc(nr) == 0) {
		stat = mmcsd_cmd_state(MMCSDCON, AM18X_FALSE);
	} else {
		stat = mmcsd_cmd_state(MMCSDCON, AM18X_TRUE);
	}
	return stat;
}

static sdmmc_rt sdmmc_cmd(int nr, uint32_t arg) {
	sdcard_response_t srt;
	mmcsd_cmd_t cmd;
	uint32_t stat;
	sdmmc_rt r;
	int i;

	r = SDMMC_OK;
	cmd.index = nr;
	cmd.arg = arg;

	if (sdprot_next_stat(nr, sd_sm->ci_stat) == SDP_INV) {
		printk("SDPROT\tCurrent State %s with CMD%d\n", 
			sdprot_stat_name(sd_sm->ci_stat), nr);
		// r = SDMMC_UNSUP;
		// goto done;
	}

	cmd.cflags = 0;
	switch(srt = sdprot_resp_type(nr)) {
	case SDCARD_48BIT_RSP:
		cmd.cflags |= MMCSD_CMD_F_RSP | MMCSD_CMD_F_SHORT;
		if (sdprot_resp_crc(nr)) {
			cmd.cflags |= MMCSD_CMD_F_CRC;
		}
		break;
	case SDCARD_136BIT_RSP:
		cmd.cflags |= MMCSD_CMD_F_RSP | MMCSD_CMD_F_LONG;
		break;
	case SDCARD_NONE_RSP:
	default:
		cmd.cflags |= MMCSD_CMD_F_NORSP;
		break;
	}
	if (sdprot_need_data(nr) != SDPROT_NO_DATA) {
		cmd.cflags |= MMCSD_CMD_F_DATA;
		if (sdprot_need_data(nr) == SDPROT_READ_DATA) {
			cmd.cflags |= MMCSD_CMD_F_READ;
		} else {
			cmd.cflags |= MMCSD_CMD_F_WRITE;
			// am1808 bug fix
			// cmd.cflags &= ~(MMCSD_CMD_F_RSP | MMCSD_CMD_F_LONG);
		}
	}

	if (sdprot_need_busy(nr)) {
		cmd.cflags |= MMCSD_CMD_F_BUSY;
	}

	mmcsd_send_cmd(MMCSDCON, &cmd);

	for(i = 0;;) {
		stat = sdmmc_cmd_stat(nr);
		if (stat == MMCSD_SC_RSP_TOUT || stat == MMCSD_SC_RSP_OK || stat == MMCSD_SC_CRC_ERR) {
			break;
		}
		if (i++ > SDMMC_REG_RETRY) {
			printk("%s() *** error stat = %d ***\n", __func__, stat);
			r = SDMMC_NO_RSP;
			goto done;
		}
	}
	if (stat != MMCSD_SC_RSP_OK) {
		printk("*** MMCCMD=0x%.8X ARG=0x%.8X ***", MMCSDCON->MMCCMD, MMCSDCON->MMCARGHL);
		printk("   *** ST0=0x%.8X RSP=0x%.8X ***\n", MMCSDCON->MMCST0, MMCSDCON->MMCRSP[3]);
	}
	if (stat == MMCSD_SC_CRC_ERR) {
		r = SDMMC_CRC_ERR;
		goto done;
	}
	if (stat == MMCSD_SC_RSP_TOUT) {
		r = SDMMC_NO_RSP;
		goto done;
	}
	printk("SDPROT\tCMD%d OK\n", nr);

	stat = sdprot_next_stat(nr, sd_sm->ci_stat);
	if (stat != sd_sm->ci_stat) {
		printk("SDPROT\tTransition from %s to %s\n", 
			sdprot_stat_name(sd_sm->ci_stat),
			sdprot_stat_name(stat));
		sd_sm->ci_stat = stat;
	}

done:
	return r;
}

static sdmmc_rt sdmmc_acmd(int nr, uint32_t arg) {
	sdmmc_rt r;

	r = sdmmc_cmd(CMD55R1_APP_CMD, sd_sm->rca << 16);
	if (r != SDMMC_OK) {
		printk("SDMMC status = 0x%.8X\n", sdmmc_resp());
		return r;
	}

	//sdmmc_print_r1();

	return sdmmc_cmd(nr, arg);
}

static inline sdmmc_rt sdmmc_cmd_noarg(int nr) {
	return sdmmc_cmd(nr, SDMMC_ARG_NULL);
}

static sdmmc_rt ACMD41(void) {
	sdmmc_rt r;
	uint32_t ocr;

	ocr = OCR_VOLTAGE_WINDOW(BUS_POWER_VOLTAGE);
	do {
		// 30 HCS(OCR[30])
		// 23:0 Vdd Voltage Window(OCR[23:0])
		r = sdmmc_acmd(ACMD41R3_SD_SEND_OP_COND, (ocr  | OCR_CCS) & ~OCR_PowerUpEnd);
		if (r != SDMMC_OK) {
			printk("SDPROT\tNot SD Memory Card\n");
			return SDMMC_UNSUP;
		}
		ocr = sdmmc_resp();
		if (0 == (ocr & OCR_VOLTAGE_WINDOW(BUS_POWER_VOLTAGE))) {
			return SDMMC_UNSUP;
		}
		if (ocr & OCR_PowerUpEnd) break;

		printk("SDPROT\tcard returns busy or host omitted voltage range\n");
		printk("%s() ocr = 0x%.8X\n", __func__, ocr);

		sd_sm->ci_stat = SDP_IDLE;
	} while (AM18X_TRUE);

	printk("%s() ocr = 0x%.8X\n", __func__, ocr);

	if (ocr & OCR_CCS) {
		sd_sm->is_hc = AM18X_TRUE;
	} else {
		sd_sm->is_hc = AM18X_FALSE;
	}

	return SDMMC_OK;
}

static sdmmc_rt CMD1(void) {
	sdmmc_rt r;
	uint32_t ocr, msk;

	ocr = OCR_VOLTAGE_WINDOW(BUS_POWER_VOLTAGE);
	msk = OCR_PowerUpEnd;
	do {
		r = sdmmc_cmd(CMD1R3_SEND_OP_COND, ocr & ~OCR_PowerUpEnd);
		if (r != SDMMC_OK) {
			printk("MMCPROT\tcards with non compatible voltage range\n");
			return r;
		}
		ocr = sdmmc_resp();
		if ((ocr & msk) == msk) break;

		printk("MMCPROT\tcard is busy or\n");
		printk("\thost omitted voltage range\n");
		sd_sm->ci_stat = SDP_IDLE;
	} while (AM18X_TRUE);

	if (ocr & MOCR_VOLTAGE_165to195) {
		printk("MMCPROT\tLow Voltage MultiMediaCard\n");
	} else {
		printk("MMCPROT\tHigh Voltage MultiMediaCard\n");
	}

	printk("%s() ocr = 0x%.8X\n", __func__, ocr);

	if (0 == (ocr & OCR_VOLTAGE_WINDOW(BUS_POWER_VOLTAGE))) {
		return SDMMC_UNSUP;
	}
	return SDMMC_OK;
}

// Protocol
// 4.2.3 Card Initialization and Identification Process
static sdmmc_rt sdmmc_card_init(void) {
	sdmmc_rt r;
	int i;

	sd_sm->rca = 0;
	sd_sm->is_mmc = 0;
	sd_sm->is_bus4bit = 0;
	sd_sm->ci_stat = SDP_IDLE;

	for (i = 0; i < 1000; i++);

	sdmmc_cmd_noarg(CMD0_GO_IDLE_STATE);
	printk("SDPROT\tIdle State(idle)\n");

	r = sdmmc_cmd(CMD8R7_SEND_IF_COND, CMD8_VHS_27to36 | CMD8_CHECK_PATTERN);
	printk("SDMMC cmd8() %s\n", sdmmc_err_string(r));

	if (r == SDMMC_NO_RSP) {
		printk("SDPROT\tVer2.00 or later SD Memory Card(voltage mismatch)\n");
		printk("\tor Ver1.X SD Memory Card\n");
		printk("\tor not SD Memory Card\n");
	} else if ((sdmmc_resp() & CMD8_CHECK_PATTERN_MASK) == CMD8_CHECK_PATTERN) {
		printk("SDPROT\tVer2.00 or later SD Memory Card\n");
	} else {
		// unsupported
		return SDMMC_UNSUP;
	}

	if ((r = ACMD41()) == SDMMC_OK) {
		printk("SDPROT\tCard returns ready\n");
		printk("\tVer1.X Standard Capacity SD Memory Card\n");
	} else {
		printk("SDPROT\tNo Response(Non valid command)\n");
		printk("\tMust be a MultiMediaCard\n");
		printk("SDPORT\tStart MultiMediaCard initialization process\n");
		printk("\tstarting at CMD1\n");

		if ((r = CMD1()) != SDMMC_OK) {
			return r;
		}
		sd_sm->is_mmc = 1;
		sd_sm->rca = MMC_RCA;
	}

	printk("SDPROT\tReady State(ready)\n");

	for (i = 0; i < SDMMC_CMD_RETRY; i++) {
		r = sdmmc_cmd_noarg(CMD2R2_ALL_SEND_CID);
		if (r == SDMMC_OK) break;
	}
	if (r != SDMMC_OK) {
		return r;
	}
	printk("SDPROT\tIdentification State(ident)\n");

	sdmmc_get_cid();
	// sdprot_print_cid(&sd_sm->cid);

	for (i = 0; i < SDMMC_CMD_RETRY; i++) {
		uint32_t arg = 0;

		if (sd_sm->is_mmc) {
			arg = sd_sm->rca << 16;
		}
		r = sdmmc_cmd(CMD3R6_SEND_RELATIVE, arg);
		if (r == SDMMC_OK) break;
	}
	if (r != SDMMC_OK) {
		return r;
	}

	printk("SDPROT\tCard responds with new RCA\n");

	if (!sd_sm->is_mmc) {
		sd_sm->rca = (sdmmc_resp() >> 16);
	}
	printk("SDMMC new RCA = 0x%.4X\n", sd_sm->rca);

	printk("SDPROT\tcard identification mode <-> data transfer mode\n");
	printk("SDPROT\tStand by State(stby)\n");

	return r;
}

static sdmmc_rt sdmmc_get_csd(void) {
	mmcsd_resp_t lngrsp;
	sdmmc_rt r;
	int i;

	for (i = 0; i < SDMMC_CMD_RETRY; i++) {
		r = sdmmc_cmd(CMD9R2_SEND_CSD, sd_sm->rca << 16);
		if (r == SDMMC_OK) break;
	}
	if (r != SDMMC_OK) {
		return r;
	}

	mmcsd_get_resp(MMCSDCON, MMCSD_RESP_LONG, &lngrsp);
	sdprot_get_csd(&sd_sm->csd, lngrsp.v);
	// sdprot_print_csd(&sd_sm->csd);

	return r;
}

static sdmmc_rt sdmmc_speed_up(void) {
	uint32_t speed;

	speed = sdprot_trans_speed(&sd_sm->csd);
	speed = mmcsd_xet_freq(MMCSDCON, speed);

	printk("SDMMC real CLK is %d Hz\n", speed);

	return SDMMC_OK;
}

static sdmmc_rt sdmmc_get_classes(void) {
	uint32_t ccc;
	int i;

	ccc = sd_sm->csd.CCC;

	printk("SDMMC Card Supported Classes:");
	for (i = 0; i < 12; i++) {
		if (ccc & BIT(i)) {
			printk(" %d", i);
		}
	}
	printk("\n");

	printk("SDMMC Card Size %u bytes\n", sdprot_device_size(&sd_sm->csd));

	return SDMMC_OK;
}

static sdmmc_rt sdmmc_sel_card(am18x_bool sel) {
	uint32_t arg;
	sdmmc_rt r;

	arg = sel? (sd_sm->rca << 16): 0;
	r = sdmmc_cmd(CMD7R1b_SEL_UNSEL_CARD, arg);
	if (r != SDMMC_OK) {
		return r;
	}

	// sdmmc_print_r1();

	return SDMMC_OK;
}

static sdmmc_rt sdmmc_max_buswidth(void) {
	sdmmc_rt r;

	if (sd_sm->is_mmc) {
		return SDMMC_OK;
	}

	r = sdmmc_acmd(ACMD6R1_SET_BUS_WIDTH, ACMD6_BW_4BIT);
	if (r == SDMMC_OK) {
		sd_sm->is_bus4bit = 1;
		sd_sm->ci_stat = SDP_TRAN;
	}

	if (sd_sm->is_bus4bit) {
		mmcsd_misc_t misc;

		misc.mflags = MMCSD_MISC_F_BUS4BIT;
		mmcsd_cntl_misc(MMCSDCON, &misc);		
	}
	return r;
}

sdmmc_rt sdmmc_read_block(uint32_t blk_nr, uint32_t blk_cnt, uint32_t* buf) {
	mmcsd_dat_state_t ds;
	mmcsd_misc_t misc;
	sdmmc_rt r;
	int cmd_nr;
	int i;

	misc.blkcnt = blk_cnt;
	misc.mflags = MMCSD_MISC_F_READ | MMCSD_MISC_F_FIFO_RST | MMCSD_MISC_F_FIFO_32B;
	mmcsd_cntl_misc(MMCSDCON, &misc);

	cmd_nr = CMD17R1_READ_SINGLE_BLOCK;
	if (blk_cnt > 1) cmd_nr = CMD18R1_READ_MULTIPLE_BLOCK;

	r = sdmmc_cmd(cmd_nr, blk_nr << MASK_OFFSET(MMCSD_BLOCK_SIZE));
	if (r != SDMMC_OK) return r;

	i = 0;
	while (i < blk_cnt * MMCSD_BLOCK_SIZE / sizeof(uint32_t)) {
		if ((ds = mmcsd_rd_state(MMCSDCON)) == MMCSD_SD_OK) {
			break;
		}
		if (ds == MMCSD_SD_TOUT) {
			return SDMMC_NO_RSP;
		}
		if (ds == MMCSD_SD_CRC_ERR) {
			return SDMMC_CRC_ERR;
		}
		if (i == 0 || ds == MMCSD_SD_RECVED) {
			int ii = 0;

			for (ii = 0; ii < 32 / sizeof(uint32_t); ii++) {
				buf[i++] = mmcsd_read(MMCSDCON);
			}
		}
		printk("   *** ST1=0x%.8X ***\n", MMCSDCON->MMCST1);
	}

	while ((ds = mmcsd_rd_state(MMCSDCON)) != MMCSD_SD_OK);

	printk("SDMMC READ %d bytes\n", i * sizeof(uint32_t));

	if (blk_cnt > 1) {
		r = sdmmc_cmd_noarg(CMD12R1b_STOP_TRANSMISSION);
		if (r != SDMMC_OK) return r;
	} else {
		sd_sm->ci_stat = SDP_TRAN;
	}

	return SDMMC_OK;
}

sdmmc_rt sdmmc_write_block(uint32_t blk_nr, uint32_t blk_cnt, const uint32_t* buf) {
	mmcsd_dat_state_t ds;
	mmcsd_misc_t misc;
	sdmmc_rt r;
	int cmd_nr;
	int i;

	misc.blkcnt = blk_cnt;
	misc.mflags = MMCSD_MISC_F_WRITE | MMCSD_MISC_F_FIFO_RST | MMCSD_MISC_F_FIFO_32B;
	mmcsd_cntl_misc(MMCSDCON, &misc);

	for (i = 0; i < 32 / sizeof(uint32_t);) {
		mmcsd_write(MMCSDCON, buf[i++]);
	}

	cmd_nr = CMD24R1_WRITE_BLOCK;
	if (blk_cnt > 1) cmd_nr = CMD25R1_WRITE_MULTIPLE_BLOCK;

	r = sdmmc_cmd(cmd_nr, blk_nr << MASK_OFFSET(MMCSD_BLOCK_SIZE));
	if (r != SDMMC_OK) return r;

	while (i < 4 + blk_cnt * MMCSD_BLOCK_SIZE / sizeof(uint32_t)) {
		if ((ds = mmcsd_wr_state(MMCSDCON)) == MMCSD_SD_OK) {
			break;
		}
		if (ds == MMCSD_SD_TOUT) {
			return SDMMC_NO_RSP;
		}
		printk("   *** ST1=0x%.8X ***\n", MMCSDCON->MMCST1);
		if (i == 32 / sizeof(uint32_t) || ds == MMCSD_SD_SENT) {
		// if (i == 0 || ds == MMCSD_SD_SENT) {
			int ii;

			for (ii = 0; ii < 32 / sizeof(uint32_t); ii++) {
				mmcsd_write(MMCSDCON, buf[i++]);
			}
		}
	}

	printk("Wait write complete!\n");
	while ((ds = mmcsd_wr_state(MMCSDCON)) != MMCSD_SD_OK) {
		printk("   *** ST1=0x%.8X ***\n", MMCSDCON->MMCST1);
	}

	printk("SDMMC WRITE %d bytes\n", i * sizeof(uint32_t));

	if (blk_cnt <= 1) {
		goto done;
	}

	r = sdmmc_cmd_noarg(CMD12R1b_STOP_TRANSMISSION);
	if (r != SDMMC_OK) return r;

	do {
		ds = mmcsd_busy_state(MMCSDCON);
		//printk("   *** ST0=0x%.8X RSP=0x%.8X ***\n", MMCSDCON->MMCST0, MMCSDCON->MMCRSP[3]);
	} while (ds == MMCSD_SD_BUSY);

done:
	sd_sm->ci_stat = SDP_TRAN;

	return SDMMC_OK;
}

sdmmc_rt sdmmc_init(void) {
	sdmmc_rt r;

	sdmmc_inf_init();

	r = sdmmc_card_init();
	if (r != SDMMC_OK) {
		printk("SDMMC card init %s\n", sdmmc_err_string(r));
		return r;
	}

	r = sdmmc_get_csd();
	if (r != SDMMC_OK) {
		printk("SDMMC get csd %s\n", sdmmc_err_string(r));
		return r;
	}

	r = sdmmc_speed_up();
	r = sdmmc_get_classes();

	r = sdmmc_sel_card(AM18X_TRUE);
	if (r != SDMMC_OK) {
		printk("SDMMC sel card %s\n", sdmmc_err_string(r));
		return r;
	}

	r = sdmmc_max_buswidth();
	printk("SDMMC bus width = %dBIT %s\n", (sd_sm->is_bus4bit? 4: 1), sdmmc_err_string(r));

	return r;
}
