#include <print.h>
#include <string.h>
#include <boot/bootinfo.h>

static void printn(int n) {
    if (n/10) printn(n/10);
    kputchar(n%10 + '0');
}

void kmain(struct bootinfo* bi, int magic) {
    if (magic != BI_MAGIC) {
        memset(bi->vid_addr, 255, bi->vid_size);
        return;
    }

    init_video(bi);

    kputs("Hello World!");
    for (int i = 0; ; i++) {
        printn(i); kputchar('\r');
    }
}
