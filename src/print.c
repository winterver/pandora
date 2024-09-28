#include <print.h>
#include <string.h>
#include <boot/bootinfo.h>

#define FW 8
#define FH 16
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

void kputchar(char c) {
    if (c == '\r') { x = 0; return; }
    if (c == '\t') { x += 8*(FW+1); return; }
    if (c == '\n') { x = 0; y += 16; return; }
    put(x, y, c);
    x += FW+1;
}

void kputs(const char* s) {
    while (*s) kputchar(*s++);
    kputchar('\n');
}
