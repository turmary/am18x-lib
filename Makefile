# tary, 0:56 2012/12/23

DIRS= ${wildcard *}

all:
	@for i in ${DIRS}; do				\
		if [ -f $${i}/Makefile ]; then		\
			make -C $${i} || exit $$?;	\
		fi;					\
	done

clean:
	@for i in ${DIRS}; do				\
		if [ -f $${i}/Makefile ]; then		\
			make -C $${i} clean;		\
		fi;					\
	done

.PHONY: all clean
