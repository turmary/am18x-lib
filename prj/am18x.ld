/* tary, 1:09 2012/12/23 */
OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm","elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SEARCH_DIR("=/usr/local/lib");
SEARCH_DIR("=/lib");
SEARCH_DIR("=/usr/lib");
SECTIONS
{
	. = 0x00000000;
	. = ALIGN(0x4);
	PROVIDE (__text_start = .);
	.text : {
		*(.init);
		*(.text);
		. = ALIGN(16);

		*(.rodata .rodata.*);
		. = ALIGN(16);

		*(.data.rel.ro*);
		. = ALIGN(16);

		PROVIDE(__got_start = .);
		*(.got.plt);
		*(.got);
		. = ALIGN(0x4);
		PROVIDE(__got_end = .);
		PROVIDE(__got_size = __got_end - __got_start);

	} = 0
	. = ALIGN(0x4);
	PROVIDE (__text_end = .);

	. = ALIGN(0x4);
	PROVIDE (__data_start = .);
	.data : {
		*(.data);
	} = 0
	. = ALIGN(0x4);
	PROVIDE (__data_end = .);

	PROVIDE (__bss_start = .);	
	.bss : {
		*(.bss)
		*(COMMON)
	} = 0
	. = ALIGN(0x4);
	PROVIDE (__bss_end = .);

	. = ALIGN(16);
	.stack : {
		*(.stack);
	}
	. = ALIGN(0x4);

	PROVIDE (end = .);

	/DISCARD/ : {
		*(.note.GNU-stack)
		*(.gnu_debuglink)
		*(.gnu.lto_*)
		/*(.debug*)*/
		*(.ARM.attributes)
		*(.comment)
		*(.dynamic)
	}
}
