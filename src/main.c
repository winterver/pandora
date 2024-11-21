#include <bootinfo.h>
#include <printk.h>

void kmain(struct bootinfo* bi) {
    init_video(bi);

    for (int i = 0; ; i++) {
        printk("%0*d\r", 10, i);
    }
}
