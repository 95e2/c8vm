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

typedef struct cpu_t {
    bool active;
    uint8_t  rx; // x寄存器
    uint8_t  ry; // y寄存器
    uint8_t  ps; // 状态寄存器
    uint16_t sp; // 栈指针
    uint16_t pc; // 程序计数器
} cpu_t;

void cpu_run(void);

/* 初始化CPU */
void cpu_init(void);

#endif //C8VM_CPU_H
