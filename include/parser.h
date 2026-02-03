#ifndef PARSER_H
#define PARSER_H

#include "instruction.h"

// Function to load a program from a file into an array of Instructions
void load_program(const char *filename, Instruction *program, int *program_size);

#endif
