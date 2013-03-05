// tary 22:22 2011/6/19
#ifndef __AUXLIB_H__
#define __AUXLIB_H__

typedef unsigned long size_t;

int delay(int d);
int puts(const char* s);
int printk(const char* s, ...);
int sscanf(const char* buf, const char* fmt, ...);
int sprintf(char * buf, const char *fmt, ...);
int strcmp(const char* ss, const char* sd);
int memset(void* dst, int pattern, size_t size);
int memcpy(char* dst, const char* src, size_t size);

#endif //__AUXLIB_H__
