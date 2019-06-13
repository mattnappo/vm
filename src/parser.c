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
    read_file_return raw_file = read_file(input_file);
    char *file = raw_file.buffer;

    char **parsed = malloc(sizeof(char) * INSTRUCTION_LIMIT * TOKEN_SIZE);

    char *token;
    char *delim = " \n";
    token = strtok(file, delim);
    parsed[0] = token;
    
    int instruction_count = 1;
    printf("\"%s\"\n", token);
    while (token != NULL) {
        printf("\"%s\"\n", token);
        token = strtok(NULL, delim);
        parsed[instruction_count] = token;
        instruction_count++;
        
        printf("[%d] this is running\n", instruction_count);
    }
    printf("DONE\n");

    // for (int i = 0; i < INSTRUCTION_LIMIT; i++) {
    //     // if (strcmp(parsed[i], NULL)) {
    //     //     printf("shit happens\n");
    //     //     break;
    //     // }
    //     if (parsed[i] == "\0") {
    //         printf("shit happened\n\n");
    //         break;
    //     }
    //     printf("'%s'\n", parsed[i]);
    // }
    // printf("we good\n");

    char instruction_tokens[4][3] = {
        "MOV",
        "SET",
        "ADD",
        "HLT",
    };
    printf("%s\n", instruction_tokens[2]);
    
    int *instructions = malloc(sizeof(int) * sizeof(instruction_count));
    for (int i = 0; i < instruction_count; i++) {
        for (int j = 0; j < sizeof(instruction_tokens) / sizeof(instruction_tokens[0]); j++) {
            // printf("%s\r\n\r\n", instruction_tokens[2]);
            // printf("\r\n\r\n");
            // if (strcmp(parsed[i], instruction_tokens[j])) {
    //             // instructions[i] = j;
            // }
        }

    //     // instructions[i] = atoi(parsed[i]);
    }
    
    return 0;
}