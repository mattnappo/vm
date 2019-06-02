#ifndef VM_H
#define VM_H

typedef enum instructions {
    MOV,
    AND,
    ADD,
    SET
} instructions;

typedef struct register {
    char _byte   [4];
    char _address[8];
} register;

#endif
