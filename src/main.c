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
 * File              : main.c
 * Author            : winterver
 * Date              : 2024.9.26~
 * Last Modified Date: 2024.11.24
 * Last Modified By  : winterver
 */

#include <boot.h>
#include <printk.h>
#include <port.h>
#include <types.h>

static __u64 gdt[] = {
    /* On x64, only the higher half of the second (from left to right)
     * byte and entire third byte are meaningful, they are Flags and
     * Access Byte respectively. The other parts are ignored. */
    0x0000000000000000, /* NULL placeholder */
    0x00a09b0000000000, /* code segment */
    0x00c0930000000000, /* data segment */
};

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

static void install_gdt() {
    struct {
        __u16 size;
        __u64 *pgdt;
    } __attribute__((packed)) gdtr;

    gdtr.size = sizeof(gdt) - 1;
    gdtr.pgdt = gdt;
    asm volatile ("lgdt %0"::"m"(gdtr));

    reload_segments();

    gdtr.size = 0;
    gdtr.pgdt = 0;
    asm volatile ("sgdt %0":"=m"(gdtr));

    for (int i = 0; i < ((gdtr.size + 1) / 8); i++) {
        __u64 entry = gdtr.pgdt[i];
        __u8 access = (entry >> 40) & 0xff;
        __u8 flags = (entry >> 52) & 0x0f;
        printk("entry %d access = %hhx, flags = %hhx\n", i, access, flags);
    }

    __u16 cs, ds, ss, es, fs, gs;
    asm volatile ("movw %%cs, %0":"=m"(cs));
    asm volatile ("movw %%ds, %0":"=m"(ds));
    asm volatile ("movw %%ss, %0":"=m"(ss));
    asm volatile ("movw %%es, %0":"=m"(es));
    asm volatile ("movw %%fs, %0":"=m"(fs));
    asm volatile ("movw %%gs, %0":"=m"(gs));
    printk("cs = %hx\n", cs);
    printk("ds = %hx\n", ds);
    printk("ss = %hx\n", ss);
    printk("es = %hx\n", es);
    printk("fs = %hx\n", fs);
    printk("gs = %hx\n", gs);
}

void kmain(struct bootinfo* bi) {
    init_video(bi);
    printk("Hello World!\n");

    // gdt, irq, paging, my own long mode
    // allocator, process, scheduler,
    // mirco kernel!!
    
    install_gdt();
}
