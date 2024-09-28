ARCH = x86_64
CFLAGS = --std=gnu11 -pedantic -Wall -Wextra -I../include -O2
LDFLAGS = --no-undefined
SRCS = $(wildcard *.c)
TARGET = pandora.efi

USE_GCC = 1
include uefi/Makefile
# uefi folder is from https://gitlab.com/bztsrc/posix-uefi
