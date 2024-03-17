#include <iostream>
#include "allocator.h"
#include "uninitialized.h"

int main() {
    // for (int i = 1; i <= 100000; i++) {
    //     if (i % 128 != 0) {
    //         MyTinySTL::allocator<int>::allocate(i % 128 * sizeof(int));
    //     }
    // }

    auto p = MyTinySTL::allocator<int>::allocate(30);
    auto last = p + 30;
    MyTinySTL::uninitialized_fill(p, last, 666);
    for (; p != last; ++p) {
        std::cout << *p << " ";
    }
    std::cout << std::endl;

    int array[30];
    MyTinySTL::uninitialized_fill_n(array, 30, 999);
    for (auto n : array) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    return 0;
}