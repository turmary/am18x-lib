# tary 1:08 2012/12/23
TARGET = main

MAKEFLAGS += 

DEFS = 

CINS = ../include

DEBUG += -gdwarf-2

ARCH = -mcpu=arm926ej-s

CFLAGS += -mabi=aapcs
CFLAGS += $(DEBUG)
CFLAGS += -Os
CFLAGS += -Wall
CFLAGS += -std=gnu99
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
LDFLAGS += -Wl,-T../prj/am18x.ld

COBJ = $(CSRC:.c=.o)
AOBJ = $(ASRC:.S=.o)

OBJS	= $(AOBJ) $(COBJ)

LST	+= $(CSRC:.c=.lst)
LST	+= $(ASRC:.S=.lst)

GENDEPFLAGS = -MD -MP -MF .dep/$(@F).d

ALL_CFLAGS = $(ARCH) $(DEFS) $(CFLAGS) $(GENDEPFLAGS)
ALL_ASFLAGS = $(ARCH) $(DEFS) $(ASFLAGS)
# -x assembler-with-cpp

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

AIS = $(TARGET).ais

program: build ${AIS}
	../tools/sfh_OMAP-L138 -p COM3 -flash_noubl -targetType AM1808 ${AIS}

${AIS}: bin
	../tools/AISgen_d800k008 -cfg="..\tools\am1808exp-spi.cfg"

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

%.lss: %.elf
	$(OBJDUMP) -x -d -S -z $< > $@

%.sym: %.elf
	$(NM) -n $< > $@

%.elf: $(OBJS)
	$(CC) $(ALL_CFLAGS) $(OBJS) --output $@ $(LDFLAGS)

$(COBJ) : %.o : %.c
	$(CC) -c $(ALL_CFLAGS) $< -o $@
	@echo ""

%.i : %.c
	$(CC) -E $(ALL_CFLAGS) $< -o $@
	@echo ""

$(AOBJ) : %.o : %.S
	$(CC) -c $(ALL_ASFLAGS) $< -o $@
	@echo ""

%.i : %.S
	$(CC) -E $(ALL_ASFLAGS) $< -o $@
	@echo ""

clean:
	$(REMOVE) $(TARGET).bin
	$(REMOVE) $(TARGET).elf
	$(REMOVE) $(TARGET).lss
	$(REMOVE) $(TARGET).sym
	$(REMOVE) $(TARGET).map
	$(REMOVE) $(TARGET).ais
	$(REMOVE) $(OBJS) $(LST)
	$(REMOVE) -r .dep

-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

.PHONY : all build elf bin lss sym size program clean
