// tary, 22:35 2013/4/26
#include "am18x_lib.h"
#include "auxlib.h"

const uint32_t f_osc = F_OSCIN;

#define KV_X(x)		{ BOOTCFG_BOOTMODE_##x, #x }
kv_t kv_boot[] = {
KV_X(I2C0EEPROM),
KV_X(I2C0SLAVE),
KV_X(NOR),
KV_X(HPI),
KV_X(I2C1EEPROM),
KV_X(I2C1SLAVE),
KV_X(SPI0EEPROM),
KV_X(SPI1EEPROM),
KV_X(SPI0FLASH),
KV_X(SPI1FLASH),
KV_X(NAND8),
KV_X(NAND16),
KV_X(SPI0SLAVE),
KV_X(SPI1SLAVE),
KV_X(UART2),
KV_X(UART0),
KV_X(UART1),
KV_X(EMU),
};

int main(int argc, char* argv[]) {
	int i, mode;
	const char* title = "\nam18x library for syscfg!\n";

	for (i = 0; i < countof(kv_boot); i++) {
		kv_boot[i].val += get_exec_base();
	}

	printk(title);
	printk("AM18XX Bootloader Revision=%s\n", (char*)ARMlocalROM_BASE + 8);

	mode = syscfg_bootmode();
	for (i = 0; i < countof(kv_boot); i++) {
		if (kv_boot[i].key == mode) {
			break;
		}
	}

	if (kv_boot[i].key == mode) {
		printk("System boot from %s\n", kv_boot[i].val);
	} else {
		printk("System boot config error\n");
	}

	return 0;
}
