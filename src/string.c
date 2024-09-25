#include "string.h"

void *memset(void *s, int c, unsigned long n)
{
    char *p=(char*)s;
    if(s && n>0) {
        while(n--) *p++ = (char)c;
    }
    return s;
}

void *memcpy(void *dst, const void *src, unsigned long n)
{
    char *a=(char*)dst,*b=(char*)src;
    if(src && dst && src != dst && n>0) {
        while(n--) *a++ = *b++;
    }
    return dst;
}
