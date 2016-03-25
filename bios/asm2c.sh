#!/bin/sh
# tary, 22:19 2016/3/25

cat $1 |	\
sed -e 's/\r\n/\n/g' |	\
awk -F' ' -v in_asm=0 '
{
	if ($1 == "ASM_START") {
		in_asm = 1;
		printf "asm (\n";
	} else if ($1 == "ASM_END") {
		in_asm = 0;
		printf ");\n";
	} else if (in_asm == "1") {
		printf "\"%s\\n\"\n", $0;
	} else {
		printf "%s\n", $0
	}
}'

