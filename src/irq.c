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
 * File              : irq.c
 * Author            : winterver
 * Date              : 2024.11.24
 * Last Modified Date: 2024.11.24
 * Last Modified By  : winterver
 */

#include <printk.h>
#include <types.h>

__attribute__((naked))
static void syscall() {
    printk("0x80 syscall!\n");
    asm volatile ("iretq");
}

typedef struct {
    __u16 isr_lo;
    __u16 cs;
    __u8  ist;
    __u8  attr;
    __u16 isr_mid;
    __u32 isr_hi;
    __u32 reserved;
} __attribute__((packed)) idt_entry_t;

__attribute__((aligned(0x10)))
static idt_entry_t idt[256];

void install_idt() {
#define ISR(index, isr, _attr)                  \
    idt[index] = (idt_entry_t) {                \
        .isr_lo     = (__u64)isr & 0xffff,      \
        .cs         = 0x08,                     \
        .ist        = 0,                        \
        .attr       = _attr,                    \
        .isr_mid    = ((__u64)isr>>16) & 0xffff,\
        .isr_hi     = ((__u64)isr>>32),         \
        .reserved   = 0,                        \
    };
    ISR(0x80, syscall, 0x8e);

    struct {
        __u16       size;
        idt_entry_t *pidt;
    } __attribute__((packed)) idtr;

    idtr.size = sizeof(idt);
    idtr.pidt = idt;
    asm volatile ("lidt %0"::"m"(idtr));
}
