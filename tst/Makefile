# tary, 23:29 2013/1/5
_INCS = .
_INCS += ../inc
_INCS += ../prj

INCS = $(patsubst %, -I%, $(_INCS))

all: uart-test.exe

%.exe: %.c
	gcc $(INCS) -o $@ $< ../src/am18x_uart.c

clean:
	rm -rf uart-test.exe
