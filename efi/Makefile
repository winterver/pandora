ARCH = x86_64
CFLAGS = -pedantic -Wall -Wextra --std=gnu11 -O2
LDFLAGS = --no-undefined
SRCS = $(wildcard *.c)
TARGET = pandora.efi

USE_GCC = 1
include uefi/Makefile
# uefi folder is from https://gitlab.com/bztsrc/posix-uefi
