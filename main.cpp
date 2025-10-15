#include "libezsimd3.hpp"
#include <vector>
#include <array>
#include <iostream>

using namespace std;

int main() {
    int32_t a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int32_t b[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int32_t c[10];
    ezsimd3::ADD(a, b, c);

    for (auto i : c) {
        cout << +i << "\n";
    }

    return 0;
}