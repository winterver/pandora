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
 * File              : linker.ld
 * Author            : winterver
 * Date              : 2024.9.26~
 * Last Modified Date: 2024.11.25
 * Last Modified By  : winterver
 */

ENTRY(_start)

SECTIONS
{
    /* It used to be universally recommended to use 1M as a start offset,
     * as it was effectively guaranteed to be available under BIOS systems.
     * However, UEFI has made things more complicated, and experimental data
     * strongly suggests that 2M is a safer place to load. In 2016, a new
     * feature was introduced to the multiboot2 spec to inform bootloaders
     * that a kernel can be loaded anywhere within a range of addresses and
     * will be able to relocate itself to run from such a loader-selected
     * address, in order to give the loader freedom in selecting a span of
     * memory which is verified to be available by the firmware, in order to
     * work around this issue. This does not use that feature, so 2M was
     * chosen as a safer option than the traditional 1M.
     * */
    . = 2M;

    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.text)
    }

    /* Read-only data. */
    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    /* Read-write data (initialized) */
    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    /* Read-write data (uninitialized) and stack */
    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }

    /* Sections that are not referenced above are appended here.
     * The linker won't discard them. */
}
