// tary, 23:22 2013/5/10
#include "am18x_lib.h"
#include "auxlib.h"
#include "uart_puts.h"

const uint32_t f_osc = F_OSCIN;

static PRU_con_t* pru = PRU0;

int main(int argc, char* argv[]) {
	const char* title = "\nam18x library for pruss!\n";
	const char* pru_string = "this is the string output by pru\r\n";
	am18x_rt r;

	printk(title);
	printk("tary, compiled date : %s %s\n", __DATE__, __TIME__);

	psc_state_transition(PSC_PRU, PSC_STATE_ENABLE);

	pru_cmd(pru, PRU_CMD_ENABLE, 0);

	memcpy((char*)PRU_DataRAM0_BASE, pru_string, strlen(pru_string) + 1);
	pru_load(pru, (const uint32_t*)pru_code, countof(pru_code));

	pru_cmd(pru, PRU_CMD_RUN, 0);
	while ((r = pru_cmd(pru, PRU_CMD_IS_HALT, 0)) != AM18X_OK);

	printk("pru halted\n");

	return 0;
}
