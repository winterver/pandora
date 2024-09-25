#include "print.h"
#include "string.h"

#define W 80
#define H 25
#define ADDR ((char*)0xb8000)

static int x, y;
static char co = 0x7;

static void incy() {
    if (++y >= H) {
        memcpy(ADDR, ADDR+W*2, W*H*2-W*2);
        memset(ADDR+W*H*2-W*2, 0, W*2);
        y = H - 1;
    }
}

static void incx() {
    if (++x >= W) {
        x = 0;
        incy();
    }
}

void kputchar(char c) {
    char* v = ADDR + (y*W+x)*2;
    switch (c) {
    case '\r': x = 0;                       break;
    case '\n': x = 0; incy();               break;
    default:   v[0] = c; v[1] = co; incx(); break;
    }
}

void kputs(const char* s) {
    while (*s) { kputchar(*s++); }
    kputchar('\n');
}
