#include <print.h>
#include <string.h>
#include <boot/bootinfo.h>

extern char font_vga[4096];

static int* vid; // video address
static int ppl; // pixels per line
static int fg;
static int bg;

static void put(int x, int y, char c) {
    int* v = vid + x + y * ppl;
    char* f = font_vga + c * 16;
    for (int i = 0; i < 16; i++) {
        v[0] = f[i] & (1 << 7) ? fg : bg;
        v[1] = f[i] & (1 << 6) ? fg : bg;
        v[2] = f[i] & (1 << 5) ? fg : bg;
        v[3] = f[i] & (1 << 4) ? fg : bg;
        v[4] = f[i] & (1 << 3) ? fg : bg;
        v[5] = f[i] & (1 << 2) ? fg : bg;
        v[6] = f[i] & (1 << 1) ? fg : bg;
        v[7] = f[i] & (1 << 0) ? fg : bg;
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

void kputchar(char c) {
    if (c == '\r') { x = 0; return; }
    if (c == '\n') { x = 0; y += 16; return; }
    put(x, y, c);
    x += 9;
}

void kputs(const char* s) {
    while (*s) kputchar(*s++);
    kputchar('\n');
}
