//
// Created by urain39 on 18-9-16.
//

#include "mem.h"

extern mem_t mem[];

void mem_init(void)
{
    unsigned int i = 0;
    for (; i < ROM_BEGIN; i++)
        mem[i] = 0;
}
