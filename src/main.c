#include "vm.h"

int main() {
    int program[] = {
        SET, 0x00, 0x00, // Set 0x00 into r0
        SET, 0x01, 0x01 // Set 0x01 into r1

    };

    vm_ *vm = init_vm();
    execute(vm, program);

    // execute(program);

    return 0;
}
