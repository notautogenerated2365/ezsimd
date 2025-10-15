A library/header for simplifying SIMD operations on vectors in C++.
Also my first ever GitHub project, I don't really know how any of this works

/
+-- make/           contains program I used to make the ezsimd source and header files
    +-- make.cpp    the program
    +-- enums.hpp   enum definitions for organizing data
    +-- maps.hpp    maps defining SIMD/operation/number type support among other important thing
    +-- makefile    will compile and run the program to produce the three files below
+-- ezsimd.cpp      can be compiled into a static or shared library
+-- libezsimd.hpp   can be included into a project that uses the static or shared library
+-- ezsimd.hpp      can be included into a project without using static or shared library

This library defines functions for addition, subtraction, multiplication, and division
of 8 to 128-bit signed/unsigned integers and 32 to 128-bit floats.

I use GCC/Clang's function attributes to define multiple functions for this,
each with different implementations using different SIMD types (like MMX, SSE, AVX)
as well as a fallback function that just completes the operation in a scalar loop (the normal way).

During runtime, the best function is picked depending on what the CPU supports.
For instance, if a particular operation is supported on scalar, MMX, SSE, and AVX, but
during runtime only scalar, MMX, and SSE is supported, the SSE function will likely be used.

There are four function names, ezsimd::add, ezsimd::sub, ezsimd::mul, and ezsimd::div.
These are overloaded a few times to support std::vector, std::array, and C-style arrays
and all the datatypes including:
    int8_t
    int16_t
    int32_t
    int64_t
    __int128_t
    uint8_t
    uint16_t
    uint32_t
    uint64_t
    __uint128_t
    float
    double
    long double

For std::vector:
    ezsimd::add(const std::vector\<T\>& a, const std::vector\<T\>& b, std::vector\<T\>& c)
    where T is the same across all three vectors,
    T is a supported type,
    a and b are the same length,
    and c is the same size as or longer than a.
    The result is written to c.

For std::array:
    ezsimd::add\<size_t S\>(const std::array\<T, S\>& a, const std::array\<T, S\>& b, std::array\<T, S\>& c)
    where T is the same across all three arrays,
    T is a supported type,
    S is the length of the arrays,
    and all three arrays are the same length
    The result is written to c.

For C-style array:
    ezsimd::add(const T* a, const T* b, T* c, size_t l)
    where T is the same across all three arrays,
    T is a supported type,
    and l is less than or equal to the sizes of all three arrays.
    The length of these arrays is not checked against l.
    The result is written to c.

These functions automatically detect if the arrays/vectors are aligned to the right boundary
to use aligned load/store intrinsics.
If they aren't, a small performance loss may be incurred by using unaligned intrinsics,
but the library works the same exact way

Examples:
    std::vector\<float\> a = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    std::vector\<float\> b = {9.9, 8.8, 7.7, 6.6, 5.5, 4.4, 3.3, 2.2, 1.1};
    std::vector\<float\> c(a.size());
    ezsimd::add(a, b, c);
    // c now contains {11, 11, 11, 11, 11, 11, 11, 11, 11}

    std::array\<int32_t, 10\> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::array\<int32_t, 10\> b = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    std::array\<int32_t, 10\> c;
    ezsimd::add\<10\>(a, b, c);
    // c now contains {9, 9, 9, 9, 9, 9, 9, 9, 9, 9}

    int32_t a[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int32_t b[] = {20, 18, 16, 14, 12, 10, 9, 6, 4, 2};
    int32_t c[10];
    ezsimd::add(a, b, c, 10);
    // OR
    ezsimd::ADD(a, b, c);
    // macro that automatically uses the length of a
    // doesn't work on arrays that have decayed to pointers

    For these examples, I used unaligned arrays/vectors.
    If I were to use aligned ones, it would work the same exact way.

    Unfortunately, due to the complicated nature of SIMD operations and my own laziness,
    any leftover elements at the end of an array that are too few to fit inside an entire
    SIMD register are processed with a scalar loop (the normal way).
    So, if I were to have an array of 100 floats (which are 32-bits long each) for a total
    length of 3200 bits or 400 bytes, if at runtime the AVX function was picked
    (which does 256 bits at a time), only 96 of those floats would be processed with AVX.
    The remaining 4 would be added at the end inside a simple for loop.

OpenCL/CUDA functions are in the works.