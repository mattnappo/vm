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
    char byte;
} register_;

typedef struct byte_ {
    char byte;
    char *address;
} byte_;

typedef struct RAM {
    byte_ *bytes[64];
} RAM;

typedef struct vm_ {
    RAM *ram;
    register_ *register_0;
    register_ *register_1;

    register_ *instruction_register;
    register_ *instruction_address_register;
} vm_;

vm_ *init_vm();
int load_program(vm_ *vm, int program[]);
int ram_dump(vm_ *vm);

int execute(vm_ *vm);

#endif
