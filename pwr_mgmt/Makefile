# tary, 0:15 2013/4/23
include ../prj/Makefile.inc

PRU_FILE=psc_config

main.c: ${PRU_FILE}.h

${PRU_FILE}.h: ${PRU_FILE}.p
	../tools/pasm -c -L -Cpru_code $<
	mv ${PRU_FILE}_bin.h ${PRU_FILE}.h
