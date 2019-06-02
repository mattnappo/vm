#include "vm.h"

vm_ *init_vm()
{
    return (vm_ *)malloc(sizeof(vm_));
}

int eval(vm_ *vm)
{
    switch instruction {
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

    register_ *instruction_register = vm->instruction_register;
    RAM *ram = vm->ram;
    instruction_register->byte = ram[instruction_register++]
    return 0;
}

int execute(vm_ *vm, int program[])
{
    int halt = 0;

    while (!halt) {
        int stop_code = eval(vm);
        if (stop_code == 0) {
            return 0;
        }
        else {
            return 1;
        }
    }

    return 0;
}
