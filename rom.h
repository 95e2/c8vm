//
// Created by urain39 on 18-9-16.
//

#ifndef C8VM_ROM_H
#define C8VM_ROM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define  ROM_MAGIC "C8R"
#define  ROM_VERSION 0x01

typedef struct rom_header_t {
    char magic[4];
    uint16_t version;
} rom_header_t;

bool check_rom(rom_header_t *header);
bool load_rom(mem_t *mem, const char *filename);

#endif //C8VM_ROM_H
