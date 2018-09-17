//
// Created by urain39 on 18-9-16.
//

#include <zconf.h>
#include "cpu.h"
#include "mem.h"
#include "c8vm.h"

#define CF (1<<0)
#define EF (1<<1)
#define VF (1<<2)
#define ZF (1<<7)

extern cpu_t cpu;
extern mem_t *mem;

void cpu_init(cpu_t *cpu)
{
    cpu->active = true;
    cpu->rx = 0x00;
    cpu->ry = 0x00;
    cpu->sp = 0x00;
    cpu->ps = 0x00;
    cpu->pc = ROM_BEGIN;
}

/**
 * 个人认为在函数里不加参数可以减少参数传递从而提升运行效率。
 * 此外对于模拟CPU来说可能不使用switch可能效率会有很大提升。
 *
 * 同时因为零页寻址与相对寻址有很大区别，所以统一为绝对寻址。
 */


void i00() {
    // NOP, Do Nothing.
}

/* 基础跳转操作指令 */

void i01() {
    // JMP, ABS
    uint8_t low = mem[cpu.pc];
    uint8_t high = mem[++cpu.pc];
    cpu.pc = (high << 8) + low;
}

void i02() {
    // JSR, ABS
    uint8_t low = mem[cpu.pc];
    uint8_t high = mem[++cpu.pc];
    mem[STACK_BEGIN + cpu.sp] = (uint8_t)(cpu.pc >> 8);
    mem[STACK_BEGIN + ++cpu.sp] = (uint8_t)(cpu.pc & 0x00FF);
    cpu.pc = (high << 8) + low;
}

void i03() {
    // RTS, ABS?
    uint8_t low = mem[STACK_BEGIN + cpu.sp];
    uint8_t high = mem[STACK_BEGIN + --cpu.sp];
    cpu.pc = (high << 8) + low;
}


/* 基础读取指令 */

void i04() {
    // LDX, IMM
    cpu.rx = mem[++cpu.pc];
}

void i05() {
    // LDY, IMM
    cpu.ry = mem[++cpu.pc];
}

void i06() {
    // LDX, ABS
    uint8_t low = mem[cpu.pc];
    uint8_t high = mem[++cpu.pc];
    cpu.rx = mem[(high << 8) + low];
}

void i07() {
    // LDY, ABS
    uint8_t low = mem[cpu.pc];
    uint8_t high = mem[++cpu.pc];
    cpu.ry = mem[(high << 8) + low];
}

void i08() {
    //
}


void cpu_run()
{

    void (*instruction[256])() = {
	    i00, i01, i02, i03, i04, i06,
            i07, i08,
    };

    uint8_t opcode = mem[cpu.pc++];
    while (cpu.active) {

        cpu.pc++; // 执行完始终指向下一条指令
    }
}

void shutdown()
{
    cpu.active = false;
}

