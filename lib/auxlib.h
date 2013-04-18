// tary 22:22 2011/6/19
#ifndef __AUXLIB_H__
#define __AUXLIB_H__

#if defined(LBP_DBG)
#define DBG_LINE(nr, ...)		do {					\
	if (LOCAL_DBG) debug_line(__FUNCTION__, __LINE__, nr, __VA_ARGS__);	\
					}while(0)
#define DBG_BUF(name, buf, size)	do {					\
	if (LOCAL_DBG) debug_buf(name, buf, size);				\
					}while(0)
#define DBG_PRINT(fmt, ...)		do {					\
	if (LOCAL_DBG){								\
		printf("\r\nDBG:%s() L%d\t", __FUNCTION__, __LINE__);		\
		printf(fmt, __VA_ARGS__);					\
	}				}while(0)
#else
#define DBG_LINE(...)
#define DBG_BUF(...)
#define DBG_PRINT(...)
#endif//LBP_DBG

#define KV(x)		{ x, #x }
typedef struct {
	int key;
	char* val;
} kv_t;

typedef unsigned long size_t;

int delay(int d);
int puts(const char* s);
int printk(const char* s, ...);
int sscanf(const char* buf, const char* fmt, ...);
int sprintf(char * buf, const char *fmt, ...);
int strcmp(const char* ss, const char* sd);
int memset(void* dst, int pattern, size_t size);
int memcpy(char* dst, const char* src, size_t size);
int debug_buf(const char* head, char* buf, int len);
int debug_line(const char* file, int lin, int nr, ...);
int dump_regs_word(const char* head, unsigned base, size_t size);

unsigned get_exec_base(void);

#endif //__AUXLIB_H__
