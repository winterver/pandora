#ifndef _PANDORA_BOOTINFO_H_
#define _PANDORA_BOOTINFO_H_

struct bootinfo {
    unsigned vid_width;
    unsigned vid_height;
    unsigned vid_depth;
    void*    vid_addr;

    void*    mm_lomem;
    void*    mm_himem;
};

#endif
