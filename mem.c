//
// Created by urain39 on 18-9-16.
//

#include "mem.h"

void mem_init(mem_t *mem)
{
    unsigned int i = 0;
    for (; i < ROM_BEGIN; i++)
        mem[i] = 0;
}
