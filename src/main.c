#include <print.h>
#include <string.h>
#include <boot/bootinfo.h>

static void printn(int n) {
    if (n/10) printn(n/10);
    kputchar(n%10 + '0');
}

void kmain(struct bootinfo* bi) {
    init_video(bi);

    for (int i = 0; ; i++) {
        printn(i); //kputchar('\r');
    }
}
