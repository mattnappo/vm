#ifndef PARSER_H
#define PARSER_H

typedef struct read_file_return {
    char *buffer;
    long length;
} read_file_return;

int *parse(char *input_file);
read_file_return read_file(char *input_file);

#endif