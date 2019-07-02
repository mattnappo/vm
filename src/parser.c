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

tokenize_return tokenize(char *input_file)
{
    char **symbols = malloc(sizeof(char) * INSTRUCTION_LIMIT * TOKEN_SIZE);
    read_file_return file = read_file(input_file);

    int token_count = 0;
    char *delimiters = " \n";

    char *token = strtok(file.buffer, delimiters);
    symbols[token_count] = token;
    token_count = 1;
    while (token != NULL) {
        token = strtok(NULL, delimiters);
        symbols[token_count] = token;
        token_count++;
    }

    token_count--;
    // for (int i = 0; i < token_count; i++) {
    //     printf("%s\n", symbols[i]);
    // }
    
    tokenize_return tokenized = {
        symbols,
        token_count
    };
    return tokenized;
}

int *parse(char *input_file)
{
    tokenize_return tokens_raw = tokenize(input_file);
    
    int *parsed = malloc(sizeof(int) * INSTRUCTION_LIMIT);

    for (int i = 0; i < tokens_raw.token_count; i++) {
        char *token = tokens_raw.tokens[i];

        // printf("{TOKEN} --%s--\n", token);
        if (strcmp(token, "MOV") == 0) {
            printf("is mov\n");
            parsed[i] = 0;
            continue;
        } else if (strcmp(token, "SET") == 0 ) {
            printf("is set\n");
            parsed[i] = 1;
            continue;
        } else if (strcmp(token, "ADD") == 0 ) {
            printf("is add\n");
            parsed[i] = 2;
            continue;
        } else if (strcmp(token, "HLT") == 0 ) {
            printf("is hlt\n");
            parsed[i] = 3;
            continue;
        } else {
            char *ptr;
            int int_ = strtol(token, &ptr, 10);
            // printf("[int_] %d\n", int_);
            // printf("String part is |%s|", ptr);

            parsed[i] = int_;
        }
    }
    
    for (int i = 0; i < tokens_raw.token_count; i++) {
        printf("[int_ token] %d\n", parsed[i]);
    }
    return parsed;
}