
.globl PUT32
PUT32:
    str r1,[r0]
    bx lr

.globl PUT16
PUT16:
    strh r1,[r0]
    bx lr

.globl PUT8
PUT8:
    strb r1,[r0]
    bx lr

.globl GET32
GET32:
    ldr r0,[r0]
    bx lr

.globl GETPC
GETPC:
    mov r0,lr
    bx lr


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
