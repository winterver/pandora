CC = gcc
LD = ld

CFLAGS = -std=c11 -nostdinc -nostdlib -Iinclude -pedantic -Wall -Wextra \
         -O2 -ffreestanding -fno-asynchronous-unwind-tables
LDFLAGS = -znoexecstack -Tsrc/linker.ld

SRCS = $(wildcard src/*.S	\
                  src/*.c)
OBJS = $(patsubst %.c,%.o,	\
       $(patsubst %.S,%.o,	\
       $(SRCS)))
TARGET = pandora.bin

# postfixing with .exe for WSL
QEMU = qemu-system-x86_64.exe
QFLAGS = -net none -bios /usr/share/ovmf/OVMF.fd

all: subprojs $(TARGET)

subprojs:
	$(MAKE) -C efi

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(TARGET)

run: all
	mkdir -p vfat/efi/boot
	cp -u $(TARGET) vfat/
	cp -u efi/*.efi vfat/efi/boot/bootx64.efi
	$(QEMU) $(QFLAGS) -drive file=fat:rw:vfat,format=raw

clean:
	$(MAKE) -C efi clean
	rm $(OBJS) 2> /dev/null || true
	rm $(TARGET) 2> /dev/null || true
