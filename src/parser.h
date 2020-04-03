#ifndef PARSER_H
#define PARSER_H

// read_file_return allows for both a buffer and the length of that buffer
// to be returned by the read_file method.
typedef struct read_file_return {
    char *buffer;
    long length;
} read_file_return;

// tokenize_return allows for tokens and the amount of tokens to be returned
// via a single call to the tokenize() method.
typedef struct parsed_file {
    int *program;
    int size;
} parsed_file;

parsed_file parse(char *input_file);

#endif
