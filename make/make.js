const fs = require("fs");
const arrays = require("./arrays.cjs");
const objects = require("./objects.cjs");

global.simdType = arrays.simdType;
global.numType = arrays.numType;
global.opType = arrays.opType;

global.simdRegTypenames = objects.simdRegTypenames;
global.supportedOps = objects.supportedOps;
global.functions = objects.functions;
global.simdMeta = objects.simdMeta;
global.numMeta = objects.numMeta;
global.opMeta = objects.opMeta;

function make(sourcePath, headerPath, templPath) {
    let source = "";
    let header = "";
    let templ = "";

    source += `#pragma once

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
    }`;

    header += `#pragma once

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
    constexpr inline size_t arrayLength(T (&)[N]) noexcept;`;

    templ += `#pragma once

#include <cstdint>
#include <array>

// all backend functions are declared here so templated frontends can work properly
// templated functions declared in libezsimd.hpp, defined in this file

namespace ezsimd {
    template <typename T, size_t N>
    constexpr inline size_t arrayLength(T (&)[N]) noexcept {
        return N;
    }`;

    let _opType;
    let _numType;
    let _arrayType;
    let _simdType;

    for (let i = 0; i < 4; i++) { // for each opType
        _opType = opType[i];
        
        source += ""
            + "\n    "
            + "\n    #pragma region // " + opMeta[_opType].name
        ;

        header += ""
            + "\n    "
            + "\n    #pragma region // " + opMeta[_opType].name
        ;

        templ += ""
            + "\n    "
            + "\n    #pragma region // " + opMeta[_opType].name
        ;

        for (let j = 0; j < 14; j++) { // for each numType
            _numType = numType[j];

            if (_numType == "FLOAT16") {
                continue;
                // not supported
            }

            source += ""
                + "\n        #pragma region // " + numMeta[_numType].numName
            ;

            header += ""
                + "\n        #pragma region // " + numMeta[_numType].numName
            ;

            templ += ""
                + "\n        #pragma region // " + numMeta[_numType].numName
            ;

            source += ""
                + "\n            __attribute__((target(\"default\")))"
                + "\n            inline void " + opMeta[_opType].name + "Backend(const " + numMeta[_numType].numName + "* a, const " + numMeta[_numType].numName + "* b, " + numMeta[_numType].numName + "* c, const size_t l) {"
                + "\n                #ifdef EZSIMD_SHOW_FUNC"
                + "\n                    EZSIMD_SHOW_FUNC << \"target(\\\"default\\\") " + opMeta[_opType].name + "\\n\";"
                + "\n                #endif"
                + "\n                "
                + "\n                for (size_t i = 0; i < l; i++) {"
                + "\n                    c[i] = a[i] + b[i];"
                + "\n                }"
                + "\n            }"
            ;

            templ += ""
                + "\n            __attribute__((target(\"default\")))"
                + "\n            inline void " + opMeta[_opType].name + "Backend(const " + numMeta[_numType].numName + "* a, const " + numMeta[_numType].numName + "* b, " + numMeta[_numType].numName + "* c, const size_t l);"
                + "\n"
            ;

            for (let k = 0; k < 5; k++) { // for each simdType
                _simdType = simdType[k];

                if (supportedOps[_simdType][_opType][_numType]) {
                    templ += ""
                        + "\n            #ifdef " + simdMeta[_simdType].ifdefMacro
                        + "\n                __attribute__((target(\"" + simdMeta[_simdType].name + "\")))"
                        + "\n                inline void " + opMeta[_opType].name + "Backend(const " + numMeta[_numType].numName + "* a, const " + numMeta[_numType].numName + "* b, " + numMeta[_numType].numName + "* c, const size_t l);"
                        + "\n            #endif // " + simdMeta[_simdType].ifdefMacro
                        + "\n"
                    ;

                    source += ""
                        + "\n"
                        + "\n            #ifdef " + simdMeta[_simdType].ifdefMacro
                        + "\n                __attribute__((target(\"" + simdMeta[_simdType].name + "\")))"
                        + "\n                inline void " + opMeta[_opType].name + "Backend(const " + numMeta[_numType].numName + "* a, const " + numMeta[_numType].numName + "* b, " + numMeta[_numType].numName + "* c, const size_t l) {"
                        + "\n                    #ifdef EZSIMD_SHOW_FUNC"
                        + "\n                        EZSIMD_SHOW_FUNC << \"target(\\\"" + simdMeta[_simdType].name + "\\\") " + opMeta[_opType].name + "\\n\";"
                        + "\n                    #endif"
                        + "\n                    "
                        + "\n                    size_t i = 0;"
                        + "\n                    " + simdRegTypenames[_simdType][_numType] + " vec_a;"
                        + "\n                    " + simdRegTypenames[_simdType][_numType] + " vec_b;"
                        + "\n                    " + simdRegTypenames[_simdType][_numType] + " vec_c;"
                        + "\n                    const bool isAlignedA = isAligned(a, " + (simdMeta[_simdType].bitSize / 8) + ");"
                        + "\n                    const bool isAlignedB = isAligned(b, " + (simdMeta[_simdType].bitSize / 8) + ");"
                        + "\n                    const bool isAlignedC = isAligned(c, " + (simdMeta[_simdType].bitSize / 8) + ");"
                        + "\n                    "
                        + "\n                    for (; i + " + ((simdMeta[_simdType].bitSize / numMeta[_numType].bitSize) - 1) + " < l; i += " + (simdMeta[_simdType].bitSize / numMeta[_numType].bitSize) + ") {"
                        + "\n                        if (isAlignedA) {"
                        + "\n                            vec_a = " + functions[_simdType]["PACK_ALIGNED"][_numType] + "(a + i);"
                        + "\n                        } else {"
                        + "\n                            vec_a = " + functions[_simdType]["PACK_UNALIGNED"][_numType] + "(a + i);"
                        + "\n                        }"
                        + "\n                        "
                        + "\n                        if (isAlignedB) {"
                        + "\n                            vec_b = " + functions[_simdType]["PACK_ALIGNED"][_numType] + "(b + i);"
                        + "\n                        } else {"
                        + "\n                            vec_b = " + functions[_simdType]["PACK_UNALIGNED"][_numType] + "(b + i);"
                        + "\n                        }"
                        + "\n                        "
                        + "\n                        vec_c = " + functions[_simdType][_opType][_numType] + "(vec_a, vec_b);"
                        + "\n                        "
                        + "\n                        if (isAlignedC) {"
                        + "\n                            " + functions[_simdType]["UNPACK_ALIGNED"][_numType] + "(c + i, vec_c);"
                        + "\n                        } else {"
                        + "\n                            " + functions[_simdType]["UNPACK_UNALIGNED"][_numType] + "(c + i, vec_c);"
                        + "\n                        }"
                        + "\n                    }"
                        + "\n                    "
                        + "\n                    for (; i < l; i++) {"
                        + "\n                        c[i] = a[i] + b[i];"
                        + "\n                    }"
                    ;

                    if (_simdType == "MMX") {
                        source += ""
                            + "\n                    "
                            + "\n                    _mm_empty();"
                        ;
                    }

                    source += ""
                        + "\n                }"
                        + "\n            #endif // " + simdMeta[_simdType].ifdefMacro
                    ;
                }
            }

            source += ""
                + "\n"
                + "\n            void " + opMeta[_opType].name + "(const std::vector<" + numMeta[_numType].numName + ">& a, const std::vector<" + numMeta[_numType].numName + ">& b, std::vector<" + numMeta[_numType].numName + ">& c) {"
                + "\n                assert(a.size() == b.size());"
                + "\n                assert(c.size() >= a.size());"
                + "\n                " + opMeta[_opType].name + "Backend(a.data(), b.data(), c.data(), a.size());"
                + "\n            }"
                + "\n            "
                + "\n            void " + opMeta[_opType].name + "(const " + numMeta[_numType].numName + "* a, const " + numMeta[_numType].numName + "* b, " + numMeta[_numType].numName + "* c, const size_t l) {"
                + "\n                " + opMeta[_opType].name + "Backend(a, b, c, l);"
                + "\n            }"
                + "\n        #pragma endregion // " + numMeta[_numType].numName
                + "\n"
            ;

            header += ""
                + "\n            void " + opMeta[_opType].name + "(const std::vector<" + numMeta[_numType].numName + ">& a, const std::vector<" + numMeta[_numType].numName + ">& b, std::vector<" + numMeta[_numType].numName + ">& c);"
                + "\n            template <size_t S>"
                + "\n            void " + opMeta[_opType].name + "(const std::array<" + numMeta[_numType].numName + ", S>& a, const std::array<" + numMeta[_numType].numName + ", S>& b, std::array<" + numMeta[_numType].numName +", S>& c);"
                + "\n            void " + opMeta[_opType].name + "(const " + numMeta[_numType].numName + "* a, const " + numMeta[_numType].numName + "* b, " + numMeta[_numType].numName + "* c, const size_t l);"
                + "\n        #pragma endregion // " + numMeta[_numType].numName
                + "\n"
            ;

            templ += ""
                + "\n            template <size_t S>"
                + "\n            void " + opMeta[_opType].name + "(const std::array<" + numMeta[_numType].numName + ", S>& a, const std::array<" + numMeta[_numType].numName + ", S>& b, std::array<" + numMeta[_numType].numName +", S>& c) {"
                + "\n                " + opMeta[_opType].name + "Backend(a.data(), b.data(), c.data(), S);"
                + "\n            }"
                + "\n        #pragma endregion // " + numMeta[_numType].numName 
                + "\n"
            ;
        }

        source += ""
            + "    #pragma endregion // " + opMeta[_opType].name
        ;

        header += ""
            + "        "
            + "\n        #define " + opMeta[_opType].capsName + "(a, b, c) " + opMeta[_opType].name + "(a, b, c, ezsimd::arrayLength(a))"
            + "\n    #pragma endregion // " + opMeta[_opType].name
        ;

        templ += ""
            + "    #pragma endregion // " + opMeta[_opType].name
        ;
    }

    source += "\n} // namespace ezsimd";
    header += ""
        + "\n} // namespace ezsimd";
        + "\n"
        + "\n#include \"libezsimd.tpp\" // full definitions for templates declared in this file only"
        + "\n// templates declared in ezsimd.hpp are simply defined in ezsimd.hpp"
    ;
    templ += "\n} // namespace ezsimd";

    fs.writeFile(sourcePath, source, (err) =>{
        if (err) console.log(err);
    });
    fs.writeFile(headerPath, header, (err) =>{
        if (err) console.log(err);
    });
    fs.writeFile(templPath, templ, (err) =>{
        if (err) console.log(err);
    });
}

const sourcePath = "../ezsimd.hpp"
const headerPath = "../libezsimd.hpp"
const libraryPath = "../ezsimd.cpp"
const templPath = "../libezsimd.tpp"

fs.writeFile(libraryPath, "#include \"ezsimd.hpp\"", (err) => {
    if (err) console.error(err);
});

make(sourcePath, headerPath, templPath);