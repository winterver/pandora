CC = gcc
LD = ld

CFLAGS = -m32 -std=c11 -nostdinc -nostdlib -ffreestanding -pedantic -Wall -Wextra -O2
LDFLAGS = -melf_i386 -znoexecstack -Tsrc/multiboot.ld

SRCS = $(wildcard src/*.S src/*.c)
OBJS = $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(SRCS)))
TARGET = pandora.bin

# postfixing with .exe for WSL
QEMU = qemu-system-x86_64.exe
QFLAGS = -net none

all: $(OBJS) $(TARGET)

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

run: $(TARGET)
	@$(QEMU) $(QFLAGS) -kernel $(TARGET)

clean:
	@rm $(OBJS) 2> /dev/null || true

distclean: clean
	@rm $(TARGET) 2> /dev/null || true
