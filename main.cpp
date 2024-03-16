#include <iostream>
#include "alloc.h"

int main() {
    for (int i = 1; i <= 100000; i++) {
        if (i % 128 != 0) {
            MyTinySTL::alloc::allocate(i % 128 * sizeof(int));
        }
    }
    system("pause");
    return 0;
}