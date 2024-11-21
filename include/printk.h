#ifndef _PANDORA_PRINT_H_
#define _PANDORA_PRINT_H_

struct bootinfo;
void init_video(struct bootinfo* bi);
int printk(const char* fmt, ...);

#endif
