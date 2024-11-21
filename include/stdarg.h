#ifndef _PANDORA_STDARG_H_
#define _PANDORA_STDARG_H_

#define va_list         __builtin_va_list
#define va_start(s, l)  __builtin_va_start(s, l)
#define va_arg(s, l)    __builtin_va_arg(s, l)
#define va_end(s)       __builtin_va_end(s)
#define va_copy(s, l)   __builtin_va_copy(s, l)

#endif
