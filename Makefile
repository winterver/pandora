CC = gcc
LD = ld

CFLAGS = -std=gnu11 -nostdinc -nostdlib -Iinclude -pedantic -Wall -Wextra \
         -m32 -O2 -fPIE -ffreestanding -fno-asynchronous-unwind-tables \
		 -fno-stack-protector -mgeneral-regs-only
LDFLAGS = -melf_i386 -znoexecstack -Tsrc/linker.ld

SRCS = $(wildcard src/*.S	\
                  src/*.c)
OBJS = $(patsubst %.c,%.o,	\
       $(patsubst %.S,%.o,	\
       $(SRCS)))
TARGET = pandora.bin

QEMU = qemu-system-x86_64.exe
QFLAGS = -nographic

all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(TARGET)

run: all
	$(QEMU) $(QFLAGS)

clean:
	rm $(OBJS) 2> /dev/null || true
	rm $(TARGET) 2> /dev/null || true
