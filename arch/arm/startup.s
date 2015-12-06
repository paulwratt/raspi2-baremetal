.globl _start
_start:
    mov sp,#0x8000
    bl kernel_main
hang: b hang

.globl mem_write32
mem_write32:
    str r1,[r0]
    bx lr

.globl mem_read32
mem_read32:
    ldr r0,[r0]
    bx lr

.globl dummy
dummy:
    bx lr

