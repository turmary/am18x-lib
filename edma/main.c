// tary, 14:00 2013/6/11
#include "am18x_lib.h"
#include "arm920t.h"
#include "systick.h"
#include "auxlib.h"
#include "edma.h"

const uint32_t f_osc = F_OSCIN;

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for edma!\n";

	arm_intr_enable();
	systick_start();

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	psc_state_transition(PSC_EDMA3_0_C0, PSC_STATE_ENABLE);
	psc_state_transition(PSC_EDMA3_0_T0, PSC_STATE_ENABLE);

	edma_block_move_example();

	edma_linked_transfer_example();

	edma_transfer_channing_example();

	return 0;
}
