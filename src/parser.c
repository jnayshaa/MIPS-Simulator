#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"

typedef struct {
    char name[32];
    int addr;
} Label;

static Label labels[256];
static int label_count = 0;

static int reg_num(const char *r) {
    if (!strcmp(r, "$zero")) return 0;
    if (!strcmp(r, "$v0")) return 2;
    if (!strcmp(r, "$v1")) return 3;
    if (!strcmp(r, "$a0")) return 4;
    if (!strcmp(r, "$a1")) return 5;
    if (!strcmp(r, "$a2")) return 6;
    if (!strcmp(r, "$a3")) return 7;
    if (!strcmp(r, "$sp")) return 29;
    if (!strcmp(r, "$ra")) return 31;
    if (r[1] == 't') return 8 + (r[2] - '0');
    if (r[1] == 's') return 16 + (r[2] - '0');
    return atoi(r + 1);
}

static void trim(char *s) {
    while (isspace(*s)) memmove(s, s + 1, strlen(s));
    int n = strlen(s);
    while (n > 0 && isspace(s[n - 1])) s[--n] = 0;
}

void load_program(const char *filename, Instruction *program, int *program_size) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("fopen");
        exit(1);
    }

    char line[256];
    int pc = 0;

    // pass 1: labels
    while (fgets(line, sizeof(line), f)) {
        char *c = strchr(line, '#');
        if (c) *c = 0;
        trim(line);
        if (strlen(line) == 0) continue;

        if (strchr(line, ':')) {
            char *colon = strchr(line, ':');
            *colon = 0;
            strcpy(labels[label_count].name, line);
            labels[label_count].addr = pc;
            label_count++;
        } else {
            pc++;
        }
    }

    rewind(f);
    pc = 0;

    // pass 2: instructions
    while (fgets(line, sizeof(line), f)) {
        char *c = strchr(line, '#');
        if (c) *c = 0;
        trim(line);
        if (strlen(line) == 0) continue;
        if (strchr(line, ':')) continue;

        Instruction *inst = &program[pc];
        inst->type = INVALID;

        char *op = strtok(line, " ,()");
        if (!op) continue;

        if (!strcmp(op, "add")) {
            inst->type = ADD;
            inst->rd = reg_num(strtok(NULL, " ,()"));
            inst->rs = reg_num(strtok(NULL, " ,()"));
            inst->rt = reg_num(strtok(NULL, " ,()"));
        }
        else if (!strcmp(op, "sub")) {
            inst->type = SUB;
            inst->rd = reg_num(strtok(NULL, " ,()"));
            inst->rs = reg_num(strtok(NULL, " ,()"));
            inst->rt = reg_num(strtok(NULL, " ,()"));
        }
        else if (!strcmp(op, "addi")) {
            inst->type = ADDI;
            inst->rt = reg_num(strtok(NULL, " ,()"));
            inst->rs = reg_num(strtok(NULL, " ,()"));
            inst->imm = atoi(strtok(NULL, " ,()"));
        }
        else if (!strcmp(op, "mul")) {
            inst->type = MUL;
            inst->rd = reg_num(strtok(NULL, " ,()"));
            inst->rs = reg_num(strtok(NULL, " ,()"));
            inst->rt = reg_num(strtok(NULL, " ,()"));
        }
        else if (!strcmp(op, "lw")) {
            inst->type = LW;
            inst->rt = reg_num(strtok(NULL, " ,()"));
            inst->imm = atoi(strtok(NULL, " ,()"));
            inst->rs = reg_num(strtok(NULL, " ,()"));
        }
        else if (!strcmp(op, "sw")) {
            inst->type = SW;
            inst->rt = reg_num(strtok(NULL, " ,()"));
            inst->imm = atoi(strtok(NULL, " ,()"));
            inst->rs = reg_num(strtok(NULL, " ,()"));
        }
        else if (!strcmp(op, "beq")) {
            inst->type = BEQ;
            inst->rs = reg_num(strtok(NULL, " ,()"));
            inst->rt = reg_num(strtok(NULL, " ,()"));
            char *label_token = strtok(NULL, " ,()");
            if (label_token) strcpy(inst->label, label_token);
        }
        else if (!strcmp(op, "bne")) {
            inst->type = BNE;
            inst->rs = reg_num(strtok(NULL, " ,()"));
            inst->rt = reg_num(strtok(NULL, " ,()"));
            char *label_token = strtok(NULL, " ,()");
            if (label_token) strcpy(inst->label, label_token);
        }
        else if (!strcmp(op, "j")) {
            inst->type = J;
            char *label_token = strtok(NULL, " ,()");
            if (label_token) strcpy(inst->label, label_token);
        }
        else if (!strcmp(op, "jal")) {
            inst->type = JAL;
            char *label_token = strtok(NULL, " ,()");
            if (label_token) strcpy(inst->label, label_token);
        }
        else if (!strcmp(op, "jr")) {
            inst->type = JR;
            inst->rs = reg_num(strtok(NULL, " ,()"));
        }
        else if (!strcmp(op, "syscall")) {
            inst->type = SYSCALL;
        }

        pc++;
    }

    fclose(f);
    *program_size = pc;

    // resolve labels
    for (int i = 0; i < *program_size; i++) {
        Instruction *inst = &program[i];
        if (inst->type == BEQ || inst->type == BNE || inst->type == J || inst->type == JAL) {
            for (int j = 0; j < label_count; j++) {
                if (!strcmp(inst->label, labels[j].name)) {
                    inst->imm = labels[j].addr;
                }
            }
        }
    }
}
