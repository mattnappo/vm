#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TOKEN_SIZE 8
#define INSTRUCTION_LIMIT 100

// read_file_return allows for both a buffer and the length of that buffer
// to be returned by the read_file method.
typedef struct read_file_return {
    char *buffer;
    long length;
} read_file_return;

// tokenize_return allows for tokens and the amount of tokens to be returned
// via a single call to the tokenize() method./ token
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

parsed_file parse(char *input_file);

#endif
