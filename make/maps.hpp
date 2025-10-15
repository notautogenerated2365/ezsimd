#pragma once

#include <map>
#include <string>

#include "enums.hpp"

// names of SIMD register variable names that hold certain datatypes
const std::map<simdType, std::map<numType, std::string>> simdRegTypenames = {
    {MMX, {
        {INT8, "__m64"},
        {INT16, "__m64"},
        {INT32, "__m64"},
        {UINT8, "__m64"},
        {UINT16, "__m64"},
        {UINT32, "__m64"},
    }},
    {SSE, {
        {FLOAT32, "__m128"},
    }},
    {SSE2, {
        {INT8, "__m128i"},
        {INT16, "__m128i"},
        {INT32, "__m128i"},
        {INT64, "__m128i"},
        {UINT8, "__m128i"},
        {UINT16, "__m128i"},
        {UINT32, "__m128i"},
        {UINT64, "__m128i"},
        {FLOAT64, "__m128d"},
    }},
    {AVX, {
        {FLOAT32, "__m256"},
        {FLOAT64, "__m256d"},
    }},
    {AVX2, {
        {INT8, "__m256i"},
        {INT16, "__m256i"},
        {INT32, "__m256i"},
        {INT64, "__m256i"},
        {UINT8, "__m256i"},
        {UINT16, "__m256i"},
        {UINT32, "__m256i"},
        {UINT64, "__m256i"}
    }},
};

