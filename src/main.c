#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "parser.h"
#include "cache.h"

Instruction program[4096]; // 4096 is an arbitrary limit for program size and 'Instruction' is defined in instruction.h
int program_size = 0;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s program.asm\n", argv[0]);
        return 1;
    }

    CPU cpu = {0};

    load_program(argv[1], program, &program_size); // Load the program from the file
    
    // Initialize the cache you want
    cache_init(&cache_64_1word, 64, 1); // or
    // cache_init(&cache_32_2word, 32, 2);
    
    cpu.regs[29] = MEM_SIZE; // initialize $sp at top of memory
    run(&cpu);

    // Print cache statistics
    print_cache_stats(&cache_64_1word); // or
    // print_cache_stats(&cache_32_2word);

    return 0;
}
