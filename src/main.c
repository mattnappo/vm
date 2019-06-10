#include "vm.h"

int main()
{
    int program[] = {
        SET, 200, 30,
        SET, 30, 30,
        SET, 123234564, 61,
        MOV, 61, 58,
        MOV, 20, 55,
        SET, 10, 40,
        SET, 10, 41,
        ADD, 40, 41, 42,
        HLT
    };
    int program_size = sizeof(program)/sizeof(program[0]);
    printf("program size: %d\n", program_size);

    int status;

    vm_ *vm = init_vm();

    status = load_program(vm, program, program_size);
    if (status != 0) {
        printf("could not load program\n");
        return 1;
    }

    ram_dump(vm, 0);

    status = execute(vm);
    if (status < 0) {
        printf("error executing program\n");
        return 1;
    }

    ram_dump(vm, 0);

    printf("program executed\n");

    delete_vm(vm);

    return 0;
}
