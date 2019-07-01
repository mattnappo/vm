#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

#define TOKEN_SIZE 8
#define INSTRUCTION_LIMIT 100

read_file_return read_file(char *input_file)
{
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

int *parse(char *input_file)
{
    char **symbols = malloc(sizeof(char) * INSTRUCTION_LIMIT * TOKEN_SIZE);
    read_file_return file = read_file(input_file);
    printf("-- START FILE READ --\n%s\n-- END FILE READ\n", file.buffer);

    int token_count = 0;
    char *delimiters = " ";

    char *token = strtok(file.buffer, delimiters);
    symbols[token_count] = token;

    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, delimiters);
        symbols[token_count] = token;
        token_count++;
    }
    
    int *base;
    return base;
}
