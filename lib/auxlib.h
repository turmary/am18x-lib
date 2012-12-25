// tary 22:22 2011/6/19
#ifndef __AUXLIB_H__
#define __AUXLIB_H__

#include "stdlib.h"

int delay(int d);
int printk(const char* s, ...);
int sscanf(const char* buf, const char* fmt, ...);
int sprintf(char * buf, const char *fmt, ...);
int strcmp(const char* ss, const char* sd);
int memset(void* dst, int pattern, size_t size);
int memcpy(char* dst, const char* src, unsigned size);

#endif //__AUXLIB_H__
