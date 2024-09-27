ARCH = x86_64
#provided by upper Makefile
#TARGET = pandora.efi
SRCS = $(wildcard *.c)
CFLAGS = -pedantic -Wall -Wextra --std=gnu11 -O2
LDFLAGS = --no-undefined

USE_GCC = 1
include uefi/Makefile
# uefi folder is from https://gitlab.com/bztsrc/posix-uefi
