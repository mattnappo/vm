#include "vm.h"

int main()
{
    int program[] = {
        SET, 0x00, 0x00, // Set 0x00 into r0
        SET, 0x01, 0x01 // Set 0x01 into r1
    };

    int status;

    vm_ *vm = init_vm();

    vm->register_0->byte = 0x10;

    // status = load_program(vm, program);
    // if (status != 0) {
    //     printf("could not load program\n")
    //     return 1;
    // }
    //
    // status = execute(vm);
    // if (status != 0) {
    //     printf("error executing program\n")
    //     return 1;
    // }
    //
    // printf("program executed\n")

    return 0;
}
