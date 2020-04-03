#include "vm.h"

// init_vm initializes a new, blank virtual machine. It returns a pointer to
// a new virtual machine.
vm_ *init_vm()
{
	// Allocate the needed memory for the virtual machine
    vm_ *vm = malloc(sizeof(vm_));

	// Allocate the needed memory for the RAM of the virtual machine
    vm->ram = malloc(sizeof(RAM));

	// Construct the RAM, which is a pointer to an array of byte_ structs. 
    for (int i = 0; i < RAM_SIZE; i++) {
		// Allocate the memory needed for the byte
        byte_ *byte = malloc(sizeof(*byte));
        byte->address = i; // Set the address of the byte
        byte->byte = 0; // Set the byte equal to 0, just to be safe

        vm->ram->bytes[i] = byte; // Set the byte in the VM's RAM to the newly-made byte
    }

    vm->register_0 = malloc(sizeof(register_));
    vm->register_1 = malloc(sizeof(register_));

	// Initialize the necessary registers in the virtual machine
    vm->IAR = malloc(sizeof(register_));
    vm->instruction_register = malloc(sizeof(register_));

    return vm;
}

// load_program loads a program into a virtual machine given the virtual machine
// to load into (vm), the program itself (program), and the size of the program
// (program_size).
int load_program(vm_ *vm, int program[], int program_size)
{
    RAM *ram = vm->ram;	// Access the virtual machine's ram
    ram->program_size = program_size; // Set the size of the program in the RAM.

	// Set the RAM of the virtual machine to the bytes of the input program.
	// This is done byte-by-byte in order to be verbose and safe.
    for (int i = 0; i < ram->program_size; i++) {
        ram->bytes[i]->byte = program[i];
    }

    return 0;
}

// ram_dump prints the ram of a virtual machine in either hexadecimal or decimal.
int ram_dump(vm_ *vm, int hex)
{
    RAM *ram = vm->ram; // Access the RAM of the virtual machine
    printf("-- START RAM DUMP --\n");

	// For each byte in the RAM (which is an array), print that byte in either
	// decimal or hexidecimal format
    for (int i = 0; i < RAM_SIZE; i++) {
        byte_ *byte = ram->bytes[i]; // Get the current byte
        if (hex) {
            printf("[0x%x] 0x%x\n", byte->address, byte->byte);
        }
        else {
            printf("[%d] %d\n", byte->address, byte->byte);

        }
    }

    printf("-- END RAM DUMP --\n");
    return 0;
}

// clear_ram clears the RAM of the virtual machine by setting each byte in
// the RAM equal to 0. clear_ram also reallocates the RAM memory.
int clear_ram(vm_ *vm)
{
    for (int i = 0; i < RAM_SIZE; i++) {
        byte_ *byte = malloc(sizeof(*byte));
        byte->byte = 0;

        vm->ram->bytes[i] = byte;
    }

    return 0;
}

// eval is the core of the entire virtual machine. This is the method that
// actually executes the instructions that make up a program.
int eval(vm_ *vm)
{
	// Load the current instruction from the RAM of the VM.
    int current_instruction = vm->ram->bytes[vm->IAR->byte]->byte;

	// Load the current instruction in to the instruction register of the
	// virtual machine.
	vm->instruction_register->byte = current_instruction;

	// Execute the necessary logical operations for the current instruction
    switch (vm->instruction_register->byte) {
    case MOV: // Algorithm/implementation of the MOV (move) instruction
        vm->IAR->byte++;
        int address_1 = vm->ram->bytes[vm->IAR->byte]->byte; // From addr
        vm->IAR->byte++;
        int address_2 = vm->ram->bytes[vm->IAR->byte]->byte; // To addr

        if (address_2 < vm->ram->program_size) {
            printf("MOV: address %d is not accessible\n", address_2);
            return -1;
        }

        vm->ram->bytes[address_2]->byte = vm->ram->bytes[address_1]->byte;
        break;
    case SET: // Algorithm/implementation of the SET instruction
        vm->IAR->byte++;
        int byte = vm->ram->bytes[vm->IAR->byte]->byte;

        vm->IAR->byte++;
        int address = vm->ram->bytes[vm->IAR->byte]->byte;
        
        if (address < vm->ram->program_size) {
            printf("SET: address %d is not accessible\n", address);
            return -1;
        }

        byte_ *new_byte = malloc(sizeof(byte_));
        new_byte->address = address;
        new_byte->byte = byte;

        vm->ram->bytes[address] = new_byte;
        break;
    case ADD: // Implementation/algorithm of the ADD instruction
        vm->IAR->byte++;
        int addend_addr_1 = vm->ram->bytes[vm->IAR->byte]->byte;
        vm->IAR->byte++;
        int addend_addr_2 = vm->ram->bytes[vm->IAR->byte]->byte;

        vm->IAR->byte++;
        int output_address = vm->ram->bytes[vm->IAR->byte]->byte;

        if (output_address < vm->ram->program_size) {
            printf("ADD: address %d is not accessible\n", output_address);
            return -1;
        }

        int addend_1 = vm->ram->bytes[addend_addr_1]->byte;
        int addend_2 = vm->ram->bytes[addend_addr_2]->byte;

        vm->ram->bytes[output_address]->byte = (addend_1 + addend_2);

        break;
    case HLT: // Implement the HLT instruction
        return 0;
    default: // Implement an unknown instruction
        return -1;
    }
    
    vm->IAR->byte++;
    return 1;
}

// execute executes the current program loaded into a virtual machine's RAM.
int execute(vm_ *vm)
{
	// Position the instruction address register
    vm->IAR->byte = 0;
    int current_instruction_address = vm->IAR->byte; // Load the current byte

	// Set the current instruction byte equal to the current byte
    vm->instruction_register->byte = vm->ram->bytes
		[current_instruction_address]->byte;
    
    int status = 0;
    
	/* STATUS CODES
        0 = program has terminated with no errors
        1 = everything is fine
        -1 = something went wrong
    */

	// Call each instruction in memory and evaluate it using the eval()
	// abstraction method
    while (1) {
        status = eval(vm); // Call the eval() abstraction method
        if (status != 1) {
            break;
        }
    }
    return status;
}

// delete_vm deletes the virtual machine and frees the memory that it allocated.
int delete_vm(vm_ *vm)
{
	// Free each byte in the RAM
    for (int i = 0; i < RAM_SIZE; i++) {
        free(vm->ram->bytes[i]);
    }

	// Free the RAM and the VM itself.
    free(vm->ram);
    free(vm->register_0);
    free(vm->register_1);
    free(vm);

    return 0;
}
