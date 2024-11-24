/**
 * Copyright (c) 2024 winterver
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * File              : boot.h
 * Author            : winterver
 * Date              : 2024.9.26~
 * Last Modified Date: 2024.11.24
 * Last Modified By  : winterver
 */

#ifndef _PANDORA_BOOT_H_
#define _PANDORA_BOOT_H_

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
