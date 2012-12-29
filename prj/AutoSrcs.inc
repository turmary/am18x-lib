# tary, 1:08 2012/12/23
CSRC += $(wildcard *.c)
CSRC += $(wildcard ../src/*.c)
CSRC += $(wildcard ../lib/uart.c)
CSRC += $(wildcard ../prj/*.c)

ASRC += $(wildcard *.S)
ASRC += $(wildcard ../src/*.S)
# ASRC += $(wildcard ../lib/*.S)
ASRC += $(wildcard ../prj/start.S)

CINCS = ../inc
CINCS += ../lib
CINCS += ../prj
