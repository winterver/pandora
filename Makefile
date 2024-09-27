CC = gcc
LD = ld

CFLAGS = -std=c11 -nostdinc -nostdlib -ffreestanding -pedantic -Wall -Wextra -O2
LDFLAGS = -znoexecstack -Tsrc/linker.ld

SRCS = $(wildcard src/*.S src/*.c)
OBJS = $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(SRCS)))
TARGET = pandora.bin

# postfixing with .exe for WSL
QEMU = qemu-system-x86_64.exe
QFLAGS = -net none -bios /usr/share/ovmf/OVMF.fd

all: subprojs $(TARGET)

subprojs:
	@cd efi && make -s TARGET=$(basename $(TARGET)).efi

%.o: %.c
	@echo Compiling $<
	@$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	@echo Compiling $<
	@$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	@echo Linking $(TARGET)
	@$(LD) $(LDFLAGS) $(OBJS) -o $(TARGET)
	@chmod -x $(TARGET)

run: all
	@mkdir -p vfat
	@cp -u $(TARGET) vfat
	@cp -u efi/$(basename $(TARGET)).efi vfat
	@$(QEMU) $(QFLAGS) -drive file=fat:rw:vfat,format=raw

clean:
	@rm $(OBJS) 2> /dev/null || true

distclean:
	@rm $(TARGET) 2> /dev/null || true

cleanall: clean distclean
