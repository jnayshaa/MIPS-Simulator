# MIPS-Simulator
A simulator for MIPS assembly language written in C that supports integer operations: arithmetic, branching, memory operations, and syscalls.

## Function
This simulator parses and executes MIPS assembly programs, providing a virtual CPU with 32 registers and 1MB of memory. It handles basic MIPS instructions and system calls for I/O operations.

## File Structure

### Source Files (`src/`)
- **main.c** - Entry point; loads assembly program and initializes CPU
- **parser.c** - Parses MIPS assembly into instruction structs; handles labels in two-pass assembly
- **cpu.c** - Implements the fetch-execute cycle that runs the simulation
- **execute.c** - Executes individual instructions (arithmetic, memory, branching, syscalls)

### Header Files (`include/`)
- **cpu.h** - Defines CPU struct with 32 registers, PC, and memory
- **instruction.h** - Defines instruction types and instruction struct
- **parser.h** - Declares program loading function

### Assembly Programs
- **test.asm** - Simple test program that prints 42
- **test2.asm** - Reads an integer from user input and prints it back
- **test3.asm** - Tests Memory operations
- **test4.asm** - Tests Arethematic operation (addition)

### Build
- **makefile** - Compiles all source files into `mips_sim` executable

## How to Run

### Build the Simulator
```bash
make
```

### Run a Program
```bash
./mips_sim <program.asm>
```
Example: `./mips_sim tests/test2.asm`

### Manual Compilation (without make)
```bash
gcc -Wall -Wextra -std=c11 -Iinclude src/main.c src/cpu.c src/execute.c src/parser.c -o mips_sim
```
