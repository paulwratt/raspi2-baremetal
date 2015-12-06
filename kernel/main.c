#include	<stdio.h>
#include	<type.h>

int kernel_main(void)
{
	// ドライバ初期化
	uart_init(NULL);

	// メインループ
	printk("a");

	return(0);
}

