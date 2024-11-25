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
#include <types.h>

void install_gdt();
void install_idt();
void install_paging();

void kmain(struct bootinfo* bi) {
    init_video(bi);

    // gdt, irq, paging, my own long mode
    // allocator, process, scheduler,
    // mirco kernel!!

    install_gdt();
    install_idt();
    install_paging();

    //int *p = 0x400000-4; // not triggering page fault, trap in while(1);
    int *p = 0x400000; // triggers page fault, trap in halt loop in page_fault(), low cpu usage
    *p = 233;

    printk("Hello World!\n");
    //printk("vid_addr = %p\n", bi->vid_addr);
}
