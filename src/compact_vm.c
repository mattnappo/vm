#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Information
 *
 * This code was entirely designed, implemented, and tested by
 * Matthew Nappo for the AP Computer Science Principles Create Task 2020.
 * There is only one small method that was not written by me, and it is
 * correctly credited in a comment above the declaraction of the method.
 * Other than that method (and the C standard library, of course), every single
 * line of code was written by me, Matthew Nappo.
 *
 * The code is separated into three main sections delimited by dashes.
 * Traditionally, these three sections of the code would be separated into
 * multiple header files and implementation files in order to add another layer
 * of abstraction. However, due to the format of AP CSP submissions, I was
 * forced to put all of the code into one single source file in order for it
 * to render well as a PDF.
 *
*/

/* ---------- BEGIN PARSER CODE ---------- */

#define TOKEN_SIZE 8
#define INSTRUCTION_LIMIT 100

// read_file_return allows for both a buffer and the length of that buffer
// to be returned by the read_file method.
typedef struct read_file_return {
    char *buffer;
    long length;
} read_file_return;

// tokenize_return allows for tokens and the amount of tokens to be returned
// via a single call to the tokenize() method.
typedef struct tokenize_return {
    char **tokens;
    unsigned int token_count;
} tokenize_return;

// parsed_file represents a parsed file, containing a program and its size,
// ready to be executed by the virtual machine.
typedef struct parsed_file {
    int *program;
    int size;
} parsed_file;

// read_file reads a file as a char* from the disk given the filepath.
read_file_return read_file(char *input_file)
{
    /* THE IMPLEMENTATION OF THIS FUNCTION WAS WRITTEN BY @Nils Pipenbrinck.
     * He can be reached at
	 * https://stackoverflow.com/users/15955/nils-pipenbrinck
    */

    char *buffer = 0;
    long length;
    FILE *file = fopen(input_file, "rb");

    if (file) {
        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer) {
            fread(buffer, 1, length, file);
        }
        fclose(file);
    }

    if (buffer) {
        read_file_return returns = {
            buffer,
            length
        };
        return returns;
    }

    read_file_return returns = {
        "error reading file",
        0
    };
    return returns;
}

// tokenize returns each token (an instruction or argument to instruction) given
// the path of the input file.
tokenize_return tokenize(char *input_file)
{
    // Prepare the char** of symbols
    char **symbols = malloc(sizeof(char) * INSTRUCTION_LIMIT * TOKEN_SIZE);
    
    // Call the read_file() abstraction method to read the file as a string
    // given the path.
    read_file_return file = read_file(input_file);

    int token_count = 0;
    char *delimiters = " \n";

    // Read the current token
    char *token = strtok(file.buffer, delimiters);
    symbols[token_count] = token; // Appent the token to the array of tokens
    token_count = 1;
    while (token != NULL) { // Repeat this step for all tokens in the file
        token = strtok(NULL, delimiters);
        symbols[token_count] = token;
        token_count++;
    }

    // Return the tokens and the amount of tokens
    token_count--;
    tokenize_return tokenized = {
        symbols,
        token_count
    };
    return tokenized;
}

// parse is the main abstraction method used for parsing a file. It is a
// very nice abstraction because it only requires a filepath and returns
// a program ready for the virtual machine to process.
parsed_file parse(char *input_file)
{
    // Parse the input file and get its tokens
    tokenize_return tokens_raw = tokenize(input_file);
    int *parsed = malloc(sizeof(int) * INSTRUCTION_LIMIT);

    // Convert the tokens into integers
    for (int i = 0; i < tokens_raw.token_count; i++) {
        char *token = tokens_raw.tokens[i];

        if (strcmp(token, "MOV") == 0) {
            parsed[i] = 0;
        } else if (strcmp(token, "SET") == 0 ) {
            parsed[i] = 1;
        } else if (strcmp(token, "ADD") == 0 ) {
            parsed[i] = 2;
        } else if (strcmp(token, "HLT") == 0 ) {
            parsed[i] = 3;
        } else {
            char *ptr;
            int int_ = strtol(token, &ptr, 10);
            parsed[i] = int_;
        }
    }

    // Return the program and amount of bytes it requires
    parsed_file program = {
        parsed,
        tokens_raw.token_count
    };
    return program;
}

/* ---------- END PARSER CODE ---------- */


/* -------- BEGIN CORE VIRTUAL MACHINE CODE ---------- */

#define RAM_SIZE 60

/* INSTRUCTIONS
    SET <value> <address>
    MOV <from> <to>
    ADD <address 1> <address 2> <output address>
    SEL <address>
    HLT (no params)
*/

// instruction represents an instruction (just an abstracted integer).
typedef enum instruction {
    MOV, // move the value at one address to another address
    SET, // set the value of the byte at an address
    ADD, // add the values of two addresses and store it in another address
    HLT, // halt the program
} instruction;

// display_type allows for switching between hexidecimal and decimal RAM dumps.
typedef enum display_type {
    HEX, // Hexidecimal printing
    DECIMAL, // Decimal printing
} display_type;

// register_ represents a register within the virtual machine.
typedef struct register_ {
    int byte;
} register_;

// byte_ represents an addressed byte.
typedef struct byte_ {
    int byte;
    int address;
} byte_;

// RAM represents a block of random access memory.
typedef struct RAM {
    int program_size;
    byte_ *bytes[RAM_SIZE];
} RAM;

