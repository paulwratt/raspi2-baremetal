#ifndef		__INCLUDE_STDIO_H__
#define		__INCLUDE_STDIO_H__


typedef char *va_list;

#define _AUPBND                 (sizeof (int) - 1)
#define _ADNBND                 (sizeof (int) - 1)
#define _bnd(X, bnd)            (((sizeof (X)) + (bnd)) & (~(bnd)))
#define va_arg(ap, T)           (*(T *)(((ap) += (_bnd (T, _AUPBND))) - (_bnd (T,_ADNBND))))
#define va_end(ap)              (ap = (va_list) NULL)
#define va_start(ap, A)         (void) ((ap) = (((char *) &(A)) + (_bnd (A,_AUPBND))))


int printk(const char *fmt, ... );
int vsnprintk(char *buffer, int count, const char *format, va_list va);



#endif		//__INCLUDE_STDIO_H__

