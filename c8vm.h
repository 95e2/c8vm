//
// Created by urain39 on 18-9-16.
//

#ifndef C8VM_C8VM_H
#define C8VM_C8VM_H

#define CPU_ERROR   1
#define MEM_ERROR   2
#define ROM_ERROR   3
#define RUN_ERROR   4
#define USAGE_ERROR 5

#include "cpu.h"
#include "mem.h"

#ifdef _DEBUG
#define DEBUG(fmt, ...) \
do { \
    printf(fmt, __VA_ARGS__); \
} while(0);
#else
    #define DEBUG(fmt, ...)
#endif

#endif //C8VM_C8VM_H
