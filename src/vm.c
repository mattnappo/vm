#include "vm.h"

vm_ *init_vm()
{
    return (vm_ *)malloc(sizeof(vm_));
}

int load_program(vm_ *vm, int program[])
{
    RAM *ram = vm->ram;
    for (int i = 0; i < (sizeof(program)/sizeof(program[0])); i++) {
        ram->bytes[i] = program[i];
    }

    return 0;
}

int ram_dump(vm_ *vm)
{
    RAM *ram_bytes = vm->ram->bytes;
    for (int i = 0; i < (sizeof(ram_bytes)/sizeof(ram_bytes[0])); i++) {
        printf("[0x%x] %d", i, ram_bytes[i]);
    }
}

int eval(vm_ *vm)
{
    RAM *ram = vm->ram;
    int instruction_address_register = vm->instruction_address_register;
    int instruction = ram->bytes[instruction_address_register];

    switch (instruction) {
    case MOV:
        break;
    case SET:
        break;
    case ADD:
        break;
    case HLT:
        return 1;
    default:
        return 1;
    }

    return 0;
}

int execute(vm_ *vm)
{
    int halt = 0;

    while (!halt) {
        int status = eval(vm);
        if (status == 0) {
            return 0;
        }
        else {
            return 1;
        }



    }

    return 0;
}
