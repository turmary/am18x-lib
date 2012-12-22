# tary 1:08 2012/12/23
TARGET = main

MAKEFLAGS += 

DEBUG = 

DEFS = 

CFLAGS += -std=gnu99
CFLAGS += -mcpu=arm926ej-s
CFLAGS += -g$(DEBUG)
CFLAGS += -O1
CFLAGS += -mabi=aapcs
CFLAGS += -Wall
CFLAGS += $(patsubst %,-I%,$(CINCS))
CFLAGS += -Wa,-adhlns=$(subst $(suffix $<),.lst,$<)
CFLAGS += $(DEFS)
CFLAGS += -I.

AFLAGS = -D__ASSEMBLY__

LINKAGE = -static

LDFLAGS = -Wl,-Map=$(TARGET).map
LDFLAGS += $(LINKAGE) -nostdlib
LDFLAGS += -T../prj/am18x.ld

COBJ = $(CSRC:.c=.o)
AOBJ = $(ASRC:.S=.o)

OBJS	= $(AOBJ) $(COBJ)

LST	+= $(CSRC:.c=.lst)
LST	+= $(ASRC:.S=.lst)

GENDEPFLAGS = -MD -MP -MF .dep/$(@F).d

ALL_CFLAGS = $(CFLAGS) $(GENDEPFLAGS)
ALL_AFLAGS = $(CFLAGS) -x assembler-with-cpp $(AFLAGS)

CROSS_COMPILE := arm-none-linux-gnueabi-
CC = $(CROSS_COMPILE)gcc
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
NM = $(CROSS_COMPILE)nm
SIZE = $(CROSS_COMPILE)size
REMOVE = rm -f
COPY = cp

OBJCOPYFLAGS = -R .comment -R .stab -R .stabstr



all: build

build: elf hex bin lss sym size

hex: $(TARGET).hex
bin: $(TARGET).bin
elf: $(TARGET).elf
lss: $(TARGET).lss
sym: $(TARGET).sym

size: $(TARGET).elf
	$(SIZE) -B $(TARGET).elf

%.hex: %.elf
	$(OBJCOPY) $(OBJCOPYFLAGS) -O ihex $< $@

%.bin: %.elf
	$(OBJCOPY) $(OBJCOPYFLAGS) -O binary $< $@

%.lss: %.elf
	$(OBJDUMP) -h -S -C $< > $@

%.sym: %.elf
	$(NM) -n $< > $@

%.elf: $(OBJS)
	$(CC) $(OBJS) --output $@ $(LDFLAGS)

$(COBJ) : %.o : %.c
	$(CC) -c $(ALL_CFLAGS) $< -o $@
	@echo ""

%.i : %.c
	$(CC) -E $(ALL_CFLAGS) $< -o $@
	@echo ""

$(AOBJ) : %.o : %.S
	$(CC) -c $(ALL_AFLAGS) $< -o $@
	@echo ""

%.i : %.S
	$(CC) -E $(ALL_AFLAGS) $< -o $@
	@echo ""

clean:
	$(REMOVE) $(TARGET).hex
	$(REMOVE) $(TARGET).bin
	$(REMOVE) $(TARGET).elf
	$(REMOVE) $(TARGET).lss
	$(REMOVE) $(TARGET).sym
	$(REMOVE) $(TARGET).map
	$(REMOVE) $(OBJS) $(LST)
	$(REMOVE) -r .dep

-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

.PHONY : all build elf hex bin lss sym clean
