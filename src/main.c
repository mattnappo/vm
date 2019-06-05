#include "vm.h"

int main()
{

    vm_ *vm = init_vm();
    
    // int program[] = {
    //     SET, 0, 3,
    //     SET, 0, 2
    // };
    // int program_size = sizeof(program)/sizeof(program[0]);

    // int status;

    // vm_ *vm = init_vm();

    // // status = load_program(vm, program, program_size);
    // if (status != 0) {
    //     printf("could not load program\n");
    //     return 1;
    // }

    // // printf("byte_* size: %lu\n", sizeof(byte_ *));

    // // int address = 0;
    // // printf("[%d] %d\n", vm->ram->bytes[address]->address, vm->ram->bytes[address]->byte);


    // ram_dump(vm);

    // // status = execute(vm);
    // if (status != 0) {
    //     printf("error executing program\n");
    //     return 1;
    // }

    // printf("program executed\n");

    return 0;
}
