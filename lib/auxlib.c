// tary 22:35 2011/6/19
#include <stdarg.h>
#include "auxlib.h"
#include "uart.h"

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
