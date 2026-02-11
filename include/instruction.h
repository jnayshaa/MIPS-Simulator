#ifndef INSTRUCTION_H
#define INSTRUCTION_H

typedef enum { // instruction types from assembly language
    ADD, SUB, ADDI, MUL,
    LW, SW,
    BEQ, BNE,
    J, JAL, JR,
    SYSCALL,
    INVALID
} InstrType;

typedef struct {
    InstrType type;
    char raw[128];  
    int rd, rs, rt; // destination and source registers
    int imm; // immediate value
    char label[32]; // label for branch and jump instructions
} Instruction;

#endif
