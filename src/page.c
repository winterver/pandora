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
 * File              : page.c
 * Author            : winterver
 * Date              : 2024.11.24
 * Last Modified Date: 2024.11.24
 * Last Modified By  : winterver
 */

#include <types.h>

static __u64 pml4t[512] __attribute__((aligned(0x1000)));
static __u64 pdpt[512] __attribute__((aligned(0x1000)));

static __u64 pdt[512] __attribute__((aligned(0x1000)));
static __u64 pt1[512] __attribute__((aligned(0x1000)));
static __u64 pt2[512] __attribute__((aligned(0x1000)));

void install_paging() {
    pml4t[0] = (__u32)pdpt + 3;
    pdpt[0] = (__u32)pdt + 3;

    pdt[0] = (__u32)pt1 + 3;
    pdt[1] = (__u32)pt2 + 3;
    for (int i = 0; i < 512; i++) {
        pt1[i] = 0x1000 * i + 3;
        pt2[i] = 0x1000 * (i+512) + 3;
    }

    /* replace pml4t directly, as uefi has already enabled
     * paging for us */
    asm volatile (
        "movq %%rax, %%cr3  \n\t"
        ::"a"(pml4t));
}
