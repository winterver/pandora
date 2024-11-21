#ifndef _PANDORA_BOOTINFO_H_
#define _PANDORA_BOOTINFO_H_

#define VID_FORMAT_UNKNOWN  0
#define VID_FORMAT_RGB32    1
#define VID_FORMAT_BGR32    2

struct bootinfo {
    void*    mm_lomem;
    void*    mm_himem;

    void*    vid_addr;
    unsigned vid_size;
    unsigned vid_width;
    unsigned vid_height;
    unsigned vid_format;    // bits per pixel
    unsigned vid_pps;       // pixels per scanline
};

#endif
