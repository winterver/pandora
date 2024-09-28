#ifndef _PANDORA_PRINT_H_
#define _PANDORA_PRINT_H_

struct bootinfo;
void init_video(struct bootinfo* bi);
void kputchar(char c);
void kputs(const char* s);

#endif
