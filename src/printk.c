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
 * File              : printk.c
 * Author            : winterver
 * Date              : 2024.9.26~
 * Last Modified Date: 2024.11.22
 * Last Modified By  : winterver
 */

#include <printk.h>
#include <string.h>
#include <vsnprintf.h>
#include <boot.h>

#define FW 8
#define FH 16
#define GAP 1
extern char font_vga[4096];

static int* vid; // video address
static int ppl; // pixels per line
static int fg;
static int bg;

static void put(int x, int y, char c) {
    int* v = vid + x + y * ppl;
    char* f = font_vga + c * 16;
    for (int i = 0; i < FH; i++) {
        for (int j = 0; j < FW; j++) {
            v[j] = f[i] & (1 << (FW-j-1)) ? fg : bg;
        }
        v += ppl;
    }
}

static int w, h;
static int x, y;

void init_video(struct bootinfo* bi) {
    memset(bi->vid_addr, 0, bi->vid_size);

    vid = bi->vid_addr;
    ppl = bi->vid_pps;
    fg = 0xffffffff;
    bg = 0;

    w = bi->vid_width;
    h = bi->vid_height;
    x = y = 0;
}

static void nextline() {
    x = 0;
    if ((y + FH) <= (h - FH)) y += FH;
    else memcpy(vid, vid+FH*ppl, 4*(h-FH)*ppl);
}

static void nextcolumn(int col) {
    for (int i = 0; i < col; i++) {
        x += FW;
        if (x <= (w - FW)) x += GAP;
        if (x > (w - FW)) nextline();
    }
}

static void putc(char c) {
    if (c == '\r') { x = 0; return; }
    if (c == '\t') { nextcolumn(8); return; }
    if (c == '\n') { nextline(); return; }
    put(x, y, c);
    nextcolumn(1);
}

static void puts(const char* s) {
    while (*s) putc(*s++);
}

int printk(const char* fmt, ...) {
    char buf[1024];
    va_list list;
    int n;

    va_start(list, fmt);
    n = vsnprintf(buf, sizeof(buf), fmt, list);
    va_end(list);

    puts(buf);

    return n;
}
