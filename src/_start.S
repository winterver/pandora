/**
 * Copyright (c) 2024 winterver
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * File              : _start.S
 * Author            : winterver
 * Date              : 2024.9.26~
 * Last Modified Date: 2024.11.22
 * Last Modified By  : winterver
 */

    .section .bss
    .align 16
    .skip 16384 # 16 KiB
stack_top:

    .section .text
    .global _start
    .type _start, @function
_start:
    /* rbx = struct bootinfo* */

    mov $stack_top, %rsp

    /* Note: the compiler requires the stack be aligned to
     * 16 bytes. So align the stack before entering C code. */
    and $-16, %rsp
    sub $16, %rsp
    mov %rbx, %rdi
    call kmain

    /* In case kmain() retunrns */
    cli     /* Disable interrupts */
1:  hlt     /* Pause CPU, until an interrupt occurs */
    jmp 1b  /* Loop in case a non-maskable interrupt occurs */
