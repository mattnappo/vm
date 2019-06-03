#include "vm.h"

int main()
{
    int program[] = {
        SET, 0, 3,
        SET, 0, 2
    };
    int program_size = sizeof(program)/sizeof(program[0]);

    int status;

    vm_ *vm = init_vm();

    status = load_program(vm, program, program_size);
    if (status != 0) {
        printf("could not load program\n");
        return 1;
    }

    ram_dump(vm);

    // status = execute(vm);
    if (status != 0) {
        printf("error executing program\n");
        return 1;
    }

    printf("program executed\n");

    return 0;
}
