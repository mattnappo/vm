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

int *parse(char *input_file);

#endif