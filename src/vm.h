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

// instruction represents an instruction (really just an abstracted integer).
typedef enum instruction {
    MOV, // move the value at one address to another address
    SET, // set the value of the byte at an address
    ADD, // add the values of two addresses and store it in another address
    HLT, // halt the program
} instruction;

// display_type allows for switching between hexidecimal and decimal RAM dumps.
typedef enum display_type {
	HEX, // Hexidecimal printing
	DECIMAL, // Decimal printing
} display_type;

// register_ represents a register within the virtual machine.
typedef struct register_ {
    int byte;
} register_;

// byte_ represents an addressed byte.
typedef struct byte_ {
    int byte;
    int address;
} byte_;

// RAM represents a block of random-access memory.
typedef struct RAM {
    int program_size;
    byte_ *bytes[RAM_SIZE];
} RAM;

// vm_ represents a virtual machine.
typedef struct vm_ {
    RAM *ram; // The random access memory of the virtual machine

	register_ *instruction_register; // the instruction register
    register_ *IAR; // The instruction address register
} vm_;

vm_ *init_vm();
int load_program(vm_ *vm, int program[], int program_size);
int ram_dump(vm_ *vm, display_type hex);
int clear_ram(vm_ *vm);
int delete_vm(vm_ *vm);

int execute(vm_ *vm);

#endif
