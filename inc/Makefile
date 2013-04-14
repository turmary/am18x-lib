# tary, 0:49 2013/4/15

all : am18x_map_s.h

am18x_map_s.h: am18x_map.h
	cat $< | sed -e "s/\([^0]0x[0-9a-fA-F]\+\)UL/\1/g" | egrep "^#define " > $@

clean:

.PHONY: all clean
