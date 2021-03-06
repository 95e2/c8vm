//
// Created by urain39 on 18-9-16.
//

#include <stdio.h>
#include <string.h>

#include "mem.h"
#include "rom.h"
#include "c8vm.h"

bool check_rom(rom_header_t *header)
{
    if ( strncmp(header->magic, ROM_MAGIC, sizeof(ROM_MAGIC)) != 0) {
        fprintf(stderr, "Error: rom file header error!\n");
        return false;
    }

    if ( header->version < ROM_VERSION ) {
        fprintf(stderr, "Error: rom version is too old!\n");
        fprintf(stderr, "Current ROM Version: %d\n", header->version);
        return false;
    }

    return true;
}

bool load_rom(mem_t *mem, const char *filename)
{
    FILE *fp = NULL;
    if ( (fp = fopen(filename, "r")) == NULL) {
        DEBUG("reason: cannot open file <%s>!\n", filename);
        return false;
    }

    rom_header_t header_buf;
    fread(&header_buf, sizeof(rom_header_t), 1, fp);

    if ( check_rom(&header_buf) == false) {
        DEBUG("reason: cannot header error!\n", NULL);
        fclose(fp);
        return false;
    }

    // 将ROM数据加载到内存
    if ( fread((void *)&mem[ROM_BEGIN], ROM_MAXSIZE, 1, fp) == 0) {
        fclose(fp);
        return false;
    }
    fclose(fp);

    return true;
}
