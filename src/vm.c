#include "vm.h"

vm_ *init_vm()
{
    vm_ *vm = malloc(sizeof(vm_));
    vm->ram = malloc(sizeof(RAM));
    
    for (int i = 0; i < RAM_SIZE; i++) {
        byte_ *byte = malloc(sizeof(*byte));
        byte->address = i;
        byte->byte = 0;

        vm->ram->bytes[i] = byte;
    }

    vm->register_0 = malloc(sizeof(register_));
    vm->register_1 = malloc(sizeof(register_));

    vm->IAR = malloc(sizeof(register_));
    vm->instruction_register = malloc(sizeof(register_));

    return vm;
}

int load_program(vm_ *vm, int program[], int program_size)
{
    RAM *ram = vm->ram;
    ram->program_size = program_size;

    for (int i = 0; i < ram->program_size; i++) {
        ram->bytes[i]->byte = program[i];
    }

    return 0;
}

int ram_dump(vm_ *vm, int hex)
{
    RAM *ram = vm->ram;
    printf("-- START RAM DUMP --\n");

    for (int i = 0; i < RAM_SIZE; i++) {
        byte_ *byte = ram->bytes[i];
        if (hex) {
            printf("[0x%x] 0x%x\n", byte->address, byte->byte);
        }
        else {
            printf("[%d] %d\n", byte->address, byte->byte);

        }
    }

    printf("-- END RAM DUMP --\n");
    return 0;
}

int clear_ram(vm_ *vm)
{
    for (int i = 0; i < RAM_SIZE; i++) {
        byte_ *byte = malloc(sizeof(*byte));
        byte->byte = 0;

        vm->ram->bytes[i] = byte;
    }

    return 0;
}

int eval(vm_ *vm)
{
    if (vm->IAR->byte > vm->ram->program_size) {
        return 0;
    }

    int current_instruction = vm->ram->bytes[vm->IAR->byte]->byte;
    vm->instruction_register->byte = current_instruction;
    printf("IAR: %d\nIR: %d\n", vm->IAR->byte, vm->instruction_register->byte);

    switch (vm->instruction_register->byte) {
    case MOV:
        vm->IAR->byte++;
        int address_1 = vm->ram->bytes[vm->IAR->byte]->byte;
        printf("address_1: %d\n", address_1);
        vm->IAR->byte++;
        int address_2 = vm->ram->bytes[vm->IAR->byte]->byte;
        printf("address_2: %d\n", address_2);

        vm->ram->bytes[address_2]->byte = vm->ram->bytes[address_1]->byte;
        break;
    case SET:
        vm->IAR->byte++;
        int byte = vm->ram->bytes[vm->IAR->byte]->byte;
        printf("read: %d\n", vm->ram->bytes[vm->IAR->byte]->byte);

        vm->IAR->byte++;
        int address = vm->ram->bytes[vm->IAR->byte]->byte;
        printf("read: %d\n", vm->ram->bytes[vm->IAR->byte]->byte);
        
        if (address < vm->ram->program_size) {
            printf("address: %d\nprogram_size: %d\n", address, vm->ram->program_size);
            printf("that memory is not accessible\n");
            return -1;
        }

        byte_ *new_byte = malloc(sizeof(byte_));
        new_byte->address = address;
        new_byte->byte = byte;

        vm->ram->bytes[address] = new_byte;
        break;
    case ADD:
        break;
    case HLT:
        return 0;
    default:
        return -1;
    }
    
    vm->IAR->byte++;
    return 1;
}

int execute(vm_ *vm)
{
    vm->IAR->byte = 0;
    int current_instruction_address = vm->IAR->byte;

    vm->instruction_register->byte = vm->ram->bytes[current_instruction_address]->byte;
    
    int status = 0;
    /* STATUS CODES
        0 = program has terminated
        1 = everything is fine
        -1 = something went wrong
    */
    // status = eval(vm);
    // status = eval(vm);
    // status = eval(vm);
    // status = eval(vm);
    // status = eval(vm);
    

    while (1) {
        status = eval(vm);
        if (status != 1) {
            break;
        }
    }
    printf("%d\n\n", status);
    return status;
}

int delete_vm(vm_ *vm)
{
    for (int i = 0; i < RAM_SIZE; i++) {
        free(vm->ram->bytes[i]);
    }

    free(vm->ram);
    free(vm->register_0);
    free(vm->register_1);
    free(vm);

    return 0;
}