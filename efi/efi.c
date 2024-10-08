#include <uefi.h>
#include <linux/elf.h>
#include <bootinfo.h>

void seek_read(FILE* f, size_t pos, void* buf, size_t n) {
    fseek(f, pos, SEEK_SET);
    fread(buf, 1, n, f);
}

__attribute__((naked, noreturn))
void jump_to_kernel(Elf64_Addr entry, struct bootinfo* bi) {
    asm("mov %1, %%rbx\n\t"
        "mov %0, %%rax\n\t"
        "jmp *%%rax\n"
        ::"r"(entry),
          "r"(bi)
         :"rax",
          "rbx");
}

__attribute__((noreturn))
void load_and_enter_kernel(char* path, struct bootinfo* bi) {
    FILE* f = fopen(path, "r");
    if (f == NULL) {
        printf("Cannot find kernel: %s\n", path);
        exit(-1);
    }

    Elf64_Ehdr ehdr;
    seek_read(f, 0, &ehdr, sizeof(ehdr));

    char verify[] = { 0x7f, 'E', 'L', 'F', ELFCLASS64 };
    if (memcmp(ehdr.e_ident, verify, sizeof(verify))) {
        printf("Not an ELF64 file: %s\n", path);
        exit(-1);
    }

    if (ehdr.e_shnum == 0) {
        printf("Can't load %s: no section or "
               "too many sections (>= %d)\n",
               path, SHN_LORESERVE);
        exit(-1);
    }

    for (int i = 1; i < ehdr.e_shnum; i++) {
        size_t pos = ehdr.e_shoff + i * ehdr.e_shentsize;

        Elf64_Shdr shdr;
        seek_read(f, pos, &shdr, sizeof(shdr));
        if (shdr.sh_type == SHT_NOBITS || shdr.sh_addr == 0)
            continue;

        seek_read(f, shdr.sh_offset, (void*)shdr.sh_addr, shdr.sh_size);
    }

    fclose(f);
    exit_bs();

    jump_to_kernel(ehdr.e_entry, bi);
}

struct bootinfo* boot_service() {
    efi_guid_t guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    efi_gop_t* gop = NULL;

    uintn_t status = 0;
    status = BS->LocateProtocol(&guid, NULL, (void**)&gop);
    if (EFI_ERROR(status)) {
        printf("Unable to locate GOP\n");
        exit(-1);
    }

    efi_gop_mode_info_t* info = NULL;
    uintn_t size = 0;
   
    status = gop->QueryMode(gop, gop->Mode?gop->Mode->Mode:0, &size, &info);
    if (status == EFI_NOT_STARTED) {
        status = gop->SetMode(gop, 0);
        if (EFI_ERROR(status)) {
            printf("Unable to start GOP\n");
            exit(-1);
        }
    }

    void*    vid_addr   = (void*)gop->Mode->FrameBufferBase;
    unsigned vid_size   = gop->Mode->FrameBufferSize;
    unsigned vid_width  = gop->Mode->Information->HorizontalResolution;
    unsigned vid_height = gop->Mode->Information->VerticalResolution;
    unsigned vid_pps    = gop->Mode->Information->PixelsPerScanLine;
    unsigned vid_format = VID_FORMAT_UNKNOWN;
    switch (gop->Mode->Information->PixelFormat)
    {
    case PixelRedGreenBlueReserved8BitPerColor:
        vid_format = VID_FORMAT_RGB32;
        break;
    case PixelBlueGreenRedReserved8BitPerColor:
        vid_format = VID_FORMAT_BGR32;
        break;
    default:
        vid_format = VID_FORMAT_UNKNOWN;
        break;
    }

    static struct bootinfo bi = { 0 };
    bi.vid_addr     = vid_addr;
    bi.vid_size     = vid_size;
    bi.vid_width    = vid_width;
    bi.vid_height   = vid_height;
    bi.vid_format   = vid_format;
    bi.vid_pps      = vid_pps;
    return &bi;
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    struct bootinfo* bi = boot_service();
    if (bi->vid_format == VID_FORMAT_UNKNOWN) {
        printf("Unsupported pixel format\n");
        return -1;
    }
    load_and_enter_kernel("pandora.bin", bi);
}
