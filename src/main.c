void *memset(void *s, int c, int n)
{
    char *p=(char*)s;
    if(s && n>0) {
        while(n--) *p++ = (char)c;
    }
    return s;
}

void kmain(void) {
    memset((void*)0xb8000, 255, 256);
}
