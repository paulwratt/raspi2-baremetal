#include "mini_uart.h"

#include	<stdio.h>
#include	<device.h>
#include	<register.h>
#include	<type.h>



#define GPFSEL1		0x3F200004
#define GPSET0		0x3F20001C
#define GPCLR0		0x3F200028
#define GPPUD		0x3F200094
#define GPPUDCLK0	0x3F200098



static struct UART_DATA
{
	addr_t base;
	struct DEVICE_OPERATIONS ope;
} regData;


//static int uart_write(const char *buffer, size_t len)
int uart_write(const char *buffer, size_t len)
{
	volatile uint32_t val;

	while (len) {
		do {
			val = mem_read32(regData.base + UART_AUX_MU_LSR);
		} while ((val & UART_AUX_MU_LSR_TIDLE) == 0);

		mem_write32(regData.base + UART_AUX_MU_IO, *buffer++);
		len--;
	}

	return 0;
}

static void uart_enable(void)
{
	volatile uint32_t val = mem_read32(regData.base + UART_AUXENB);
	val |= UART_AUXENB_UART;
	mem_write32(regData.base + UART_AUXENB, val);
}

static void uart_disable(void)
{
	volatile uint32_t val = mem_read32(regData.base + UART_AUXENB);
	val &= ~UART_AUXENB_UART;
	mem_write32(regData.base + UART_AUXENB, val);
}

static void uart_startup(void)
{
	volatile uint32_t val;

#if 1
	// 一旦、送受信無効
	mem_write32(regData.base + UART_AUX_MU_CNTL, 0);

	// FIFOクリア
	mem_write32(regData.base + UART_AUX_MU_IIR, 0x3 << 1);

	// CTS/RTSクリア
	mem_write32(regData.base + UART_AUX_MU_CNTL, 0x0);
	mem_write32(regData.base + UART_AUX_MU_MCR, 0x0);

	// 8bit
	mem_write32(regData.base + UART_AUX_MU_LCR, 0x1);

	// ボーレート(115,200)
	//((250,000,000/115200)/8)-1 = 270
	val  = 250 * 1000 * 1000;
	val /= 115200;
	val /= 8;
	mem_write32(regData.base + UART_AUX_MU_BAUD, val - 1);

	// GPIO
	//GPIO14  TXD0 and TXD1
	//GPIO15  RXD0 and RXD1
	//alt function 5 for uart1
	//alt function 0 for uart0
	val = mem_read32(GPFSEL1); // 0x3F200004
	val &= ~(7 << 12); //gpio14
	val |= 2 << 12;    //alt5
	mem_write32(GPFSEL1, val);

	mem_write32(GPPUD, 0); // 0x3F200094
	for (val = 0;val < 150;val++) ;
	mem_write32(GPPUDCLK0, (1 << 14)); // 0x3F200098
	for (val = 0;val < 150;val++) ;
	mem_write32(GPPUDCLK0, 0);

	// 送信有効
	val = 0x2;
	mem_write32(regData.base + UART_AUX_MU_CNTL, val);

#else
	mem_write32(AUX_ENABLES, 1);
	mem_write32(AUX_MU_IER_REG, 0);
	mem_write32(AUX_MU_CNTL_REG, 0);
	mem_write32(AUX_MU_LCR_REG, 3);
	mem_write32(AUX_MU_MCR_REG, 0);
	mem_write32(AUX_MU_IER_REG, 0);
	mem_write32(AUX_MU_IIR_REG, 0xC6);
	mem_write32(AUX_MU_BAUD_REG, 270);

	val = mem_read32(GPFSEL1); // 0x3F200004
	val &= ~(7 << 12); //gpio14
	val |= 2 << 12;    //alt5
	mem_write32(GPFSEL1, val);

	mem_write32(GPPUD, 0); // 0x3F200094
	for (val = 0;val < 150;val++)
		;
	mem_write32(GPPUDCLK0, (1 << 14)); // 0x3F200098
	for (val = 0;val < 150;val++)
		;
	mem_write32(GPPUDCLK0, 0);

	mem_write32(AUX_MU_CNTL_REG, 2);

#if 0
	val = 0;
	while (1) {
		while (1) {
			if (mem_read32(AUX_MU_LSR_REG) & 0x20)
				break;
		}
		mem_write32(AUX_MU_IO_REG, 0x30 + (val++ & 7));
	}
#endif
#endif
}

int uart_init(struct DEVICE_DATA *data)
{
	if (data == NULL)
		return -1;

	// ベースアドレスコピー
	regData.base = data->reg.reg_start;
	regData.ope.startup = uart_startup;
	regData.ope.enable = uart_enable;
	regData.ope.disable = uart_disable;
	regData.ope.write = uart_write;

	// TODO :
	regData.base = 0x3F215000;

	// UART初期化
	if (regData.ope.startup)
		regData.ope.startup();

	// UART有効化
	if (regData.ope.enable)
		regData.ope.enable();

	return 0;
}

