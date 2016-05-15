# tary 1:08 2012/12/23
TARGET = main

MAKEFLAGS += 

DEFS = 
ifeq ($(MAKECMDGOALS),run)
DEFS += -D_M_BOOT_DELAY
endif

CINS = ../include

LINK_SCRIPT ?= ../prj/am18x.ld

DEBUG += -gdwarf-2

ARCH = -mcpu=arm926ej-s

CFLAGS += -mabi=aapcs
CFLAGS += $(DEBUG)
CFLAGS += -Os
CFLAGS += -Wall
CFLAGS += -std=gnu99
CFLAGS += -fno-builtin
CFLAGS += -I.
CFLAGS += $(patsubst %,-I%,$(CINCS))
CFLAGS += -fpic -msingle-pic-base -mpic-register=r10
CFLAGS += -Wa,--keep-locals
CFLAGS += -Wa,-adhlns=$(subst $(suffix $<),.lst,$<)

ASFLAGS += -D__ASSEMBLY__
ASFLAGS += $(DEBUG)
ASFLAGS += -I.
ASFLAGS += $(patsubst %,-I%,$(CINCS))
ASFLAGS += -Wa,--keep-locals
ASFLAGS += -Wa,-ahdlns=$(<:.S=.lst)

LDFLAGS += $(DEBUG)
LDFLAGS += -static -nostdlib
LDFLAGS += -Wl,-Map=$(TARGET).map
LDFLAGS += -Wl,-T$(LINK_SCRIPT)
# import for symbol __lds_xxx when option -pie used
LDFLAGS += -Wl,-Bsymbolic
LDFLAGS += -pie

COBJ = $(CSRC:.c=.o)
AOBJ = $(ASRC:.S=.o)

OBJS	= $(AOBJ) $(COBJ)

LST	+= $(CSRC:.c=.lst)
LST	+= $(ASRC:.S=.lst)

GENDEPFLAGS = -MD -MP -MF .dep/$(@F).d

ALL_CFLAGS = $(ARCH) $(DEFS) $(CFLAGS) $(GENDEPFLAGS)
ALL_ASFLAGS = $(ARCH) $(DEFS) $(ASFLAGS)

CROSS_COMPILE := arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
NM = $(CROSS_COMPILE)nm
SIZE = $(CROSS_COMPILE)size
REMOVE = rm -f
COPY = cp


all: build

build: elf bin lss sym size

bin: $(TARGET).bin
elf: $(TARGET).elf
lss: $(TARGET).lss
sym: $(TARGET).sym

size: $(TARGET).elf
	$(SIZE) -B $(TARGET).elf

AIS_SPI = $(TARGET)_spi.ais
AIS_UART = $(TARGET)_uart.ais

program: build ${AIS_SPI}
	../tools/sfh_OMAP-L138 -p COM3 -flash_noubl -targetType AM1808 ${AIS_SPI}

run: build ${AIS_UART}
	../tools/slh_OMAP-L138 -p COM3 -waitForDevice -v ${AIS_UART}

${AIS_SPI}: bin
	../tools/AISgen_d800k008 -cfg="..\tools\am1808exp-spi.cfg"

${AIS_UART}: bin
	../tools/AISgen_d800k008 -cfg="..\tools\am1808exp-uart.cfg"

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

%.lss: %.elf
	$(OBJDUMP) -x -d -S -z $< > $@

%.sym: %.elf
	$(NM) -n $< > $@

%.elf: $(OBJS) $(LINK_SCRIPT) $(MAKEFILE_LIST)
	$(CC) --output $@ $(LDFLAGS) -Wl,--start-group $(OBJS) -Wl,--end-group

$(COBJ) : %.o : %.c $(MAKEFILE_LIST)
	$(CC) -c $(ALL_CFLAGS) $< -o $@
	@echo ""

%.i : %.c $(MAKEFILE_LIST)
	$(CC) -E -CC $(ALL_CFLAGS) $< -o $@
	@echo ""

$(AOBJ) : %.o : %.S $(MAKEFILE_LIST)
	$(CC) -c $(ALL_ASFLAGS) $< -o $@
	@echo ""

%.i : %.S $(MAKEFILE_LIST)
	$(CC) -E $(ALL_ASFLAGS) $< -o $@
	@echo ""

clean:
	$(REMOVE) $(TARGET).bin
	$(REMOVE) $(TARGET).elf
	$(REMOVE) $(TARGET).lss
	$(REMOVE) $(TARGET).sym
	$(REMOVE) $(TARGET).map
	$(REMOVE) $(TARGET)*.ais
	$(REMOVE) AIGgen_log.txt
	$(REMOVE) $(OBJS) $(LST)
	$(REMOVE) -r .dep

-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

.PHONY : all build elf bin lss sym size program clean
