#include <print.h>
#include <string.h>
#include <boot/bootinfo.h>

/*
static void printn(int n) {
    if (n/10) printn(n/10);
    kputchar(n%10 + '0');
}

void kmain(multiboot_info_t* mbd, unsigned int magic) {
    memset((void*)0xb8000, 0, 4000);
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        kputs("Invalid magic!");
        return;
    }
    kputs("Valid magic!");
}
*/

void kmain(struct bootinfo* bi, int magic) {
    if (magic == BI_MAGIC) {
        while (1);
    }
}
