// tary, 1:15 2011/8/3
#include "arm920t.h"
#include "auxlib.h"

int arm_mmu_show_id_code(void) {
	cp15_id_code_t id[1];

	id[0] = arm_read_cp15_id_code();

	printk("MMU\tLayoutRev\t= 0x%X\n", id->LayoutRev);
	printk("\tPartNumber\t= 0x%X\n", id->PartNumber);
	printk("\tArchitecture\t= 0x%X\n", id->Architecture);
	printk("\tSpecRev  \t= 0x%X\n", id->SpecRev);
	printk("\tImplementer\t= 0x%X\n", id->Implementer);

	return 0;
}

int arm_mmu_show_cache_type(void) {
	cp15_cache_type_t ctype[1];

	ctype[0] = arm_read_cp15_cache_type();

	printk("MMU\tIlen\t= 0x%X\n", ctype->Ilen);
	printk("\tIM\t= 0x%X\n", ctype->IM);
	printk("\tIassoc\t= 0x%X\n", ctype->Iassoc);
	printk("\tIsize\t= 0x%X\n", ctype->Isize);
	printk("\tDlen\t= 0x%X\n", ctype->Dlen);
	printk("\tDM\t= 0x%X\n", ctype->DM);
	printk("\tDassoc\t= 0x%X\n", ctype->Dassoc);
	printk("\tDsize\t= 0x%X\n", ctype->Dsize);
	printk("\tS\t= 0x%X\n", ctype->S);
	printk("\tctype\t= 0x%X\n", ctype->ctype);

	printk("MMU\tDCache Size     \t= %d KB\n", (1 << ctype->Dsize) >> 1);
	printk("\tDCache Line length\t= %d bytes\n", 8 << ctype->Dlen);
	printk("\tDCache associativity\t= %d-way\n", (1 << ctype->Dassoc));
	printk("\tICache Size     \t= %d KB\n", (1 << ctype->Isize) >> 1);
	printk("\tICache Line length\t= %d bytes\n", 8 << ctype->Ilen);
	printk("\tICache associativity\t= %d-way\n", (1 << ctype->Iassoc));

	return 0;
}

unsigned arm_read_cp15_fault_address(void) {
	unsigned fadr;

	asm volatile(
	"mrc	p15, 0, %0, c6, c0, 0\n"
	: "=r"(fadr));
	return fadr;
}
