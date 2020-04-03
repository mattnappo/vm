#include "parser.h"

/* ---------- BEGIN PARSER CODE ---------- */

// read_file reads a file as a char* from the disk given the filepath.
read_file_return read_file(char *input_file)
{
	/* THE IMPLEMENTATION OF THIS FUNCTION WAS WRITTEN BY @Nils Pipenbrinck.
	 * He can be reached at https://stackoverflow.com/users/15955/nils-pipenbrinck
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
// and input file.
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

