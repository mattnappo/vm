#include "vm.h"
#include "parser.h"

// execute_file is the highest level of abstraction in the entire program.
// It calls all the lower level abstractions to piece the entire program
// together. 
int execute_file(char *file_name)
{
	// Call the parse() abstraction method to parse the file at the given path
    parsed_file raw_program = parse(file_name);

	// Extract the program and the size of the program from the parse() call
    int *program = raw_program.program;
    int program_size = raw_program.size;
    printf("program size: %d\n", program_size);

    int status; // Initialize the status of the virtual machine

	// Call the init_vm() abstraction method to initialize the virtual machine
    vm_ *vm = init_vm();

	// Load the program into the virtual machine
    status = load_program(vm, program, program_size);
    if (status != 0) { // Check that the load was successful
        printf("could not load program\n");
        return 1;
    }

	// Print the current memory (ram) of the virtual machine as hexadecimal
	// The memory at the current state of the virtual machine at this point
	// should contain only the bytes of the program that was just loaded
	// into the virtual machine.
    ram_dump(vm, HEX);

	// Call the execute() abstraction method, which executes the program
	// loaded into the virtual machine.
    status = execute(vm);
    if (status < 0) { // Check that the execution was successful
        printf("error executing program\n");
        return 1;
    }

	// Print the current state of the virtual machine's memory (again).
    ram_dump(vm, HEX);
    printf("program executed\n");
	delete_vm(vm); // Free the memory allocated by the virtual machine

    return 0;
}

// main is the entrypoint into the program.
int main()
{
	// Call the execute_file() abstraction method, executing the program
	// located at the path "./input.prgm"
    int status = execute_file("input.prgm");
    printf("\n-- PRGM STATUS: %d --\n", status); // Print the status of the execun
    return 0;
}
