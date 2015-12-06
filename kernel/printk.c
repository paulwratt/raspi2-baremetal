#include	<stdio.h>
#include	<type.h>


static int __log_pos = 0;
static int __log_size = 0x1000;
static char __log_buf[0x1000];


int vprintk(const char *fmt, va_list va)
{
	int i;

	if (fmt == NULL)
		return 0;

	for (i = 0;fmt[i];i++) {
		char ch = fmt[i];

		__log_buf[__log_pos++] = ch;
		if (__log_pos >= __log_size)
			__log_pos = 0;
	}

	return 0;
}

int printk(const char *fmt, ... )
{
	int ret;
	va_list va;

	va_start(va, fmt);
	ret = vprintk(fmt, va);
	va_end(va);

	return ret;
}




