#include "vm.h"

int main()
{
    int program[] = {
        SET, 2, 0x03, // Set 0x00 into r0
        SET, 0, 0x5 // Set 0x01 into r1
    };
    int program_size = sizeof(program)/sizeof(program[0]);

    int status;

    vm_ *vm = init_vm();

    status = load_program(vm, program, program_size);
    if (status != 0) {
        printf("could not load program\n");
        return 1;
    }

    // for (int i = 0; i < 1; i++) {
    //     printf("%d\n", vm->ram->bytes[1]->address);
    // }

    ram_dump(vm);

    // status = execute(vm);
    // if (status != 0) {
    //     printf("error executing program\n")
    //     return 1;
    // }
    //
    // printf("program executed\n")

    return 0;
}
