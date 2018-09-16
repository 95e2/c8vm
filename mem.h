//
// Created by urain39 on 18-9-16.
//

#ifndef C8VM_MEM_H
#define C8VM_MEM_H

#include <stdint.h>

#define MEM_SIZE        0x10000
#define ROM_BEGIN       0x8000
#define STACK_BEGIN     0x6000
#define ROM_MAXSIZE     0x7000
#define DISPLAY_BEGIN   0xFC00


typedef uint8_t mem_t;

void mem_init(mem_t *mem);

#endif //C8VM_MEM_H
