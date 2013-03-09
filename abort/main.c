// tary, 17:49 2013/3/9
#include "am18x_lib.h"
#include "auxlib.h"
#include "systick.h"
#include "arm920t.h"

const uint32_t f_osc = F_OSCIN;

systick_handler_t handler;

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for arm926ej-s abort!\n";
	unsigned pc, sp;
	unsigned* inst;
	int i;

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	asm volatile(
	"MOV	%0, PC\n"
	"MOV	%1, SP\n"
	: "=r" (pc), "=r" (sp)
	);

	printk("current running address = 0x%.8X\n", pc);
	printk("current stack pointer   = 0x%.8X\n", sp);

	arm_mmu_show_id_code();
	arm_mmu_show_cache_type();

	for (inst = (unsigned*)ARMlocalRAM_BASE, i = 0; i < 16; i++) {
		printk("[%.2d] = 0x%.8X\n", i, *inst++);
	}

	printk("\n");

	asm volatile (
	".long	0x2301fc09\n"
	"nop\n"
	);

	printk("undef abort passed\n");

	// *(unsigned*)0x3ABCDEFF = 0x0;
	// *(unsigned*)0x3ABCDEFC = 0x0;
	handler = (systick_handler_t)0x3ABCDEFC;
	// handler(1);

	return 0;
}
