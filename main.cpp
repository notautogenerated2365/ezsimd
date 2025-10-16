#include <iostream>
#include <array>
#include <vector>

/*#ifdef __MMX__
    #undef __MMX__
#endif
#ifdef __SSE__
    #undef __SSE__
#endif
#ifdef __SSE2__
    #undef __SSE2__
#endif
#ifdef __AVX__
    #undef __AVX__
#endif
#ifdef __AVX2__
    #undef __AVX2__
#endif*/

#define EZSIMD_SHOW_FUNC std::clog
#include "../ezsimd3/ezsimd.hpp"

#include "../h/ez.hpp"

using namespace std;

int main() {
    constexpr size_t SIZE = 10000;
    array<int32_t, SIZE> a;
    array<int32_t, SIZE> b;
    array<int32_t, SIZE> c_n;
    array<int32_t, SIZE> c_es;

    for (size_t i = 0; i < SIZE; i++) {
        a[i] = i;
        b[i] = SIZE - i;
    }

    double es = bench([&a, &b, &c_es, SIZE]() {
        ezsimd::add<SIZE>(a, b, c_es);
    });

    double n = bench([&a, &b, &c_n, SIZE]() {
        for (size_t i = 0; i < SIZE; i++) {
            c_n[i] = a[i] + b[i];
        }
    });

    cout << es << '\n' << n << '\n';

    int inequalCount = 0;
    for (size_t i = 0; i < SIZE; i++) {
        if (c_es[i] != c_n[i]) {
            cerr << "inequal: " << i << " (es: " << c_es[i] << ", n: " << c_n[i] << ")\n";
            inequalCount++;

            if ((SIZE >= 100) && (inequalCount >= 100)) {
                cerr << "inequal overflow\n";
                return 1;
            }
        }
    }
    
    if (inequalCount > 0) return 1;
    return 0;
}