// supported operations for each numType for each simdType
const std::map<simdType, std::map<opType, std::map<numType, bool>>> supportedOps = {
    {MMX, {
        {ADD, {
            {INT8, true},
            {INT16, true},
            {INT32, true},
            {INT64, false},
            {INT128, false},
            {UINT8, true},
            {UINT16, true},
            {UINT32, true},
            {UINT64, false},
            {UINT128, false},
            {FLOAT16, false},
            {FLOAT32, false},
            {FLOAT64, false},
            {FLOAT128, false},
        }}, // ADD
        {SUB, {
            {INT8, true},
            {INT16, true},
            {INT32, true},
            {INT64, false},
            {INT128, false},
            {UINT8, true},
            {UINT16, true},
            {UINT32, true},
            {UINT64, false},
            {UINT128, false},
            {FLOAT16, false},
            {FLOAT32, false},
            {FLOAT64, false},
            {FLOAT128, false},
        }}, // SUB
        {MUL, {
            {INT8, false},
            {INT16, true},
            {INT32, false},
            {INT64, false},
            {INT128, false},
            {UINT8, false},
            {UINT16, true},
            {UINT32, false},
            {UINT64, false},
            {UINT128, false},
            {FLOAT16, false},
            {FLOAT32, false},
            {FLOAT64, false},
            {FLOAT128, false},
        }}, // MUL
        {DIV, {
            {INT8, false},
            {INT16, false},
            {INT32, false},
            {INT64, false},
            {INT128, false},
            {UINT8, false},
            {UINT16, false},
            {UINT32, false},
            {UINT64, false},
            {UINT128, false},
            {FLOAT16, false},
            {FLOAT32, false},
            {FLOAT64, false},
            {FLOAT128, false},
        }}, // DIV
    }}, // MMX
    {SSE, {
        {ADD, {
            {INT8, false},
            {INT16, false},
            {INT32, false},
            {INT64, false},
            {INT128, false},
            {UINT8, false},
            {UINT16, false},
            {UINT32, false},
            {UINT64, false},
            {UINT128, false},
            {FLOAT16, false},
            {FLOAT32, true},
            {FLOAT64, false},
            {FLOAT128, false},
        }}, // ADD
        {SUB, {
            {INT8, false},
            {INT16, false},
            {INT32, false},
            {INT64, false},
            {INT128, false},
            {UINT8, false},
            {UINT16, false},
            {UINT32, false},
            {UINT64, false},
            {UINT128, false},
            {FLOAT16, false},
            {FLOAT32, true},
            {FLOAT64, false},
            {FLOAT128, false},
        }}, // SUB
        {MUL, {
            {INT8, false},
            {INT16, false},
            {INT32, false},
            {INT64, false},
            {INT128, false},
            {UINT8, false},
            {UINT16, false},
            {UINT32, false},
            {UINT64, false},
            {UINT128, false},
            {FLOAT16, false},
            {FLOAT32, true},
            {FLOAT64, false},
            {FLOAT128, false},
        }}, // MUL
        {DIV, {
            {INT8, false},
            {INT16, false},
            {INT32, false},
            {INT64, false},
            {INT128, false},
            {UINT8, false},
            {UINT16, false},
            {UINT32, false},
            {UINT64, false},
            {UINT128, false},
            {FLOAT16, false},
            {FLOAT32, true},
            {FLOAT64, false},
            {FLOAT128, false},
        }}, // DIV
    }}, // SSE
    {SSE2, {
        {ADD, {
            {INT8, true},
            {INT16, true},
            {INT32, true},
            {INT64, true},
            {INT128, false},
            {UINT8, true},
            {UINT16, true},
            {UINT32, true},
            {UINT64, true},
            {UINT128, false},
            {FLOAT16, false},
            {FLOAT32, false},
            {FLOAT64, true},
            {FLOAT128, false},
        }}, // ADD
        {SUB, {
            {INT8, true},
            {INT16, true},
            {INT32, true},
            {INT64, true},
            {INT128, false},
            {UINT8, true},
            {UINT16, true},
            {UINT32, true},
            {UINT64, true},
            {UINT128, false},
            {FLOAT16, false},
            {FLOAT32, false},
            {FLOAT64, true},
            {FLOAT128, false},
        }}, // SUB
        {MUL, {
            {INT8, false},
            {INT16, true},
            {INT32, false},
            {INT64, false},
            {INT128, false},
            {UINT8, false},
            {UINT16, true},
            {UINT32, false},
            {UINT64, false},
            {UINT128, false},
            {FLOAT16, false},
            {FLOAT32, false},
            {FLOAT64, true},
            {FLOAT128, false},
        }}, // MUL
        {DIV, {
            {INT8, false},
            {INT16, false},
            {INT32, false},
            {INT64, false},
            {INT128, false},
            {UINT8, false},
            {UINT16, false},
            {UINT32, false},
            {UINT64, false},
            {UINT128, false},
            {FLOAT16, false},
            {FLOAT32, false},
            {FLOAT64, true},
            {FLOAT128, false},
        }}, // DIV
    }}, // SSE2
    {AVX, {
        {ADD, {
            {INT8, false},
            {INT16, false},
            {INT32, false},
            {INT64, false},
            {INT128, false},
            {UINT8, false},
            {UINT16, false},
            {UINT32, false},
            {UINT64, false},
            {UINT128, false},
            {FLOAT16, false},
            {FLOAT32, true},
            {FLOAT64, true},
            {FLOAT128, false},
        }}, // ADD
        {SUB, {
            {INT8, false},
            {INT16, false},
            {INT32, false},
            {INT64, false},
            {INT128, false},
            {UINT8, false},
            {UINT16, false},
            {UINT32, false},
            {UINT64, false},
            {UINT128, false},
            {FLOAT16, false},
            {FLOAT32, true},
            {FLOAT64, true},
            {FLOAT128, false},
        }}, // SUB
        {MUL, {
            {INT8, false},
            {INT16, false},
            {INT32, false},
            {INT64, false},
            {INT128, false},
            {UINT8, false},
            {UINT16, false},
            {UINT32, false},
            {UINT64, false},
            {UINT128, false},
            {FLOAT16, false},
            {FLOAT32, true},
            {FLOAT64, true},
            {FLOAT128, false},
        }}, // MUL
        {DIV, {
            {INT8, false},
            {INT16, false},
            {INT32, false},
            {INT64, false},
            {INT128, false},
            {UINT8, false},
            {UINT16, false},
            {UINT32, false},
            {UINT64, false},
            {UINT128, false},
            {FLOAT16, false},
            {FLOAT32, true},
            {FLOAT64, true},
            {FLOAT128, false},
        }}, // DIV
    }}, // AVX
    {AVX2, {
        {ADD, {
            {INT8, true},
            {INT16, true},
            {INT32, true},
            {INT64, true},
            {INT128, false},
            {UINT8, true},
            {UINT16, true},
            {UINT32, true},
            {UINT64, true},
            {UINT128, false},
            {FLOAT16, false},
            {FLOAT32, false},
            {FLOAT64, false},
            {FLOAT128, false},
        }}, // ADD
        {SUB, {
            {INT8, true},
            {INT16, true},
            {INT32, true},
            {INT64, true},
            {INT128, false},
            {UINT8, true},
            {UINT16, true},
            {UINT32, true},
            {UINT64, true},
            {UINT128, false},
            {FLOAT16, false},
            {FLOAT32, false},
            {FLOAT64, false},
            {FLOAT128, false},
        }}, // SUB
        {MUL, {
            {INT8, false},
            {INT16, true},
            {INT32, true},
            {INT64, false},
            {INT128, false},
            {UINT8, false},
            {UINT16, true},
            {UINT32, true},
            {UINT64, false},
            {UINT128, false},
            {FLOAT16, false},
            {FLOAT32, false},
            {FLOAT64, false},
            {FLOAT128, false},
        }}, // MUL
        {DIV, {
            {INT8, false},
            {INT16, false},
            {INT32, false},
            {INT64, false},
            {INT128, false},
            {UINT8, false},
            {UINT16, false},
            {UINT32, false},
            {UINT64, false},
            {UINT128, false},
            {FLOAT16, false},
            {FLOAT32, false},
            {FLOAT64, false},
            {FLOAT128, false},
        }}, // DIV
    }}, // AVX2
}; // supportedOps

