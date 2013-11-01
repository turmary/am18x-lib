# tary, 23:21 2013/5/10
include ../prj/Makefile.inc

PRU_FILE=uart_puts

main.c: ${PRU_FILE}.h

${PRU_FILE}.h: ${PRU_FILE}.p
	../tools/pasm -c -L -Cpru_code $<
	mv ${PRU_FILE}_bin.h ${PRU_FILE}.h

clean: pru_clean

pru_clean:
	rm -f ${PRU_FILE}.h
	rm -f ${PRU_FILE}.txt

.PHONY: pru_clean
