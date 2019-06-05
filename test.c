#include <stdlib.h>
#include <stdio.h>

#define RAM_SIZE 64

typedef struct byte_ {
    int byte;
    int address;
} byte_;

typedef struct RAM {
    int program_size;
    byte_ *bytes[RAM_SIZE];
} RAM;

int main() {

    int program[] = {
        1, 2, 0x03,
        0, 0, 0x5
    };

    // printf("address: %d\n   byte: %d\n", byte->address, byte->byte);

    RAM *ram = malloc(sizeof(*ram));

    for (int i = 0; i < RAM_SIZE; i++) {
        byte_ *byte = malloc(sizeof(*byte));
        byte->byte = 8;
        byte->address = i;
        ram->bytes[i] = byte;
    }

    for (int i = 0; i < RAM_SIZE; i++) {
        printf("byte: %d\n", ram->bytes[i]->byte);
        printf("address: %d\n", ram->bytes[i]->address);
    }
    


    return 0;
}
