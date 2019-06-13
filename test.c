#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    if (0) printf("0 works\n");
    if (1) printf("1 works\n");
    
    printf("[`8` == `8`] %d\n", strcmp("8", "8"));
    printf("[`8` == `5`] %d\n", strcmp("8", "5"));

    return 0;
}