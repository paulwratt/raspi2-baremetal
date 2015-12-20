#include	<stdio.h>
#include	<type.h>


#define		__LOG_SIZE			(0x1000)
#define		__LOG_SIZE_MASK		(__LOG_SIZE - 1)

//static int __log_start = 0;
//static int __log_end = 0;
static char __log_buf[__LOG_SIZE];

//static char __log_temp[64];
//static int __log_temp_pos;



int printk(const char *fmt, ... )
{
	int ret;
	va_list va;

	va_start(va, fmt);
	ret = vsnprintk(__log_buf, __LOG_SIZE, fmt, va);
	va_end(va);

	// TODO :
	uart_write(__log_buf, ret);
//	uart_write("a0b1c2d3e4\n", 8);

	return ret;
}




