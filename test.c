#include <stdlib.h>
#include <stdio.h>

void test(int program[]) {
    printf("%lu\n", sizeof(program));
}

int main() {

    int program[] = {
        1, 2, 0x03, // Set 0x00 into r0
        0, 0, 0x5 // Set 0x01 into r1
    };

    printf("%lu\n", sizeof(program));

    test(program);

    return 0;
}
