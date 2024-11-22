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
 * File              : string.c
 * Author            : winterver
 * Date              : 2024.9.26~
 * Last Modified Date: 2024.11.22
 * Last Modified By  : winterver
 */

#include "string.h"

void *memset(void *s, int c, unsigned long n)
{
    char *p=(char*)s;
    if(s && n>0) {
        while(n--) *p++ = (char)c;
    }
    return s;
}

void *memcpy(void *dst, const void *src, unsigned long n)
{
    char *a=(char*)dst,*b=(char*)src;
    if(src && dst && src != dst && n>0) {
        while(n--) *a++ = *b++;
    }
    return dst;
}
