#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cpu.h"
#include "mem.h"
#include "rom.h"
#include "c8vm.h"

#ifdef _DEBUG
#define DEBUG(fmt, ...) \
do { \
    printf(fmt, __VA_ARGS__); \
} while(0);
#else
#define DEBUG(fmt, ...)
#endif

static cpu_t cpu;
static mem_t mem[MEM_SIZE];

int main(int argc, char **argv)
{
    cpu_init(&cpu);
    DEBUG("CPU初始化完毕\n", NULL)

    mem_init(&mem); // 忽略这里的警告
    DEBUG("内存初始化完毕\n", NULL)

    if (argc < 2) {
        printf("Usage: %s <rom>\n", argv[0]);
        exit(USAGE_ERROR);
    }

    if ( load_rom(mem, argv[1]) == false ) {
        fprintf(stderr, "Error: cannot open '%s'\n", argv[1]);
    }

}