// vm_ represents a virtual machine.
typedef struct vm_ {
    RAM *ram; // The random access memory of the virtual machine

    register_ *instruction_register; // The instruction register
    register_ *IAR; // The instruction address register
} vm_;

// init_vm initializes a new, blank virtual machine and returns a pointer
// to that virtual machine.
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

        // Set the current byte in the VM's RAM to the newly-made byte
        vm->ram->bytes[i] = byte;
    }

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
    RAM *ram = vm->ram; // Access the virtual machine's ram
    ram->program_size = program_size; // Set the size of the program in the RAM.

    // Set the RAM of the virtual machine to the bytes of the input program.
    // This is done byte-by-byte in order to be verbose and safe.
    for (int i = 0; i < ram->program_size; i++) {
        ram->bytes[i]->byte = program[i];
    }

    return 0;
}

// ram_dump_no_addrs prints the ram of a virtual machine without displaying the
// addresses of each byte. This makes the RAM much easier to read.
int ram_dump_no_addrs(vm_ *vm, display_type type)
{
	RAM *mem = vm->ram; // Access the RAM of the virtual machine
	printf("\n=== START RAM DUMP ===\n");
	for (int i = 0; i < RAM_SIZE; i++) {
        // Print the byte as either hexidecimal or decimal
        if (mem->bytes[i]->byte == 0) {
            printf("%s", (type == HEX) ? "00 " : " ");
        }
	    else if (type == HEX) {
            printf("%x ", mem->bytes[i]->byte);
        }
        else if (type == DECIMAL) {
            printf("%c", mem->bytes[i]->byte);
        }
    }
    printf("\n=== END RAM DUMP ===\n");
    return 0;
}

// ram_dump prints the RAM of a virtual machine in either hexadecimal or decimal.
int ram_dump(vm_ *vm, display_type type)
{
    RAM *ram = vm->ram; // Access the RAM of the virtual machine
    printf("\n=== START RAM DUMP ===\n");
	printf("[ADDRESS] VALUE\n");
	printf("---------------\n");
    // For each byte in the RAM (which is an array), print that byte in either
    // decimal or hexidecimal format
    for (int i = 0; i < RAM_SIZE; i++) {
        byte_ *byte = ram->bytes[i]; // Get the current byte
        if (type == HEX) {
            printf("[0x%08x] 0x%08x\n", byte->address, byte->byte);
        }
        else if (type == DECIMAL) {
            printf("[%08d] %08d\n", byte->address, byte->byte);

        }
    }

    printf("\n=== END RAM DUMP ===\n");
    return 0;
}

// clear_ram clears the RAM of the virtual machine by setting each byte in
// the RAM equal to 0. clear_ram also reallocates the RAM memory.
int clear_ram(vm_ *vm)
{
    // For each byte in the ram, reallocate that byte and set it equal to 0.
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
    case ADD: // Algorithm/implementation of the ADD instruction
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

// execute executes the current program loaded into a virtual machine's RAM and
// returns the status of the virtual machine.
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
    free(vm);

    return 0;
}

/* -------- END CORE VIRTUAL MACHINE CODE ---------- */


/* ---------- BEGIN MAIN FUNCTIONALITY ---------- */

// execute_file is the highest level of abstraction in the entire program.
// It calls all the lower level abstractions to piece the entire program
// together and fully execute the entire lifecycle of the virtual machine
// implemented in this program.
int execute_file(char *file_name)
{
    // Call the parse() abstraction method to parse the file at the given path
    parsed_file raw_program = parse(file_name);

    // Extract the program and the size of the program from the parse() call
    int *program = raw_program.program;
    int program_size = raw_program.size;

    int status; // Initialize the status of the virtual machine

    // Call the init_vm() abstraction method to initialize the virtual machine
    vm_ *vm = init_vm();

	printf("\nvirtual machine memory before program load:\n");
	// Print the current memory of the VM (should be all blank)
	ram_dump(vm, DECIMAL);

    // Load the program into the virtual machine using the load_program()
	// abstraction method
    status = load_program(vm, program, program_size);
    if (status != 0) { // Check that the load was successful
        printf("could not load program\n");
        return -1;
    }

	printf("\nvirtual machine memory after program load:\n");
    // Print the current memory (ram) of the virtual machine as hexadecimal
    // The memory at the current state of the virtual machine at this point
    // should contain only the bytes of the program that was just loaded
    // into the virtual machine.
    ram_dump(vm, DECIMAL);

    // Call the execute() abstraction method, which executes the program
    // loaded into the virtual machine.
    status = execute(vm);
    if (status < 0) { // Check that the execution was successful
        printf("error executing program\n");
        return -1;
    }

	printf("\nvirtual machine memory after program execution:\n");
    // Print the current state of the virtual machine's memory (again).
    ram_dump(vm, DECIMAL);
    printf("program executed\n");
    
	// Call the delete_vm() abstraction method to free the memory allocated
	// by the virtual machine and its components
	delete_vm(vm);

    return 0;
}

// main is the entrypoint into the program.
int main(int argc, char **args)
{
    if (argc != 2) {
		printf("please supply input program path\n");
		return -1;
	}
    // Call the execute_file() abstraction method, executing the program
    // located at the path "./input.prgm"
    int status = execute_file(args[1]);

    printf("\n-- PRGM STATUS: %d --\n", status); // Print the status of the execun
    
	return 0;
}

/* ---------- END MAIN FUNCTIONALITY ---------- */

