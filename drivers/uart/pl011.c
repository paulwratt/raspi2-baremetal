#include	<device.h>
#include	<register.h>
#include	<stdio.h>


#define GPFSEL1 0x3F200004
#define GPSET0  0x3F20001C
#define GPCLR0  0x3F200028
#define GPPUD       0x3F200094
#define GPPUDCLK0   0x3F200098

#define AUX_ENABLES     0x3F215004
#define AUX_MU_IO_REG   0x3F215040
#define AUX_MU_IER_REG  0x3F215044
#define AUX_MU_IIR_REG  0x3F215048
#define AUX_MU_LCR_REG  0x3F21504C
#define AUX_MU_MCR_REG  0x3F215050
#define AUX_MU_LSR_REG  0x3F215054
#define AUX_MU_MSR_REG  0x3F215058
#define AUX_MU_SCRATCH  0x3F21505C
#define AUX_MU_CNTL_REG 0x3F215060
#define AUX_MU_STAT_REG 0x3F215064
#define AUX_MU_BAUD_REG 0x3F215068

//GPIO14  TXD0 and TXD1
//GPIO15  RXD0 and RXD1
//alt function 5 for uart1
//alt function 0 for uart0

//((250,000,000/115200)/8)-1 = 270


int uart_init(struct DEVICE_DATA *data)
{
    volatile unsigned int ra;

    mem_write32(AUX_ENABLES,1);
    mem_write32(AUX_MU_IER_REG,0);
    mem_write32(AUX_MU_CNTL_REG,0);
    mem_write32(AUX_MU_LCR_REG,3);
    mem_write32(AUX_MU_MCR_REG,0);
    mem_write32(AUX_MU_IER_REG,0);
    mem_write32(AUX_MU_IIR_REG,0xC6);
    mem_write32(AUX_MU_BAUD_REG,270);

    ra=mem_read32(GPFSEL1);
    ra&=~(7<<12); //gpio14
    ra|=2<<12;    //alt5
    mem_write32(GPFSEL1,ra);

    mem_write32(GPPUD,0);
    for(ra=0;ra<150;ra++) ;
    mem_write32(GPPUDCLK0,(1<<14));
    for(ra=0;ra<150;ra++) ;
    mem_write32(GPPUDCLK0,0);

    mem_write32(AUX_MU_CNTL_REG,2);

    ra=0;
    while(1)
    {
        while(1)
        {
            if(mem_read32(AUX_MU_LSR_REG)&0x20) break;
        }
        mem_write32(AUX_MU_IO_REG,0x30+(ra++&7));
    }

	return 0;
}


