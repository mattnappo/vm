#ifndef VM_H
#define VM_H

#include <stdlib.h>
#include <stdio.h>

#define RAM_SIZE 64

/* INSTRUCTIONS
    SET <value> <address>
    MOV <from> <to>
    ADD <address 1> <address 2> <output address>
    SEL <address>
    HLT (no params)
*/

typedef enum instructions {
    MOV, // move
    SET, // set
    ADD, // add
    SEL, // select
    HLT, // halt
} instructions;

typedef struct register_ {
    int byte;
} register_;

typedef struct byte_ {
    int byte;
    int address;
} byte_;

typedef struct RAM {
    int program_size;
    byte_ *bytes[RAM_SIZE];
} RAM;

typedef struct vm_ {
    RAM *ram;
    register_ *register_0;
    register_ *register_1;

    register_ *instruction_register;
    register_ *IAR;
} vm_;

vm_ *init_vm();
int load_program(vm_ *vm, int program[], int program_size);
int ram_dump(vm_ *vm, int hex);
int clear_ram(vm_ *vm);
int delete_vm(vm_ *vm);

int execute(vm_ *vm);

#endif
