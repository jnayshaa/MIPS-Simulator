#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"
#include "instruction.h"
#include "cache.h"

void execute_instruction(CPU *cpu, Instruction *inst) {
    switch (inst->type) {

        case ADD:
            cpu->regs[inst->rd] =
                cpu->regs[inst->rs] + cpu->regs[inst->rt];
            cpu->pc++;
            break;

        case SUB:
            cpu->regs[inst->rd] =
                cpu->regs[inst->rs] - cpu->regs[inst->rt];
            cpu->pc++;
            break;

        case ADDI:
            cpu->regs[inst->rt] =
                cpu->regs[inst->rs] + inst->imm;
            cpu->pc++;
            break;

        case MUL:
            cpu->regs[inst->rd] =
                cpu->regs[inst->rs] * cpu->regs[inst->rt];
            cpu->pc++;
            break;

        case LW: { // includes cache access
            int addr = cpu->regs[inst->rs] + inst->imm;
            if (addr < 0 || addr + (int)sizeof(int32_t) > MEM_SIZE) {
                fprintf(stderr, "ERROR: LW access out of bounds: addr=%d\n", addr);
                exit(1);
            }
            cache_access(addr);
            int32_t val;
            memcpy(&val, &cpu->memory[addr], sizeof(int32_t));
            cpu->regs[inst->rt] = val;
            cpu->pc++;
            break;
        }

        case SW: { // includes cache access
            int addr = cpu->regs[inst->rs] + inst->imm;
            if (addr < 0 || addr + (int)sizeof(int32_t) > MEM_SIZE) {
                fprintf(stderr, "ERROR: SW access out of bounds: addr=%d\n", addr);
                exit(1);
            }
            cache_access(addr);
            memcpy(&cpu->memory[addr], &cpu->regs[inst->rt], sizeof(int32_t));
            cpu->pc++;
            break;
        }

        case BEQ:
            if (cpu->regs[inst->rs] == cpu->regs[inst->rt])
                cpu->pc = inst->imm;
            else
                cpu->pc++;
            break;

        case BNE:
            if (cpu->regs[inst->rs] != cpu->regs[inst->rt])
                cpu->pc = inst->imm;
            else
                cpu->pc++;
            break;

        case J:
            cpu->pc = inst->imm;
            break;

        case JAL:
            cpu->regs[31] = cpu->pc + 1;  // save return address in $ra
            cpu->pc = inst->imm;
            break;

        case JR:
            cpu->pc = cpu->regs[inst->rs];
            break;

        case SYSCALL:
            switch (cpu->regs[2]) {
                case 1:
                    printf("%d", cpu->regs[4]);
                    break;
                case 5:
                    scanf("%d", &cpu->regs[2]);
                    break;
                case 10:
                    exit(0);
            }
            cpu->pc++;
            break;

        default:
            printf("Invalid instruction at PC %u\n", cpu->pc);
            exit(1);
    }
}
