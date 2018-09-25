//
// Created by urain39 on 18-9-16.
//

#ifndef C8VM_MEM_H
#define C8VM_MEM_H

#include <stdint.h>

#include "cpu.h"

/**
 * ZP    　0x0000~0x00FF      256
 * 未使用　　0x0100~0x0FFF     3840
 * 显示内存　0x1000~0x1FFF     4096 (4K)
 * BIOS    0x2000~0x3FFF     4096 (8K)
 * 未使用   0x4000~0x6FFF     16384 (8K)
 * 栈 　  　0x7000~0x7FFF    4096 (4K)
 * ROM　 　0x8000~0xFFFF    32768 (32K)
 *
 * 其中0x00FE表示按键映射，0x00FF表示随机数
 */

#define MEM_SIZE        0x10000
#define DISPLAY_SIZE    0x1000
#define DISPLAY_BEGIN   0x1000
#define BIOS_SIZE       0x2000
#define BIOS_BEGIN      0x2000
#define ROM_BEGIN       0x8000
#define STACK_SIZE      0x1000
#define STACK_BEGIN     0x6000
#define ROM_MAXSIZE     0x7000

typedef uint8_t mem_t;

extern cpu_t cpu;
extern uint8_t low;
extern uint8_t high;

#define JMP_TO_ADDR(low, high) \
do { \
    cpu.pc = ( (high << 8) + low ) - 1; \
} while(0); // See also: c8vm.c cpu_run()

#define JMP_TO_ADDR_DIRECT(addr) \
do { \
    cpu.pc = addr - 1; \
} while(0);

#define PUSH_PC_TO_STACK(cpu, mem) \
do { \
    mem[STACK_BEGIN + cpu.sp] = (uint8_t)( (cpu.pc & 0x0F00) >> 8 ); \
    mem[STACK_BEGIN + ++cpu.sp] = (uint8_t)(cpu.pc & 0x00FF); \
} while (0);

#define  POP_PC_FROM_STACK(cpu, mem) \
do { \
    low = mem[STACK_BEGIN + cpu.sp]; \
    high = ( mem[STACK_BEGIN + --cpu.sp] & 0x0F00 ) >> 8; \
    cpu.pc = (high << 8) + low; \
} while (0);

void mem_init(void);

#endif //C8VM_MEM_H
