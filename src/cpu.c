#include <stdio.h>
#include "cpu.h"
#include "instruction.h"

extern Instruction program[];
extern int program_size;

void execute_instruction(CPU *cpu, Instruction *inst);

void run(CPU *cpu) {
    while (cpu->pc < (uint32_t)program_size) {
        execute_instruction(cpu, &program[cpu->pc]);
        cpu->regs[0] = 0;
    }
}
