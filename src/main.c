#include "print.h"
#include "string.h"

static void printn(int n) {
    if (n/10) printn(n/10);
    kputchar(n%10 + '0');
}

void kmain(void) {
    memset((void*)0xb8000, 0, 4000);
    for (int i = 0; ; i++) {
        printn(i);
        kputchar('\n');
    }
}
