//
// Created by urain39 on 18-9-16.
//

#ifndef C8VM_CPU_H
#define C8VM_CPU_H

#include <stdint.h>
#include <stdbool.h>

#define CF (1<<0)
#define EF (1<<1)
#define VF (1<<2)
#define ZF (1<<7)

#define PUSH_PC_TO_STACK(cpu, mem) \
do { \
    mem[STACK_BEGIN + cpu.sp] = (uint8_t)(cpu.pc >> 8); \
    mem[STACK_BEGIN + ++cpu.sp] = (uint8_t)(cpu.pc & 0x00FF); \
} while (0);

#define  POP_PC_FROM_STACK(cpu, mem) \
do { \
    low = mem[STACK_BEGIN + cpu.sp]; \
    high = mem[STACK_BEGIN + --cpu.sp]; \
    cpu.pc = (high << 8) + low; \
} while (0);

typedef struct cpu_t {
    bool active;
    uint8_t  rx; // x寄存器
    uint8_t  ry; // y寄存器
    uint8_t  ps; // 状态寄存器
    uint16_t sp; // 栈指针
    uint16_t pc; // 程序计数器
} cpu_t;


void cpu_run();

/* 初始化CPU */
void cpu_init(cpu_t *cpu);


#endif //C8VM_CPU_H
