#include	<stdio.h>
#include	<type.h>

int kernel_main(void)
{
	// ドライバ初期化
	uart_init("aaaaa");

	// メインループ
	printk("abcdefghijklmnopqrstuvwxyz\n");

	while (1) ;
	return(0);
}

