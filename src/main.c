#include "vm.h"
#include "parser.h"

int execute_file(char *file_name)
{
    parsed_file raw_program = parse(file_name);

    int *program = raw_program.program;
    int program_size = raw_program.size;
    printf("program size: %d\n", program_size);

    int status;

    vm_ *vm = init_vm();

    status = load_program(vm, program, program_size);
    if (status != 0) {
        printf("could not load program\n");
        return 1;
    }

    ram_dump(vm, 1);

    status = execute(vm);
    if (status < 0) {
        printf("error executing program\n");
        return 1;
    }

    ram_dump(vm, 1);
    printf("program executed\n");
    delete_vm(vm);

    return 0;
}

int main()
{
    int status = execute_file("input.prgm");
    printf("\n-- PRGM STATUS: %d --\n", status);
    return 0;
}