#ifndef CPU_H  // ifndef is used to prevent multiple inclusions of the same header file
#define CPU_H // define the macro CPU_H

#include <stdint.h> // include standard integer types

#define NUM_REGS 32 // define the number of registers
#define MEM_SIZE 1048576 // define memory size (1 MB)

typedef struct {
    int32_t regs[NUM_REGS]; // array of 32-bit registers
    uint32_t pc; // program counter
    uint8_t memory[MEM_SIZE]; // memory array
} CPU;

void init_cpu(CPU *cpu); // This function initializes the CPU state

void run(CPU *cpu); // This function runs the CPU simulation, The difference between CPU and cpu is that CPU is the type name while cpu is a variable of that type.

#endif