// function names for each supported numType for each supported opType for each simdType
// if any numType is marked as false in supportedOps, it should not be included here
const std::map<simdType, std::map<opType, std::map<numType, std::string>>> functions = {
    {MMX, {
        {PACK_ALIGNED, {
            {INT8, "[](const int8_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}"},
            {INT16, "[](const int16_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}"},
            {INT32, "[](const int32_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}"},
            {UINT8, "[](const uint8_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}"},
            {UINT16, "[](const uint16_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}"},
            {UINT32, "[](const uint32_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}"},
        }},
        {PACK_UNALIGNED, {
            {INT8, "[](const int8_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}"},
            {INT16, "[](const int16_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}"},
            {INT32, "[](const int32_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}"},
            {UINT8, "[](const uint8_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}"},
            {UINT16, "[](const uint16_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}"},
            {UINT32, "[](const uint32_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}"},
        }},
        {ADD, {
            {INT8, "_mm_add_pi8"},
            {INT16, "_mm_add_pi16"},
            {INT32, "_mm_add_pi32"},
            {UINT8, "_mm_add_pi8"},
            {UINT16, "_mm_add_pi16"},
            {UINT32, "_mm_add_pi32"},
        }},
        {SUB, {
            {INT8, "_mm_sub_pi8"},
            {INT16, "_mm_sub_pi16"},
            {INT32, "_mm_sub_pi32"},
            {UINT8, "_mm_sub_pi8"},
            {UINT16, "_mm_sub_pi16"},
            {UINT32, "_mm_sub_pi32"},
        }},
        {MUL, {
            {INT16, "_mm_mullo_pi16"},
            {UINT16, "_mm_mullo_pi16"},
        }},
        {DIV, {
            // no support
        }},
        {UNPACK_ALIGNED, {
            {INT8, "[](int8_t *ptr, const __m64 vec) {*reinterpret_cast<__m64*>(ptr) = vec;}"},
            {INT16, "[](int16_t *ptr, const __m64 vec) {*reinterpret_cast<__m64*>(ptr) = vec;}"},
            {INT32, "[](int32_t *ptr, const __m64 vec) {*reinterpret_cast<__m64*>(ptr) = vec;}"},
            {UINT8, "[](uint8_t *ptr, const __m64 vec) {*reinterpret_cast<__m64*>(ptr) = vec;}"},
            {UINT16, "[](uint16_t *ptr, const __m64 vec) {*reinterpret_cast<__m64*>(ptr) = vec;}"},
            {UINT32, "[](uint32_t *ptr, const __m64 vec) {*reinterpret_cast<__m64*>(ptr) = vec;}"},
        }},
        {UNPACK_UNALIGNED, {
            {INT8, "[](int8_t *ptr, const __m64 vec) {std::memcpy(ptr, &vec, sizeof(__m64));}"},
            {INT16, "[](int16_t *ptr, const __m64 vec) {std::memcpy(ptr, &vec, sizeof(__m64));}"},
            {INT32, "[](int32_t *ptr, const __m64 vec) {std::memcpy(ptr, &vec, sizeof(__m64));}"},
            {UINT8, "[](uint8_t *ptr, const __m64 vec) {std::memcpy(ptr, &vec, sizeof(__m64));}"},
            {UINT16, "[](uint16_t *ptr, const __m64 vec) {std::memcpy(ptr, &vec, sizeof(__m64));}"},
            {UINT32, "[](uint32_t *ptr, const __m64 vec) {std::memcpy(ptr, &vec, sizeof(__m64));}"},
        }},
    }},
    {SSE, {
        {PACK_ALIGNED, {
            {FLOAT32, "_mm_load_ps"}
        }},
        {PACK_UNALIGNED, {
            {FLOAT32, "_mm_loadu_ps"}
        }},
        {ADD, {
            {FLOAT32, "_mm_add_ps"}
        }},
        {SUB, {
            {FLOAT32, "_mm_sub_ps"}
        }},
        {MUL, {
            {FLOAT32, "_mm_mul_ps"}
        }},
        {DIV, {
            {FLOAT32, "_mm_div_ps"}
        }},
        {UNPACK_ALIGNED, {
            {FLOAT32, "_mm_store_ps"}
        }},
        {UNPACK_UNALIGNED, {
            {FLOAT32, "_mm_storeu_ps"}
        }},
    }},
    {SSE2, { // revisit integer support for SSE versions, might have to add SSE3 section or something
        {PACK_ALIGNED, {
            {INT8, "[](const int8_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}"},
            {INT16, "[](const int16_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}"},
            {INT32, "[](const int32_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}"},
            {INT64, "[](const int64_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}"},
            {UINT8, "[](const uint8_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}"},
            {UINT16, "[](const uint16_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}"},
            {UINT32, "[](const uint32_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}"},
            {UINT64, "[](const uint64_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}"},
            {FLOAT64, "_mm_load_pd"},
        }},
        {PACK_UNALIGNED, {
            {INT8, "[](const int8_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}"},
            {INT16, "[](const int16_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}"},
            {INT32, "[](const int32_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}"},
            {INT64, "[](const int64_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}"},
            {UINT8, "[](const uint8_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}"},
            {UINT16, "[](const uint16_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}"},
            {UINT32, "[](const uint32_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}"},
            {UINT64, "[](const uint64_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}"},
            {FLOAT64, "_mm_loadu_pd"},
        }},
        {ADD, {
            {INT8, "_mm_add_epi8"},
            {INT16, "_mm_add_epi16"},
            {INT32, "_mm_add_epi32"},
            {INT64, "_mm_add_epi64"},
            {UINT8, "_mm_add_epi8"},
            {UINT16, "_mm_add_epi16"},
            {UINT32, "_mm_add_epi32"},
            {UINT64, "_mm_add_epi64"},
            {FLOAT64, "_mm_add_pd"},
        }},
        {SUB, {
            {INT8, "_mm_sub_epi8"},
            {INT16, "_mm_sub_epi16"},
            {INT32, "_mm_sub_epi32"},
            {INT64, "_mm_sub_epi64"},
            {UINT8, "_mm_sub_epi8"},
            {UINT16, "_mm_sub_epi16"},
            {UINT32, "_mm_sub_epi32"},
            {UINT64, "_mm_sub_epi64"},
            {FLOAT64, "_mm_sub_pd"},
        }},
        {MUL, {
            {INT16, "_mm_mullo_epi16"},
            {UINT16, "_mm_mullo_epi16"},
            {FLOAT64, "_mm_mul_pd"},
        }},
        {DIV, {
            {FLOAT64, "_mm_div_pd"},
        }},
        {UNPACK_ALIGNED, {
            {INT8, "[](int8_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}"},
            {INT16, "[](int16_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}"},
            {INT32, "[](int32_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}"},
            {INT64, "[](int64_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}"},
            {UINT8, "[](uint8_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}"},
            {UINT16, "[](uint16_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}"},
            {UINT32, "[](uint32_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}"},
            {UINT64, "[](uint64_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}"},
            {FLOAT64, "_mm_store_pd"},
        }},
        {UNPACK_UNALIGNED, {
            {INT8, "[](int8_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}"},
            {INT16, "[](int16_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}"},
            {INT32, "[](int32_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}"},
            {INT64, "[](int64_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}"},
            {UINT8, "[](uint8_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}"},
            {UINT16, "[](uint16_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}"},
            {UINT32, "[](uint32_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}"},
            {UINT64, "[](uint64_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}"},
            {FLOAT64, "_mm_storeu_pd"},
        }},
    }},
    {AVX, {
        {PACK_ALIGNED, {
            {FLOAT32, "_mm256_load_ps"},
            {FLOAT64, "_mm256_load_pd"},
        }},
        {PACK_UNALIGNED, {
            {FLOAT32, "_mm256_loadu_ps"},
            {FLOAT64, "_mm256_loadu_pd"},
        }},
        {ADD, {
            {FLOAT32, "_mm256_add_ps"},
            {FLOAT64, "_mm256_add_pd"},
        }},
        {SUB, {
            {FLOAT32, "_mm256_sub_ps"},
            {FLOAT64, "_mm256_sub_pd"},
        }},
        {MUL, {
            {FLOAT32, "_mm256_mul_ps"},
            {FLOAT64, "_mm256_mul_pd"},
        }},
        {DIV, {
            {FLOAT32, "_mm256_div_ps"},
            {FLOAT64, "_mm256_div_pd"},
        }},
        {UNPACK_ALIGNED, {
            {FLOAT32, "_mm256_store_ps"},
            {FLOAT64, "_mm256_store_pd"},
        }},
        {UNPACK_UNALIGNED, {
            {FLOAT32, "_mm256_storeu_ps"},
            {FLOAT64, "_mm256_storeu_pd"},
        }},
    }},
    {AVX2, {
        {PACK_ALIGNED, {
            {INT8, "[](const int8_t* ptr) {return _mm256_load_si256(reinterpret_cast<__m256i*>(ptr));}"},
            {INT16, "[](const int16_t* ptr) {return _mm256_load_si256(reinterpret_cast<__m256i*>(ptr));}"},
            {INT32, "[](const int32_t* ptr) {return _mm256_load_si256(reinterpret_cast<__m256i*>(ptr));}"},
            {INT64, "[](const int64_t* ptr) {return _mm256_load_si256(reinterpret_cast<__m256i*>(ptr));}"},
            {UINT8, "[](const uint8_t* ptr) {return _mm256_load_si256(reinterpret_cast<__m256i*>(ptr));}"},
            {UINT16, "[](const uint16_t* ptr) {return _mm256_load_si256(reinterpret_cast<__m256i*>(ptr));}"},
            {UINT32, "[](const uint32_t* ptr) {return _mm256_load_si256(reinterpret_cast<__m256i*>(ptr));}"},
            {UINT64, "[](const uint64_t* ptr) {return _mm256_load_si256(reinterpret_cast<__m256i*>(ptr));}"},
        }},
        {PACK_UNALIGNED, {
            {INT8, "[](const int8_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<__m256i*>(ptr));}"},
            {INT16, "[](const int16_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<__m256i*>(ptr));}"},
            {INT32, "[](const int32_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<__m256i*>(ptr));}"},
            {INT64, "[](const int64_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<__m256i*>(ptr));}"},
            {UINT8, "[](const uint8_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<__m256i*>(ptr));}"},
            {UINT16, "[](const uint16_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<__m256i*>(ptr));}"},
            {UINT32, "[](const uint32_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<__m256i*>(ptr));}"},
            {UINT64, "[](const uint64_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<__m256i*>(ptr));}"},
        }},
        {ADD, {
            {INT8, "_mm256_add_epi8"},
            {INT16, "_mm256_add_epi16"},
            {INT32, "_mm256_add_epi32"},
            {INT64, "_mm256_add_epi64"},
            {UINT8, "_mm256_add_epi8"},
            {UINT16, "_mm256_add_epi16"},
            {UINT32, "_mm256_add_epi32"},
            {UINT64, "_mm256_add_epi64"},
        }},
        {SUB, {
            {INT8, "_mm256_sub_epi8"},
            {INT16, "_mm256_sub_epi16"},
            {INT32, "_mm256_sub_epi32"},
            {INT64, "_mm256_sub_epi64"},
            {UINT8, "_mm256_sub_epi8"},
            {UINT16, "_mm256_sub_epi16"},
            {UINT32, "_mm256_sub_epi32"},
            {UINT64, "_mm256_sub_epi64"},
        }},
        {MUL, {
            {INT16, "_mm256_mullo_epi16"},
            {INT32, "_mm256_mullo_epi32"},
            {UINT16, "_mm256_mullo_epi16"},
            {UINT32, "_mm256_mullo_epi32"},
        }},
        {DIV, {
            // no support
        }},
        {UNPACK_ALIGNED, {
            {INT8, "[](int8_t* ptr, const __m128i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}"},
            {INT16, "[](int16_t* ptr, const __m128i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}"},
            {INT32, "[](int32_t* ptr, const __m128i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}"},
            {INT64, "[](int64_t* ptr, const __m128i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}"},
            {UINT8, "[](uint8_t* ptr, const __m128i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}"},
            {UINT16, "[](uint16_t* ptr, const __m128i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}"},
            {UINT32, "[](uint32_t* ptr, const __m128i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}"},
            {UINT64, "[](uint64_t* ptr, const __m128i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}"},
        }},
        {UNPACK_UNALIGNED, {
            {INT8, "[](int8_t* ptr, const __m128i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}"},
            {INT16, "[](int16_t* ptr, const __m128i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}"},
            {INT32, "[](int32_t* ptr, const __m128i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}"},
            {INT64, "[](int64_t* ptr, const __m128i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}"},
            {UINT8, "[](uint8_t* ptr, const __m128i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}"},
            {UINT16, "[](uint16_t* ptr, const __m128i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}"},
            {UINT32, "[](uint32_t* ptr, const __m128i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}"},
            {UINT64, "[](uint64_t* ptr, const __m128i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}"},
        }},
    }}
}; // functions

