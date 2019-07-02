#ifndef PARSER_H
#define PARSER_H

typedef struct read_file_return {
    char *buffer;
    long length;
} read_file_return;

typedef struct tokenize_return {
    char **tokens;
    unsigned int token_count;
} tokenize_return;

typedef struct parsed_file {
    int *program;
    int size;
} parsed_file;

parsed_file parse(char *input_file);

#endif