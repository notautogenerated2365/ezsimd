#include <iostream>
#include <fstream>
#include <string>

#include "enums.hpp"
#include "maps.hpp"

using namespace std;

void make(ofstream& source, ofstream& header, ofstream& templ) {
    source << R"(#pragma once

#include <vector>
#include <array>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <type_traits>

#ifdef EZSIMD_SHOW_FUNC
    #include <iostream>
#endif

#include "libezsimd.hpp"

// __AVX2__ uses same header as __AVX__
#if defined(__AVX__)
    #include <immintrin.h>
#endif
#if defined(__SSE2__)
    #include <emmintrin.h>
#endif
#if defined(__SSE__)
    #include <xmmintrin.h>
#endif
#if defined(__MMX__)
    #include <mmintrin.h>
#endif

namespace ezsimd {
    template <typename T>
    bool isAligned(const T* ptr, size_t alignment) {
        return reinterpret_cast<std::uintptr_t>(static_cast<const void*>(ptr)) % alignment == 0;
    })";

    header << R"(#pragma once

#include <cstdint>
#include <vector>
#include <array>

#if defined(__clang__)
    #warning "clang currently produces unwanted behavior for large amounts of multiversioned functions, keeping only default and best supported SIMD. use g++ for best results."

    #if (defined(__MMX__) && defined(__SSE2__) && defined(__AVX2__))
        #undef __MMX__
        #undef __SSE2__
    #elif defined(__SSE2__)
        #undef __MMX__
    #elif defined(__MMX__) && defined(__AVX2__)
        #undef __MMX__
    #endif

    #if defined(__AVX__)
        #undef __SSE__
    #endif
#elif !(defined(__GNUC__) && !defined(__clang__))
    #warning "compiler may not be supported. use g++ for best results."
#endif

namespace ezsimd {
    template <typename T, size_t N>
    constexpr inline size_t arrayLength(T (&)[N]) noexcept;)";

    templ << R"(#pragma once

#include <cstdint>
#include <array>

// all backend functions must be declared for templated frontends to work properly
// templated functions declared in libezsimd.hpp, defined in this file

namespace ezsimd {
    template <typename T, size_t N>
    constexpr inline size_t arrayLength(T (&)[N]) noexcept {
        return N;
    })";

    opType _opType;
    numType _numType;
    arrayType _arrayType;
    simdType _simdType;

    for (char i = 0; i < 4; i++) { // for each of the 4 opTypes (add, sub, mul, div)
        _opType = opType(i);

        source
            << "\n    "
            << "\n    #pragma region // " << opMeta.at(_opType).name
        ;

        header
            << "\n    "
            << "\n    #pragma region // " << opMeta.at(_opType).name
        ;

        templ
            << "\n    "
            << "\n    #pragma region // " << opMeta.at(_opType).name
        ;

        for (char j = 0; j < 14; j++) { // for each numType
            _numType = numType(j);

            if (_numType == FLOAT16) {
                continue;
                // not supported
            }

            source
                << "\n        #pragma region // " << numMeta.at(_numType).numName
            ;

            header
                << "\n        #pragma region // " << numMeta.at(_numType).numName
            ;

            templ
                << "\n        #pragma region // " << numMeta.at(_numType).numName
            ;
            
            source
                << "\n            __attribute__((target(\"default\")))"
                << "\n            inline void " << opMeta.at(_opType).name << "Backend(const " << numMeta.at(_numType).numName << "* a, const " << numMeta.at(_numType).numName << "* b, " << numMeta.at(_numType).numName << "* c, size_t l) {"
                << "\n                #ifdef EZSIMD_SHOW_FUNC"
                << "\n                    EZSIMD_SHOW_FUNC << \"target(\\\"default\\\") "<< opMeta.at(_opType).name << "\\n\";"
                << "\n                #endif"
                << "\n                "
                << "\n                for (size_t i = 0; i < l; i++) {"
                << "\n                    c[i] = a[i] + b[i];"
                << "\n                }"
                << "\n            }"
            ;

            header
                << "\n            __attribute__((target(\"default\")))"
                << "\n            inline void " << opMeta.at(_opType).name << "Backend(const " << numMeta.at(_numType).numName << "* a, const " << numMeta.at(_numType).numName << "* b, " << numMeta.at(_numType).numName << "* c, size_t l);"
            ;

            for (char l = 0; l < 5; l++) { // for each simdType
                _simdType = simdType(l);
            
                if (supportedOps.at(_simdType).at(_opType).at(_numType)) {
                    templ
                        << "\n            #ifdef " << simdMeta.at(_simdType).ifdefMacro
                        << "\n                __attribute__((target(\"" << simdMeta.at(_simdType).name << "\")))"
                        << "\n                inline void " << opMeta.at(_opType).name << "Backend(const " << numMeta.at(_numType).numName << "* a, const " << numMeta.at(_numType).numName << "* b, " << numMeta.at(_numType).numName << "* c, const size_t l);"
                        << "\n            #endif // " << simdMeta.at(_simdType).ifdefMacro
                        << '\n'
                    ;

                    source
                        << '\n'
                        << "\n            #ifdef " << simdMeta.at(_simdType).ifdefMacro
                        << "\n                __attribute__((target(\"" << simdMeta.at(_simdType).name << "\")))"
                        << "\n                inline void " << opMeta.at(_opType).name << "Backend(const " << numMeta.at(_numType).numName << "* a, const " << numMeta.at(_numType).numName << "* b, " << numMeta.at(_numType).numName << "* c, const size_t l) {"
                        << "\n                    #ifdef EZSIMD_SHOW_FUNC"
                        << "\n                        EZSIMD_SHOW_FUNC << \"target(\\\"" << simdMeta.at(_simdType).name << "\\\") "<< opMeta.at(_opType).name << "\\n\";"
                        << "\n                    #endif"
                        << "\n                    "
                        << "\n                    size_t i = 0;"
                        << "\n                    " << simdRegTypenames.at(_simdType).at(_numType) << " vec_a;"
                        << "\n                    " << simdRegTypenames.at(_simdType).at(_numType) << " vec_b;"
                        << "\n                    " << simdRegTypenames.at(_simdType).at(_numType) << " vec_c;"
                        << "\n                    const bool isAlignedA = isAligned(a, " << (simdMeta.at(_simdType).bitSize / 8) << ");"
                        << "\n                    const bool isAlignedB = isAligned(b, " << (simdMeta.at(_simdType).bitSize / 8) << ");"
                        << "\n                    const bool isAlignedC = isAligned(c, " << (simdMeta.at(_simdType).bitSize / 8) << ");"
                        << "\n                    "
                        << "\n                    for (; i + " << ((simdMeta.at(_simdType).bitSize / numMeta.at(_numType).bitSize) - 1) << " < l; i += " << (simdMeta.at(_simdType).bitSize / numMeta.at(_numType).bitSize) << ") {"
                        << "\n                        if (isAlignedA) {"
                        << "\n                            vec_a = " << functions.at(_simdType).at(PACK_ALIGNED).at(_numType) << "(a + i);"
                        << "\n                        } else {"
                        << "\n                            vec_a = " << functions.at(_simdType).at(PACK_UNALIGNED).at(_numType) << "(a + i);"
                        << "\n                        }"
                        << "\n                        "
                        << "\n                        if (isAlignedB) {"
                        << "\n                            vec_b = " << functions.at(_simdType).at(PACK_ALIGNED).at(_numType) << "(b + i);"
                        << "\n                        } else {"
                        << "\n                            vec_b = " << functions.at(_simdType).at(PACK_UNALIGNED).at(_numType) << "(b + i);"
                        << "\n                        }"
                        << "\n                        "
                        << "\n                        vec_c = " << functions.at(_simdType).at(_opType).at(_numType) << "(vec_a, vec_b);"
                        << "\n                        "
                        << "\n                        if (isAlignedC) {"
                        << "\n                            " << functions.at(_simdType).at(UNPACK_ALIGNED).at(_numType) << "(c + i, vec_c);"
                        << "\n                        } else {"
                        << "\n                            " << functions.at(_simdType).at(UNPACK_UNALIGNED).at(_numType) << "(c + i, vec_c);"
                        << "\n                        }"
                        << "\n                    }"
                        << "\n                    "
                        << "\n                    for (; i < l; i++) {"
                        << "\n                        c[i] = a[i] + b[i];"
                        << "\n                    }"
                    ;

                    if (_simdType == MMX) {
                        source
                            << "\n                    "
                            << "\n                    _mm_empty();"
                        ;
                    }

                    source
                        << "\n                }"
                        << "\n            #endif // " << simdMeta.at(_simdType).ifdefMacro
                    ;
                }
            }

            source
                << "\n"
                << "\n            void " << opMeta.at(_opType).name << "(const std::vector<" << numMeta.at(_numType).numName << ">& a, const std::vector<" << numMeta.at(_numType).numName << ">& b, std::vector<" << numMeta.at(_numType).numName <<">& c) {"
                << "\n                assert(a.size() == b.size());"
                << "\n                assert(c.size() >= a.size());"
                << "\n                " << opMeta.at(_opType).name << "Backend(a.data(), b.data(), c.data(), a.size());"
                << "\n            }"
                << "\n            "
                << "\n            void " << opMeta.at(_opType).name << "(const " << numMeta.at(_numType).numName << "* a, const " << numMeta.at(_numType).numName << "* b, " << numMeta.at(_numType).numName << "* c, size_t l) {"
                << "\n                " << opMeta.at(_opType).name << "Backend(a, b, c, l);"
                << "\n            }"
                << "\n        #pragma endregion // " << numMeta.at(_numType).numName
                << "\n"
            ;

            header
                << "\n            void " << opMeta.at(_opType).name << "(const std::vector<" << numMeta.at(_numType).numName << ">& a, const std::vector<" << numMeta.at(_numType).numName << ">& b, std::vector<" << numMeta.at(_numType).numName <<">& c);"
                << "\n            template <size_t S>"
                << "\n            void " << opMeta.at(_opType).name << "(const std::array<" << numMeta.at(_numType).numName << ", S>& a, const std::array<" << numMeta.at(_numType).numName << ", S>& b, std::array<" << numMeta.at(_numType).numName <<", S>& c);"
                << "\n            void " << opMeta.at(_opType).name << "(const " << numMeta.at(_numType).numName << "* a, const " << numMeta.at(_numType).numName << "* b, " << numMeta.at(_numType).numName << "* c, size_t l);"
                << "\n            #define " << opMeta.at(_opType).capsName << "(a, b, c) " << opMeta.at(_opType).name << "(a, b, c, ezsimd::arrayLength(a))"
                << "\n        #pragma endregion // " << numMeta.at(_numType).numName
                << "\n"
            ;

            templ
                << "\n            template <size_t S>"
                << "\n            void " << opMeta.at(_opType).name << "(const std::array<" << numMeta.at(_numType).numName << ", S>& a, const std::array<" << numMeta.at(_numType).numName << ", S>& b, std::array<" << numMeta.at(_numType).numName <<", S>& c) {"
                << "\n                " << opMeta.at(_opType).name << "Backend(a.data(), b.data(), c.data(), S);"
                << "\n            }"
                << "\n        #pragma endregion // " << numMeta.at(_numType).numName
                << "\n"
            ;
        }

        source
            << "    #pragma endregion // " << opMeta.at(_opType).name
        ;

        header
            << "    #pragma endregion // " << opMeta.at(_opType).name
        ;
    }

    source << "\n} // namespace ezsimd";
    header 
        << "\n} // namespace ezsimd"
        << "\n"
        << "\n#include \"libezsimd.ipp\" // full definitions for templates declared in this file only"
        << "\n// templates declared in ezsimd.hpp are simply defined in ezsimd.hpp"
    ;
    templ << "\n} // namespace ezsimd";
}

int main() {
    ofstream source("../ezsimd.hpp");
    ofstream header("../libezsimd.hpp");
    ofstream library("../ezsimd.cpp");
    ofstream templ("../libezsimd.ipp");

    if (!source.is_open()) {
        cerr << "Error opening output source file\n";
        return 1;
    } if (!header.is_open()) {
        cerr << "Error opening output header file\n";
        return 1;
    } if (!library.is_open()) {
        cerr << "Error opening output library file\n";
        return 1;
    } if (!templ.is_open()) {
        cerr << "Error opening output template file\n";
        return 1;
    }

    library
        << "#include \"ezsimd.hpp\""
    ;

    make(source, header, templ);
    source.close();
    header.close();
    library.close();
    templ.close();
    return 0;
}