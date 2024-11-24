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
 * File              : gdt.c
 * Author            : winterver
 * Date              : 2024.11.24
 * Last Modified Date: 2024.11.24
 * Last Modified By  : winterver
 */

#include <types.h>

__attribute__((naked))
static void reload_segments() {
    asm volatile (
        "pushq $0x08              \n\t"
        "leaq .reload(%rip), %rax \n\t"
        "pushq %rax               \n\t"
        "lretq                      \n"
    ".reload:                     \n\t"
        "movw $0x10, %ax          \n\t"
        "movw %ax, %ds            \n\t"
        "movw %ax, %ss            \n\t"
        "movw %ax, %es            \n\t"
        "movw %ax, %fs            \n\t"
        "movw %ax, %gs            \n\t"
        "ret                          ");
}

__attribute__((aligned(0x10)))
static __u64 gdt[] = {
    /* On x64, only the higher half of the second (from left to right)
     * byte and entire third byte are meaningful, they are Flags and
     * Access Byte respectively. The other parts are ignored. */
    0x0000000000000000, /* NULL placeholder */
    0x00a09b0000000000, /* code segment */
    0x00c0930000000000, /* data segment */
};

void install_gdt() {
    struct {
        __u16 size;
        __u64 *pgdt;
    } __attribute__((packed)) gdtr;

    gdtr.size = sizeof(gdt) - 1;
    gdtr.pgdt = gdt;
    asm volatile ("lgdt %0"::"m"(gdtr));

    reload_segments();
}
