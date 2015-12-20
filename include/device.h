#ifndef		__INCLUDE_DEVICE_H__
#define		__INCLUDE_DEVICE_H__

#include	<register.h>
#include	<type.h>

struct DEVICE_DATA
{
	char *name;
	struct REG_DATA	reg;

};

struct DEVICE_OPERATIONS
{
	int (*write)(const char *, size_t);
	int (*read)(char *, size_t);

	void (*enable)(void);
	void (*disable)(void);

	void (*startup)(void);
};

#endif		//__INCLUDE_DEVICE_H__

