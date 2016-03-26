#!/bin/sh
# tary, 22:19 2016/3/25

cat $1 |	\
sed -e 's/\r\n/\n/g' |	\
awk -F' ' '
BEGIN {
	in_asm = 0;
};
{
	if ($1 == "ASM_START") {
		in_asm = 1;
		printf "asm (\n";
	} else if ($1 == "ASM_END") {
		in_asm = 0;
		printf ");\n";
	} else if (in_asm == 1) {
		n = 0;
		tabline = "";
		for (i = 1; i <= length($0); i++) {
			c = substr($0, i, 1);
			if (c == " " && n++ < 2) {
				c = "\t";
			}
			tabline = (tabline c);
		}
		printf "\"%s\\n\"\n", tabline;
	} else {
		printf "%s\n", $0
	}
}'

