#include <stdlib.h>
#include <stdio.h>

typedef struct a {
    int thing;
} b;

int main() {

    b test;

    test.thing = 10;
    printf("%d\n", test.thing);



    return 0;
}
