    .section .bss
    .align 16
    .skip 16384 # 16 KiB
stack_top:

    .section .text
    .global _start
    .type _start, @function
_start:
    /* rbx = struct bootinfo* */
    /* rcx = BI_MAGIC */

    mov $stack_top, %rsp

    /* Note: the compiler requires the stack be aligned to
     * 16 bytes. So align the stack before entering C code. */
    and $-16, %rsp
    sub $16, %rsp
    mov %rbx, %rdi
    mov %rcx, %rsi
    call kmain

    /* In case kmain() retunrns */
    cli     /* Disable interrupts */
1:  hlt     /* Pause CPU, until an interrupt occurs */
    jmp 1b  /* Loop in case a non-maskable interrupt occurs */