struct _struct_simdMeta {
    std::string name;
    std::string ifdefMacro;
    std::string header;
    int bitSize;
}; // this struct is only used to organize metadata for the following map
const std::map<simdType, _struct_simdMeta> simdMeta = {
    {MMX, {"mmx", "__MMX__", "mmintrin.h", 64}},
    {SSE, {"sse", "__SSE__", "xmmintrin.h", 128}},
    {SSE2, {"sse2", "__SSE2__", "emmintrin.h", 128}},
    {AVX, {"avx", "__AVX__", "immintrin.h", 256}},
    {AVX2, {"avx2", "__AVX2__", "immintrin.h", 256}},
}; // simdMeta

struct _struct_numMeta {
    std::string className;
    std::string numName;
    int bitSize;
}; // this struct is only used to organize metadata for the following map
const std::map<numType, _struct_numMeta> numMeta = {
    {INT8, {"int8", "int8_t", 8}},
    {INT16, {"int16", "int16_t", 16}},
    {INT32, {"int32", "int32_t", 32}},
    {INT64, {"int64", "int64_t", 64}},
    {INT128, {"int128", "__int128_t", 128}}, // for gcc/clang
    {UINT8, {"uint8", "uint8_t", 8}},
    {UINT16, {"uint16", "uint16_t", 16}},
    {UINT32, {"uint32", "uint32_t", 32}},
    {UINT64, {"uint64", "uint64_t", 64}},
    {UINT128, {"uint128", "__uint128_t", 128}}, // for gcc/clang
    {FLOAT16, {"float16", "not yet implemented", 16}},
    {FLOAT32, {"float32", "float", 32}},
    {FLOAT64, {"float64", "double", 64}},
    {FLOAT128, {"float128", "long double", 128}},
}; // numMeta

struct _struct_opMeta {
    std::string name;
    std::string capsName;
    char op;
}; // this struct is only used to organize metadata for the following map
const std::map<opType, _struct_opMeta> opMeta = {
    {ADD, {"add", "ADD", '+'}},
    {SUB, {"sub", "SUB", '-'}},
    {MUL, {"mul", "MUL", '*'}},
    {DIV, {"div", "DIV", '/'}},
};