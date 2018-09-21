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
static uint8_t low = 0;
static uint8_t high = 0;
static uint8_t zp_addr = 0;

void i00() {
    // NOP, Do Nothing.
}

/* 基础跳转操作指令 */
void i01() {
    // JMP, ABS
    low = mem[++cpu.pc];
    high = mem[++cpu.pc];
    cpu.pc = (high << 8) + low;
}

void i02() {
    // JSR, ABS
    low = mem[++cpu.pc];
    high = mem[++cpu.pc];
    PUSH_PC_TO_STACK(cpu, mem);
    cpu.pc = (high << 8) + low;
}

void i03() {
    // RTS, IMM
    POP_PC_FROM_STACK(cpu, mem);
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
    // LDX, ZP
    zp_addr = mem[++cpu.pc];
    cpu.rx = mem[zp_addr];
}

void i07() {
    // LDX, ZP
    zp_addr = mem[++cpu.pc];
    cpu.ry = mem[zp_addr];
}

void i08() {
    // LDX, ABS
    low = mem[++cpu.pc];
    high = mem[++cpu.pc];
    cpu.ry = mem[(high << 8) + low];
}

void i09() {
    // LDY, ABS
    low = mem[++cpu.pc];
    high = mem[++cpu.pc];
    cpu.ry = mem[(high << 8) + low];
}

void i0a() {
    // STX, ZP
    zp_addr = mem[++cpu.pc];
    mem[zp_addr] = cpu.rx;
}

void i0b() {
    // STY, ZP
    zp_addr = mem[++cpu.pc];
    mem[zp_addr] = cpu.ry;
}

void i0c() {
    // STX, ABS
    low = mem[++cpu.pc];
    high = mem[++cpu.pc];
    mem[(high << 8) + low] = cpu.rx;
}

void i0d() {
    // STY, ABS
    low = mem[++cpu.pc];
    high = mem[++cpu.pc];
    mem[(high << 8) + low] = cpu.ry;
}

/* 基础比较操作指令 */
void i0e() {
    // CMP, IMM, ZP
}

void i0f() {
    // CMP, IMM, ABS
}

void i10() {
    // CMP, 保留
}

void i11() {
    // CMP, 保留
}

void cpu_run(void)
{
    uint8_t opcode = 0x00; // NOP
    void (*instruction[256])() = {
            i00, i01, i02, i03, i04, i05,
            i06, i07, i08, i09, i0a, i0b,
            i0c, i0d, i0e, i0f, i10, i11,
    };

    DEBUG("CPU开始执行\n", NULL);

    while (cpu.active) {
        // 理论上效率比switch好很多
        opcode = mem[cpu.pc];
        DEBUG("地址： 0x%X\n", cpu.pc);
        DEBUG("指令： 0x%X\n", opcode);
        instruction[opcode]();
        ++cpu.pc; // 执行完始终指向下一条指令
    }
}

void shutdown(void)
{
    cpu.active = false;
}
