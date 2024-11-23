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
 * File              : port.h
 * Author            : winterver
 * Date              : 2024.11.23
 * Last Modified Date: 2024.11.23
 * Last Modified By  : winterver
 */

#ifndef _PANDORA_PORT_H_
#define _PANDORA_PORT_H_
#include <types.h>

inline __u8
inb(__u16 p)
{
    __u8 ret;
    asm volatile ("inb %%dx, %%al":"=a"(ret):"d"(p));
    return ret;
}

inline __u16
inw(__u16 p)
{
    __u16 ret;
    asm volatile ("inw %%dx, %%ax":"=a"(ret):"d"(p));
    return ret;
}

inline __u32
ind(__u16 p)
{
    __u32 ret;
    asm volatile ("ind %%dx, %%eax":"=a"(ret):"d"(p));
    return ret;
}

inline __u64
inq(__u16 p)
{
    __u64 ret;
    asm volatile ("inq %%dx, %%rax":"=a"(ret):"d"(p));
    return ret;
}

inline void
outb(__u16 p, __u8 v)
{
    asm volatile ("outb %%al, %%dx"::"d"(p),"a"(v));
}

inline void
outw(__u16 p, __u16 v)
{
    asm volatile ("outw %%ax, %%dx"::"d"(p),"a"(v));
}

inline void
outd(__u16 p, __u32 v)
{
    asm volatile ("outd %%eax, %%dx"::"d"(p),"a"(v));
}

inline void
outq(__u16 p, __u64 v)
{
    asm volatile ("outq %%rax, %%dx"::"d"(p),"a"(v));
}

#endif
