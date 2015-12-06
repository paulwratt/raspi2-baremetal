#ifndef		__INCLUDE_REGISTER_H__
#define		__INCLUDE_REGISTER_H__

#include	<arch/board/raspi2/register.h>
#include	<type.h>


extern void mem_write32(uint32_t, uint32_t);
extern uint32_t mem_read32(uint32_t);

struct REG_DATA
{
	addr_t		reg_start;
	uint32_t	reg_size;
};



#endif		//__INCLUDE_REGISTER_H__

