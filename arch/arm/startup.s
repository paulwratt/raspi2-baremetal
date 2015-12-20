
MODE_USR	= 0x10
MODE_FIQ	= 0x11
MODE_IRQ	= 0x12
MODE_SVC	= 0x13
MODE_MON	= 0x16
MODE_ABT	= 0x17
MODE_UND	= 0x1B
MODE_SYS	= 0x1F

A_BIT		= 0x100
I_BIT		= 0x080
F_BIT		= 0x040

;@ ------------------------------------
.globl _start
_start:
	ldr pc,reset_handler
	ldr pc,undefined_handler
	ldr pc,swi_handler
	ldr pc,prefetch_handler
	ldr pc,data_handler
	ldr pc,unused_handler
	ldr pc,irq_handler
	ldr pc,fiq_handler
reset_handler:      .word reset
undefined_handler:  .word hang
swi_handler:        .word hang
prefetch_handler:   .word hang
data_handler:       .word hang
unused_handler:     .word hang
irq_handler:        .word irq
fiq_handler:        .word fiq

;@ ------------------------------------
hang:
	b hang

;@ ------------------------------------
irq:
	push {r0,r1,r2,r3,r4,r5,r6,r7,lr}
;@	bl c_irq_handler
	pop  {r0,r1,r2,r3,r4,r5,r6,r7,lr}
	subs pc,lr,#4

;@ ------------------------------------
fiq:
	push {r0,r1,r2,r3,r4,r5,r6,r7,lr}
;@	bl c_irq_handler
	pop  {r0,r1,r2,r3,r4,r5,r6,r7,lr}
	subs pc,lr,#4

;@ ------------------------------------
reset:
	;@ VectorTableのコピー
	mov r0,#0x8000
	mov r1,#0x0000
	ldmia r0!,{r2,r3,r4,r5,r6,r7,r8,r9}
	stmia r1!,{r2,r3,r4,r5,r6,r7,r8,r9}
	ldmia r0!,{r2,r3,r4,r5,r6,r7,r8,r9}
	stmia r1!,{r2,r3,r4,r5,r6,r7,r8,r9}

	;@ (PSR_IRQ_MODE|PSR_FIQ_DIS|PSR_IRQ_DIS)
	msr cpsr_c, #MODE_IRQ | I_BIT | F_BIT
	mov sp, #0x00008000

	;@ (PSR_FIQ_MODE|PSR_FIQ_DIS|PSR_IRQ_DIS)
	msr cpsr_c, #MODE_FIQ | I_BIT | F_BIT
	mov sp,#0x00004000

    ;@ (PSR_SYS_MODE|PSR_FIQ_DIS|PSR_IRQ_DIS)
	msr cpsr_c, #MODE_SYS | I_BIT | F_BIT
	mov sp,#0x08000000

	;@ メインループ実行
	bl kernel_main

	;@ 終了
	b hang
