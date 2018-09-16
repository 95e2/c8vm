//
// Created by urain39 on 18-9-16.
//

#include "cpu.h"
#include "mem.h"

#define CF (1<<0)
#define EF (1<<1)
#define VF (1<<2)
#define ZF (1<<7)

void cpu_init(cpu_t *cpu)
{
    cpu->active = true;
    cpu->rx = 0x00;
    cpu->ry = 0x00;
    cpu->sp = 0x00;
    cpu->ps = 0x00;
    cpu->pc = ROM_BEGIN;
}

void i00(cpu_t *cpu) {
    // NOP, Do Nothing.
}

void i01() {
    // JMP

}

void cpu_run(cpu_t *cpu, mem_t *mem)
{
    uint8_t opcode = mem[cpu->pc++];

    while (cpu->active) {

    }
}

void shutdown(cpu_t *cpu)
{
    cpu->active = false;
}

