#include "vm.h"

vm_ *init_vm() {
    return (vm_ *)malloc(sizeof(vm_));
}

int eval() {

}

int execute(vm_ *vm, int program[]) {
    int halt = 0;
    while (halt) {
        printf("asd");
    }
    for (int i = 0x0; i < (sizeof(program)/sizeof(program[0])); i++) {
        byte_ instruction_register = vm->instruction_register->byte;

    }

    return 0;
}
