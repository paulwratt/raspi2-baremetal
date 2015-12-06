#include	<device.h>
#include	<register.h>
#include	<type.h>


static struct DEVICE_DATA device_data[] =
{
	// UART
	{
		.name	= "BCM2836,UART",
		.reg	= {UART_REG_BASE, 0x1000},
	},
};


int device_init(void)
{
	device_data;


	return 0;
}


