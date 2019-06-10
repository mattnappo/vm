#include "vm.h"
#include "parser.h"

int proram()
{
    int program[] = {};
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

int main()
{
    int *program = parse("input.prgm");

    return 0;
}
