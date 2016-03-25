# tary, 20:09 2016/3/25
LINK_SCRIPT = ./rombios.ld

BSRC = rombios

include ../prj/AutoSrcs.inc
ASRC := $(filter-out ../prj/start.S, $(ASRC))

# ASRC := $(sort $(BSRC).S $(ASRC)
ASRC := $(filter-out $(BSRC).S, $(ASRC))
ASRC := $(BSRC).S $(ASRC)

CSRC := $(filter-out rombios.c, $(CSRC))

include ../prj/Rules.inc

$(BSRC).S : $(BSRC)_.i $(MAKEFILE_LIST)
	$(CC) -S $(ALL_CFLAGS) $< -o $@
	@echo ""

$(BSRC)_.i : $(BSRC).i $(MAKEFILE_LIST)
	./asm2c.sh $< > $@

clean: local_clean

local_clean:
	$(REMOVE) $(BSRC)_.i
	$(REMOVE) $(BSRC).i
	$(REMOVE) $(BSRC).S

.PHONY: local_clean
