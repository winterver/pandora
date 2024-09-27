#include <uefi.h>
#include <linux/elf.h>

void seek_read(FILE* f, size_t pos, void* buf, size_t n) {
    fseek(f, pos, SEEK_SET);
    fread(buf, 1, n, f);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("usage: elfload <elf_file>\n");
        return -1;
    }

    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("no such file: %s\n", argv[1]);
        return -1;
    }

    Elf64_Ehdr ehdr;
    seek_read(f, 0, &ehdr, sizeof(ehdr));

    char verify[] = { 0x7f, 'E', 'L', 'F', ELFCLASS64 };
    if (memcmp(ehdr.e_ident, verify, sizeof(verify))) {
        printf("not an ELF64 file: %s\n", argv[1]);
        return -1;
    }

    if (ehdr.e_shnum == 0) {
        printf("can't load %s: no section or "
               "too much sections (>= %d)\n",
               argv[1], SHN_LORESERVE);
        return -1;
    }

    for (int i = 1; i < ehdr.e_shnum; i++) {
        size_t pos = ehdr.e_shoff + i * ehdr.e_shentsize;

        Elf64_Shdr shdr;
        seek_read(f, pos, &shdr, sizeof(shdr));
        if (shdr.sh_type == SHT_NOBITS || shdr.sh_addr == 0)
            continue;

        /*
        printf("%02d\t0x%x\t0x%x\t0x%x\n", i,
               shdr.sh_offset,
               shdr.sh_addr,
               shdr.sh_size);
        */
        seek_read(f,
            shdr.sh_offset,
            (void*)shdr.sh_addr,
            shdr.sh_size);
    }

    exit_bs();
    asm("mov %0, %%rax\n\t"
        "jmp *%%rax\n"
        :
        :"m"(ehdr.e_entry)
        :"rax");
}
