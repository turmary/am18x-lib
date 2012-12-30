# tary, 1:08 2012/12/23
CSRC += $(wildcard *.c)
CSRC += $(wildcard ../prj/*.c)
CSRC += $(wildcard ../src/*.c)
CSRC += $(wildcard ../lib/*.c)

ASRC += $(wildcard *.S)
ASRC += $(wildcard ../prj/*.S)
ASRC += $(wildcard ../src/*.S)
ASRC += $(wildcard ../lib/*.S)

CINCS = ../inc
CINCS += ../lib
CINCS += ../prj
