#include "vm.h"

vm_ *init_vm()
{
    vm_ *vm = malloc(sizeof(vm_));
    vm->ram = malloc(sizeof(RAM *));

    RAM *ram = vm->ram;

    for (int i = 0; i < RAM_SIZE; i++) {
        byte_ byte;
        byte.address = i;
        byte.byte = 0;

        ram->bytes[i] = byte;
    }

    // vm->register_0 = (register_ *)malloc(sizeof(register_ *));
    // vm->register_1 = (register_ *)malloc(sizeof(register_ *));

    return vm;
}

int load_program(vm_ *vm, int program[], int program_size)
{
    RAM *ram = vm->ram;
    ram->ram_size = program_size;

    for (int i = 0; i < ram->ram_size; i++) {
        ram->bytes[i].byte = program[i];
    }

    return 0;
}

int ram_dump(vm_ *vm)
{
    RAM *ram = vm->ram;
    printf("-- START RAM DUMP --\n");

    for (int i = 0; i < RAM_SIZE; i++) {
        byte_ byte = ram->bytes[i];
        printf("[0x%x] 0x%x\n", byte.address, byte.byte);
        // printf("[%d] %d\n", byte.address, byte.byte);
    }

    printf("-- END RAM DUMP --\n");
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
