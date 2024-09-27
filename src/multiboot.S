.set ALIGN,     1<<0     /* align loaded modules on page boundaries */
.set MEMINFO,   1<<1     /* provide memory map */
.set VIDEOMODE, 1<<2     /* set and provide video mode info */

.set MAGIC,     0x1BADB002
.set FLAGS,     ALIGN | MEMINFO | VIDEOMODE
.set CHECKSUM,  -(MAGIC + FLAGS)

.set MODE,      0       /* 0 for graphics, 1 for text */
.set WIDTH,     1360
.set HEIGHT,    768
.set DEPTH,     32      /* num of bits per pixel */

    .section .multiboot
    .align 4
multiboot:
    .long MAGIC
    .long FLAGS
    .long CHECKSUM
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long MODE
    .long WIDTH
    .long HEIGHT
    .long DEPTH

    /* The stack on x86 must be 16-byte aligned according to the System V
     * ABI standard and de-facto extensions. The compiler will assume the
     * stack is properly aligned and failure to align the stack will result
     * in undefined behavior.
     * */
    .section .bss
    .align 16
    .skip 16384 # 16 KiB
stack_top:

    .section .text
    .global _start
    .type _start, @function
_start:
    /* The bootloader has loaded us into 32-bit protected mode.
     * The processor state is as defined in the multiboot standard.
     * The kernel now has absolute and complete power over the machine.
     * Interrupts are disabled.
     * Paging is disabled.
     * */

    /* This is a good place to initialize crucial processor state before the
     * high-level kernel is entered. It's best to minimize the early environ
     * -ment where crucial features are offline.
     * Note that the processor is not fully initialized yet: Features such
     * as floating point instructions and instruction set extensions are not
     * initialized yet.
     * The GDT should be loaded here.
     * Paging should be enabled here.
     * */
    mov $stack_top, %esp

    /* Note: System V ABI and the compiler requires the stack be aligned to
     * 16 bytes. So align the stack before entering C code. */
    and $-16, %esp
    sub $16, %esp
    /* GRUB provided a pointer to multiboot_info_t in ebx and a magic number
     * in eax for verification. Make sure they're unchanged. */
    mov %eax, 4(%esp)
    mov %ebx, (%esp)
    call kmain

    /* In case kmain() retunrns */
    cli     /* Disable interrupts */
1:  hlt     /* Pause CPU, until an interrupt occurs */
    jmp 1b  /* Loop in case a non-maskable interrupt occurs */

    /* Set the size of the _start symbol. This is useful when debugging
     * or when you implement call tracing. */
    .size _start, . - _start
