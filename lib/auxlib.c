// tary 22:35 2011/6/19
#include <stdarg.h>
#include "auxlib.h"
#include "uart.h"

#ifndef NULL
#define NULL	((void*)0)
#endif

extern int vsprintf(char *buf, const char *fmt, va_list args);

int delay(int d) {
	for (;d > 0; d--) {
		asm volatile("nop");
	}
	return 0;
}

int puts(const char* s) {
	const char* st = s;
	while (*s) {
		putchar(*s++);
	}
	return s - st;
}

int printk(const char* s, ...) {
	static char prbuf[1024];
	va_list v;
	int r;

	va_start(v, s);
	r = vsprintf(prbuf, s, v);
	puts(prbuf);
	va_end(v);
	return r;
}

int memset(void* dst, int pattern, size_t size) {
	char* dstc;
	int i;

	dstc = (char*)dst;
	for (i = 0; i < size; i++) {
		dstc[i] = pattern;
	}
	return size;
}

int memcpy(char* dst, const char* src, size_t size) {
	int i;

	for (i = 0; i < size; i++) {
		dst[i] = src[i];
	}
	return size;
}

size_t strlen(const char* s) {
	const char* b = s;

	while (*++s);
	return s - b;
}

size_t strnlen(const char* s, size_t size) {
	size_t i;

	for (i = 0; i < size && s[i] != 0; i++);

	return i;
}

int strcmp(const char* ss, const char* sd) {
	while (*ss && *sd && *ss++ == *sd++);
	return *ss - *sd;
}

const char* strchr(const char* s, char c) {
	for (; *s && *s != c; s++);
	if (*s == c) {
		return s;
	}
	return NULL;
}

int debug_buf(const char* head, char* buf, int len) {
	int i;

	printk("\r\nDBG:%s[%d] = \r\n\t", head, len);
	for (i = 0; i < len; i++) {
		printk("%.2X ", buf[i]);
	}
	return len;
}

int debug_line(const char* file, int lin, int nr, ...) {
	int val = 0;
	const char* s;
	va_list ap;

	printk("\r\nDBG:%s() L%d\t", file, lin);

	va_start(ap, nr);
	while (nr-- > 0) {
		s = va_arg(ap, char*);
		if (nr-- <= 0) {
			printk(s);
			break;
		}
		val = va_arg(ap, int);
		if (strchr(s, '%') == NULL) {
			printk("%s=%d", s, val);
		} else {
			printk(s, val);
		}
	}
	va_end(ap);

	return nr;
}

int dump_regs_word(const char* head, unsigned base, size_t size) {
	int i;

	for (i = 0; i < size / sizeof (unsigned long); i++) {
		printk("%s[0x%.2X] = 0x%.8X\n", head, i << 2, ((volatile unsigned*)base)[i]);
	}
	return 0;
}
