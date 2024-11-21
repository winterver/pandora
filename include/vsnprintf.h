#ifndef _PANDORA_VSNPRINTF_H_
#define _PANDORA_VSNPRINTF_H_

#include <stddef.h>
#include <stdarg.h>

int vsnprintf(char *buf, size_t size, const char *fmt, va_list ap);

#endif
