//
// Created by urain39 on 18-9-16.
//

#include <stdio.h>

#include "cpu.h"
#include "mem.h"
#include "c8vm.h"

extern cpu_t cpu;

/*
 * 注意：写成extern mem_t *mem;
 * 会报错，应该是编译器理解的不一样
 */
extern mem_t mem[];

void cpu_init(void)
{
    cpu.active = true;
    cpu.rx = 0x00;
    cpu.ry = 0x00;
    cpu.sp = 0x00;
    cpu.ps = 0x00;
    cpu.pc = ROM_BEGIN;
}

/**
 * 个人认为在函数里不加参数可以减少参数传递从而提升运行效率。
 * 此外对于模拟CPU来说不使用switch可能效率会有很大提升。
 */

/* 函数共享静态变量 */
uint8_t low = 0;
uint8_t high = 0;
uint8_t zp_addr = 0;
uint8_t intr_idx = 0; // 中断向量指针

void i00() {
    // NOP, Do Nothing.
}

void i01() {
    // INT, IMM
    intr_idx = mem[++cpu.pc];
    PUSH_PC_TO_STACK(cpu, mem);
    low = mem[intr_idx];
    high = mem[++intr_idx];
    JMP_TO_ADDR(low, high);
}

/* 基础跳转操作指令 */
void i02() {
    // JMP, ABS
    low = mem[++cpu.pc];
    high = mem[++cpu.pc];
    cpu.pc = (high << 8) + low;
    JMP_TO_ADDR(low, high);
}

void i03() {
    // JSR, ABS
    low = mem[++cpu.pc];
    high = mem[++cpu.pc];
    PUSH_PC_TO_STACK(cpu, mem);
    JMP_TO_ADDR(low, high);
}

void i04() {
    // RTS, IMM
    POP_PC_FROM_STACK(cpu, mem);
}

/* 基础读取指令 */
void i05() {
    // LDX, IMM
    cpu.rx = mem[++cpu.pc];
}

void i06() {
    // LDY, IMM
    cpu.ry = mem[++cpu.pc];
}

void i07() {
    // LDX, ZP
    zp_addr = mem[++cpu.pc];
    cpu.rx = mem[zp_addr];
}

void i08() {
    // LDX, ZP
    zp_addr = mem[++cpu.pc];
    cpu.ry = mem[zp_addr];
}

void i09() {
    // LDX, ABS
    low = mem[++cpu.pc];
    high = mem[++cpu.pc];
    cpu.ry = mem[(high << 8) + low];
}

void i0a() {
    // LDY, ABS
    low = mem[++cpu.pc];
    high = mem[++cpu.pc];
    cpu.ry = mem[(high << 8) + low];
}

void i0b() {
    // STX, ZP
    zp_addr = mem[++cpu.pc];
    mem[zp_addr] = cpu.rx;
}

void i0c() {
    // STY, ZP
    zp_addr = mem[++cpu.pc];
    mem[zp_addr] = cpu.ry;
}

void i0d() {
    // STX, ABS
    low = mem[++cpu.pc];
    high = mem[++cpu.pc];
    mem[(high << 8) + low] = cpu.rx;
}

void i0e() {
    // STY, ABS
    low = mem[++cpu.pc];
    high = mem[++cpu.pc];
    mem[(high << 8) + low] = cpu.ry;
}

/* 基础比较操作指令 */
void i0f() {
    // CMP, IMM, ZP
}

void i10() {
    // CMP, IMM, ABS
}

void i11() {
    // CMP, 保留
}

void i12() {
    // CMP, 保留
}


void cpu_run(void)
{
    uint8_t opcode = 0x00; // NOP
    void (*instruction[256])() = {
            i00, i01, i02, i03, i04, i05,
            i06, i07, i08, i09, i0a, i0b,
            i0c, i0d, i0e, i0f, i10, i11,
            i12, //i13, i14, i15, i16, i17,
    };

    DEBUG("CPU开始执行\n", NULL);

    while (cpu.active) {
        // 理论上效率比switch好很多
        opcode = mem[cpu.pc];
        DEBUG("地址： 0x%X\n", cpu.pc);
        DEBUG("指令： 0x%X\n", opcode);
        instruction[opcode]();
        ++cpu.pc; // See also: mem.h JMP_TO_ADDR()
    }
}

void shutdown(void)
{
    cpu.active = false;
}
