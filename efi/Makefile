all: pandora.efi

pandora.efi: pandora.so
	objcopy pandora.so pandora.efi		\
		--target=efi-app-x86_64			\
		-j .text						\
		-j .sdata						\
		-j .data						\
		-j .dynamic						\
		-j .dynsym						\
		-j .rel							\
		-j .rela						\
		-j .reloc

pandora.so: efi.o
	ld efi.o gnuefi/crt0-efi-x86_64.o	\
		-T gnuefi/elf_x86_64_efi.lds	\
		-o pandora.so					\
		-shared							\
		-nostdlib						\
		-znocombreloc					\
		--no-undefined					\
		-Bsymbolic						\
		-L gnuefi						\
		-l:libgnuefi.a					\
		-l:libefi.a

efi.o: efi.c
	gcc -c efi.c						\
		-DEFI_FUNCTION_WRAPPER			\
		-fno-stack-protector			\
		-fshort-wchar					\
		-mno-red-zone					\
		-I gnuefi/inc					\
		-fpic

clean:
	rm efi.o pandora.so pandora.efi 2> /dev/null || true
