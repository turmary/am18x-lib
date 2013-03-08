# tary, 23:29 2013/1/5
_INCS = .
_INCS += ../inc
_INCS += ../prj

EXE = 
EXE += uart-test.exe
EXE += aintc-offset.exe

INCS = $(patsubst %, -I%, $(_INCS))

all:  $(EXE)

uart-test.exe: uart-test.c
	gcc $(INCS) -o $@ $< ../src/am18x_uart.c

%.exe: %.c
	gcc $(INCS) -o $@ $<

clean:
	rm -rf $(EXE)
