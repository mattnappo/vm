#include "vm.h"

vm_ *init_vm()
{
    vm_ *vm = (vm_ *)malloc(sizeof(vm_));
    vm->ram = (RAM *)malloc(sizeof(RAM *));

    RAM *ram = vm->ram;

    for (int i = 0; i < RAM_SIZE; i++) {
        ram->bytes[i] = (byte_ *)malloc(sizeof(byte_ *));   
        ram->bytes[i]->address = i;
    }

    vm->register_0 = (register_ *)malloc(sizeof(register_ *));
    vm->register_1 = (register_ *)malloc(sizeof(register_ *));

    return vm;
}

int load_program(vm_ *vm, int program[])
{
    RAM *ram = vm->ram;
    for (int i = 0; i < (sizeof(*program)/sizeof(program[0])); i++) {
        byte_ *byte = (byte_ *)malloc(sizeof(byte_ *));

        byte->byte = program[i];
        byte->address = i;

        ram->bytes[i] = byte;
    }

    return 0;
}

int ram_dump(vm_ *vm)
{
    RAM *ram = vm->ram;
    for (int i = 0; i < (sizeof(*ram->bytes)/sizeof(ram->bytes[0])); i++) {
        byte_ *byte = ram->bytes[i];
        
        printf("[0x%d] %d", byte->address, byte->byte);
    }
    return 0;
}

int eval(vm_ *vm)
{
    RAM *ram = vm->ram;
    // int instruction_address_register = vm->instruction_address_register;
    // int instruction = ram->bytes[instruction_address_register];
    int instruction = 0;

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
