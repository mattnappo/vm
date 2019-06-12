#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

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
    // split every space and line break
    // remove all extra spaces and line breaks
    // swap out the ADDs and SETs for 1s and 0s ...
    char *file = read_file(input_file).buffer;

    char *parsed;
    int counter = 0;
    char *delim = "\n";
    parsed = strtok(file, delim);
    while (parsed != NULL) {
        printf("-- COUNT: %d --\n", counter);
        printf("\"%s\"\n", parsed);
        parsed = strtok(NULL, delim);
        counter++;
    }
}