#ifndef VM_H
#define VM_H

#include <stdlib.h>
#include <stdio.h>

typedef enum instructions {
    MOV, // move
    SET, // set
    ADD, // add
    SEL, // select
    HLT, // halt
} instructions;

typedef struct register_ {
    char *byte;
    char *address;
} register_;

typedef struct byte_ {
    char *byte;
    char *address;
} byte_;

typedef struct RAM {
    byte_ *bytes[64];
} RAM;

typedef struct vm_ {
    RAM ram;
    register_ *register_0;
    register_ *register_1;
    register_ *instruction_register;
} vm_;

vm_ *init_vm();
int execute(vm_ *vm, int program[]);
int eval(vm_ *vm);

#endif
