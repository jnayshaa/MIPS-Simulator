#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "parser.h"

Instruction program[4096]; // 4096 is an arbitrary limit for program size and 'Instruction' is defined in instruction.h
int program_size = 0;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s program.asm\n", argv[0]);
        return 1;
    }

    CPU cpu = {0};

    load_program(argv[1], program, &program_size); // Load the program from the file
    run(&cpu);

    return 0;
}
