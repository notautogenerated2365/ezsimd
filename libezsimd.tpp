#pragma once

#include <cstdint>
#include <array>

// all backend functions are declared here so templated frontends can work properly
// templated functions declared in libezsimd.hpp, defined in this file

namespace ezsimd {
    template <typename T, size_t N>
    constexpr inline size_t arrayLength(T (&)[N]) noexcept {
        return N;
    }
    
    #pragma region // add
        #pragma region // int8_t
            __attribute__((target("default")))
            inline void addBackend(const int8_t* a, const int8_t* b, int8_t* c, size_t l);

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void addBackend(const int8_t* a, const int8_t* b, int8_t* c, const size_t l);
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void addBackend(const int8_t* a, const int8_t* b, int8_t* c, const size_t l);
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void addBackend(const int8_t* a, const int8_t* b, int8_t* c, const size_t l);
            #endif // __AVX2__

            template <size_t S>
            void add(const std::array<int8_t, S>& a, const std::array<int8_t, S>& b, std::array<int8_t, S>& c) {
                addBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // int8_t

        #pragma region // int16_t
            __attribute__((target("default")))
            inline void addBackend(const int16_t* a, const int16_t* b, int16_t* c, size_t l);

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void addBackend(const int16_t* a, const int16_t* b, int16_t* c, const size_t l);
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void addBackend(const int16_t* a, const int16_t* b, int16_t* c, const size_t l);
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void addBackend(const int16_t* a, const int16_t* b, int16_t* c, const size_t l);
            #endif // __AVX2__

            template <size_t S>
            void add(const std::array<int16_t, S>& a, const std::array<int16_t, S>& b, std::array<int16_t, S>& c) {
                addBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // int16_t

        #pragma region // int32_t
            __attribute__((target("default")))
            inline void addBackend(const int32_t* a, const int32_t* b, int32_t* c, size_t l);

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void addBackend(const int32_t* a, const int32_t* b, int32_t* c, const size_t l);
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void addBackend(const int32_t* a, const int32_t* b, int32_t* c, const size_t l);
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void addBackend(const int32_t* a, const int32_t* b, int32_t* c, const size_t l);
            #endif // __AVX2__

            template <size_t S>
            void add(const std::array<int32_t, S>& a, const std::array<int32_t, S>& b, std::array<int32_t, S>& c) {
                addBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // int32_t

        #pragma region // int64_t
            __attribute__((target("default")))
            inline void addBackend(const int64_t* a, const int64_t* b, int64_t* c, size_t l);

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void addBackend(const int64_t* a, const int64_t* b, int64_t* c, const size_t l);
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void addBackend(const int64_t* a, const int64_t* b, int64_t* c, const size_t l);
            #endif // __AVX2__

            template <size_t S>
            void add(const std::array<int64_t, S>& a, const std::array<int64_t, S>& b, std::array<int64_t, S>& c) {
                addBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // int64_t

        #pragma region // __int128_t
            __attribute__((target("default")))
            inline void addBackend(const __int128_t* a, const __int128_t* b, __int128_t* c, size_t l);

            template <size_t S>
            void add(const std::array<__int128_t, S>& a, const std::array<__int128_t, S>& b, std::array<__int128_t, S>& c) {
                addBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // __int128_t

        #pragma region // uint8_t
            __attribute__((target("default")))
            inline void addBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, size_t l);

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void addBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, const size_t l);
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void addBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, const size_t l);
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void addBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, const size_t l);
            #endif // __AVX2__

            template <size_t S>
            void add(const std::array<uint8_t, S>& a, const std::array<uint8_t, S>& b, std::array<uint8_t, S>& c) {
                addBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // uint8_t

        #pragma region // uint16_t
            __attribute__((target("default")))
            inline void addBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, size_t l);

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void addBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, const size_t l);
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void addBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, const size_t l);
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void addBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, const size_t l);
            #endif // __AVX2__

            template <size_t S>
            void add(const std::array<uint16_t, S>& a, const std::array<uint16_t, S>& b, std::array<uint16_t, S>& c) {
                addBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // uint16_t

        #pragma region // uint32_t
            __attribute__((target("default")))
            inline void addBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, size_t l);

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void addBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, const size_t l);
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void addBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, const size_t l);
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void addBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, const size_t l);
            #endif // __AVX2__

            template <size_t S>
            void add(const std::array<uint32_t, S>& a, const std::array<uint32_t, S>& b, std::array<uint32_t, S>& c) {
                addBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // uint32_t

        #pragma region // uint64_t
            __attribute__((target("default")))
            inline void addBackend(const uint64_t* a, const uint64_t* b, uint64_t* c, size_t l);

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void addBackend(const uint64_t* a, const uint64_t* b, uint64_t* c, const size_t l);
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void addBackend(const uint64_t* a, const uint64_t* b, uint64_t* c, const size_t l);
            #endif // __AVX2__

            template <size_t S>
            void add(const std::array<uint64_t, S>& a, const std::array<uint64_t, S>& b, std::array<uint64_t, S>& c) {
                addBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // uint64_t

        #pragma region // __uint128_t
            __attribute__((target("default")))
            inline void addBackend(const __uint128_t* a, const __uint128_t* b, __uint128_t* c, size_t l);

            template <size_t S>
            void add(const std::array<__uint128_t, S>& a, const std::array<__uint128_t, S>& b, std::array<__uint128_t, S>& c) {
                addBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // __uint128_t

        #pragma region // float
            __attribute__((target("default")))
            inline void addBackend(const float* a, const float* b, float* c, size_t l);

            #ifdef __SSE__
                __attribute__((target("sse")))
                inline void addBackend(const float* a, const float* b, float* c, const size_t l);
            #endif // __SSE__

            #ifdef __AVX__
                __attribute__((target("avx")))
                inline void addBackend(const float* a, const float* b, float* c, const size_t l);
            #endif // __AVX__

            template <size_t S>
            void add(const std::array<float, S>& a, const std::array<float, S>& b, std::array<float, S>& c) {
                addBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // float

        #pragma region // double
            __attribute__((target("default")))
            inline void addBackend(const double* a, const double* b, double* c, size_t l);

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void addBackend(const double* a, const double* b, double* c, const size_t l);
            #endif // __SSE2__

            #ifdef __AVX__
                __attribute__((target("avx")))
                inline void addBackend(const double* a, const double* b, double* c, const size_t l);
            #endif // __AVX__

            template <size_t S>
            void add(const std::array<double, S>& a, const std::array<double, S>& b, std::array<double, S>& c) {
                addBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // double

        #pragma region // long double
            __attribute__((target("default")))
            inline void addBackend(const long double* a, const long double* b, long double* c, size_t l);

            template <size_t S>
            void add(const std::array<long double, S>& a, const std::array<long double, S>& b, std::array<long double, S>& c) {
                addBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // long double

    
    #pragma region // sub
        #pragma region // int8_t
            __attribute__((target("default")))
            inline void subBackend(const int8_t* a, const int8_t* b, int8_t* c, size_t l);

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void subBackend(const int8_t* a, const int8_t* b, int8_t* c, const size_t l);
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void subBackend(const int8_t* a, const int8_t* b, int8_t* c, const size_t l);
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void subBackend(const int8_t* a, const int8_t* b, int8_t* c, const size_t l);
            #endif // __AVX2__

            template <size_t S>
            void sub(const std::array<int8_t, S>& a, const std::array<int8_t, S>& b, std::array<int8_t, S>& c) {
                subBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // int8_t

        #pragma region // int16_t
            __attribute__((target("default")))
            inline void subBackend(const int16_t* a, const int16_t* b, int16_t* c, size_t l);

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void subBackend(const int16_t* a, const int16_t* b, int16_t* c, const size_t l);
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void subBackend(const int16_t* a, const int16_t* b, int16_t* c, const size_t l);
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void subBackend(const int16_t* a, const int16_t* b, int16_t* c, const size_t l);
            #endif // __AVX2__

            template <size_t S>
            void sub(const std::array<int16_t, S>& a, const std::array<int16_t, S>& b, std::array<int16_t, S>& c) {
                subBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // int16_t

        #pragma region // int32_t
            __attribute__((target("default")))
            inline void subBackend(const int32_t* a, const int32_t* b, int32_t* c, size_t l);

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void subBackend(const int32_t* a, const int32_t* b, int32_t* c, const size_t l);
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void subBackend(const int32_t* a, const int32_t* b, int32_t* c, const size_t l);
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void subBackend(const int32_t* a, const int32_t* b, int32_t* c, const size_t l);
            #endif // __AVX2__

            template <size_t S>
            void sub(const std::array<int32_t, S>& a, const std::array<int32_t, S>& b, std::array<int32_t, S>& c) {
                subBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // int32_t

        #pragma region // int64_t
            __attribute__((target("default")))
            inline void subBackend(const int64_t* a, const int64_t* b, int64_t* c, size_t l);

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void subBackend(const int64_t* a, const int64_t* b, int64_t* c, const size_t l);
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void subBackend(const int64_t* a, const int64_t* b, int64_t* c, const size_t l);
            #endif // __AVX2__

            template <size_t S>
            void sub(const std::array<int64_t, S>& a, const std::array<int64_t, S>& b, std::array<int64_t, S>& c) {
                subBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // int64_t

        #pragma region // __int128_t
            __attribute__((target("default")))
            inline void subBackend(const __int128_t* a, const __int128_t* b, __int128_t* c, size_t l);

            template <size_t S>
            void sub(const std::array<__int128_t, S>& a, const std::array<__int128_t, S>& b, std::array<__int128_t, S>& c) {
                subBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // __int128_t

        #pragma region // uint8_t
            __attribute__((target("default")))
            inline void subBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, size_t l);

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void subBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, const size_t l);
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void subBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, const size_t l);
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void subBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, const size_t l);
            #endif // __AVX2__

            template <size_t S>
            void sub(const std::array<uint8_t, S>& a, const std::array<uint8_t, S>& b, std::array<uint8_t, S>& c) {
                subBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // uint8_t

        #pragma region // uint16_t
            __attribute__((target("default")))
            inline void subBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, size_t l);

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void subBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, const size_t l);
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void subBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, const size_t l);
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void subBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, const size_t l);
            #endif // __AVX2__

            template <size_t S>
            void sub(const std::array<uint16_t, S>& a, const std::array<uint16_t, S>& b, std::array<uint16_t, S>& c) {
                subBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // uint16_t

        #pragma region // uint32_t
            __attribute__((target("default")))
            inline void subBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, size_t l);

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void subBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, const size_t l);
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void subBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, const size_t l);
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void subBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, const size_t l);
            #endif // __AVX2__

            template <size_t S>
            void sub(const std::array<uint32_t, S>& a, const std::array<uint32_t, S>& b, std::array<uint32_t, S>& c) {
                subBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // uint32_t

        #pragma region // uint64_t
            __attribute__((target("default")))
            inline void subBackend(const uint64_t* a, const uint64_t* b, uint64_t* c, size_t l);

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void subBackend(const uint64_t* a, const uint64_t* b, uint64_t* c, const size_t l);
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void subBackend(const uint64_t* a, const uint64_t* b, uint64_t* c, const size_t l);
            #endif // __AVX2__

            template <size_t S>
            void sub(const std::array<uint64_t, S>& a, const std::array<uint64_t, S>& b, std::array<uint64_t, S>& c) {
                subBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // uint64_t

        #pragma region // __uint128_t
            __attribute__((target("default")))
            inline void subBackend(const __uint128_t* a, const __uint128_t* b, __uint128_t* c, size_t l);

            template <size_t S>
            void sub(const std::array<__uint128_t, S>& a, const std::array<__uint128_t, S>& b, std::array<__uint128_t, S>& c) {
                subBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // __uint128_t

        #pragma region // float
            __attribute__((target("default")))
            inline void subBackend(const float* a, const float* b, float* c, size_t l);

            #ifdef __SSE__
                __attribute__((target("sse")))
                inline void subBackend(const float* a, const float* b, float* c, const size_t l);
            #endif // __SSE__

            #ifdef __AVX__
                __attribute__((target("avx")))
                inline void subBackend(const float* a, const float* b, float* c, const size_t l);
            #endif // __AVX__

            template <size_t S>
            void sub(const std::array<float, S>& a, const std::array<float, S>& b, std::array<float, S>& c) {
                subBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // float

        #pragma region // double
            __attribute__((target("default")))
            inline void subBackend(const double* a, const double* b, double* c, size_t l);

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void subBackend(const double* a, const double* b, double* c, const size_t l);
            #endif // __SSE2__

            #ifdef __AVX__
                __attribute__((target("avx")))
                inline void subBackend(const double* a, const double* b, double* c, const size_t l);
            #endif // __AVX__

            template <size_t S>
            void sub(const std::array<double, S>& a, const std::array<double, S>& b, std::array<double, S>& c) {
                subBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // double

        #pragma region // long double
            __attribute__((target("default")))
            inline void subBackend(const long double* a, const long double* b, long double* c, size_t l);

            template <size_t S>
            void sub(const std::array<long double, S>& a, const std::array<long double, S>& b, std::array<long double, S>& c) {
                subBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // long double

    
    #pragma region // mul
        #pragma region // int8_t
            __attribute__((target("default")))
            inline void mulBackend(const int8_t* a, const int8_t* b, int8_t* c, size_t l);

            template <size_t S>
            void mul(const std::array<int8_t, S>& a, const std::array<int8_t, S>& b, std::array<int8_t, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // int8_t

        #pragma region // int16_t
            __attribute__((target("default")))
            inline void mulBackend(const int16_t* a, const int16_t* b, int16_t* c, size_t l);

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void mulBackend(const int16_t* a, const int16_t* b, int16_t* c, const size_t l);
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void mulBackend(const int16_t* a, const int16_t* b, int16_t* c, const size_t l);
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void mulBackend(const int16_t* a, const int16_t* b, int16_t* c, const size_t l);
            #endif // __AVX2__

            template <size_t S>
            void mul(const std::array<int16_t, S>& a, const std::array<int16_t, S>& b, std::array<int16_t, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // int16_t

        #pragma region // int32_t
            __attribute__((target("default")))
            inline void mulBackend(const int32_t* a, const int32_t* b, int32_t* c, size_t l);

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void mulBackend(const int32_t* a, const int32_t* b, int32_t* c, const size_t l);
            #endif // __AVX2__

            template <size_t S>
            void mul(const std::array<int32_t, S>& a, const std::array<int32_t, S>& b, std::array<int32_t, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // int32_t

        #pragma region // int64_t
            __attribute__((target("default")))
            inline void mulBackend(const int64_t* a, const int64_t* b, int64_t* c, size_t l);

            template <size_t S>
            void mul(const std::array<int64_t, S>& a, const std::array<int64_t, S>& b, std::array<int64_t, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // int64_t

        #pragma region // __int128_t
            __attribute__((target("default")))
            inline void mulBackend(const __int128_t* a, const __int128_t* b, __int128_t* c, size_t l);

            template <size_t S>
            void mul(const std::array<__int128_t, S>& a, const std::array<__int128_t, S>& b, std::array<__int128_t, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // __int128_t

        #pragma region // uint8_t
            __attribute__((target("default")))
            inline void mulBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, size_t l);

            template <size_t S>
            void mul(const std::array<uint8_t, S>& a, const std::array<uint8_t, S>& b, std::array<uint8_t, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // uint8_t

        #pragma region // uint16_t
            __attribute__((target("default")))
            inline void mulBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, size_t l);

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void mulBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, const size_t l);
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void mulBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, const size_t l);
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void mulBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, const size_t l);
            #endif // __AVX2__

            template <size_t S>
            void mul(const std::array<uint16_t, S>& a, const std::array<uint16_t, S>& b, std::array<uint16_t, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // uint16_t

        #pragma region // uint32_t
            __attribute__((target("default")))
            inline void mulBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, size_t l);

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void mulBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, const size_t l);
            #endif // __AVX2__

            template <size_t S>
            void mul(const std::array<uint32_t, S>& a, const std::array<uint32_t, S>& b, std::array<uint32_t, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // uint32_t

        #pragma region // uint64_t
            __attribute__((target("default")))
            inline void mulBackend(const uint64_t* a, const uint64_t* b, uint64_t* c, size_t l);

            template <size_t S>
            void mul(const std::array<uint64_t, S>& a, const std::array<uint64_t, S>& b, std::array<uint64_t, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // uint64_t

        #pragma region // __uint128_t
            __attribute__((target("default")))
            inline void mulBackend(const __uint128_t* a, const __uint128_t* b, __uint128_t* c, size_t l);

            template <size_t S>
            void mul(const std::array<__uint128_t, S>& a, const std::array<__uint128_t, S>& b, std::array<__uint128_t, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // __uint128_t

        #pragma region // float
            __attribute__((target("default")))
            inline void mulBackend(const float* a, const float* b, float* c, size_t l);

            #ifdef __SSE__
                __attribute__((target("sse")))
                inline void mulBackend(const float* a, const float* b, float* c, const size_t l);
            #endif // __SSE__

            #ifdef __AVX__
                __attribute__((target("avx")))
                inline void mulBackend(const float* a, const float* b, float* c, const size_t l);
            #endif // __AVX__

            template <size_t S>
            void mul(const std::array<float, S>& a, const std::array<float, S>& b, std::array<float, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // float

        #pragma region // double
            __attribute__((target("default")))
            inline void mulBackend(const double* a, const double* b, double* c, size_t l);

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void mulBackend(const double* a, const double* b, double* c, const size_t l);
            #endif // __SSE2__

            #ifdef __AVX__
                __attribute__((target("avx")))
                inline void mulBackend(const double* a, const double* b, double* c, const size_t l);
            #endif // __AVX__

            template <size_t S>
            void mul(const std::array<double, S>& a, const std::array<double, S>& b, std::array<double, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // double

        #pragma region // long double
            __attribute__((target("default")))
            inline void mulBackend(const long double* a, const long double* b, long double* c, size_t l);

            template <size_t S>
            void mul(const std::array<long double, S>& a, const std::array<long double, S>& b, std::array<long double, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // long double

    
    #pragma region // div
        #pragma region // int8_t
            __attribute__((target("default")))
            inline void divBackend(const int8_t* a, const int8_t* b, int8_t* c, size_t l);

            template <size_t S>
            void div(const std::array<int8_t, S>& a, const std::array<int8_t, S>& b, std::array<int8_t, S>& c) {
                divBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // int8_t

        #pragma region // int16_t
            __attribute__((target("default")))
            inline void divBackend(const int16_t* a, const int16_t* b, int16_t* c, size_t l);

            template <size_t S>
            void div(const std::array<int16_t, S>& a, const std::array<int16_t, S>& b, std::array<int16_t, S>& c) {
                divBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // int16_t

        #pragma region // int32_t
            __attribute__((target("default")))
            inline void divBackend(const int32_t* a, const int32_t* b, int32_t* c, size_t l);

            template <size_t S>
            void div(const std::array<int32_t, S>& a, const std::array<int32_t, S>& b, std::array<int32_t, S>& c) {
                divBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // int32_t

        #pragma region // int64_t
            __attribute__((target("default")))
            inline void divBackend(const int64_t* a, const int64_t* b, int64_t* c, size_t l);

            template <size_t S>
            void div(const std::array<int64_t, S>& a, const std::array<int64_t, S>& b, std::array<int64_t, S>& c) {
                divBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // int64_t

        #pragma region // __int128_t
            __attribute__((target("default")))
            inline void divBackend(const __int128_t* a, const __int128_t* b, __int128_t* c, size_t l);

            template <size_t S>
            void div(const std::array<__int128_t, S>& a, const std::array<__int128_t, S>& b, std::array<__int128_t, S>& c) {
                divBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // __int128_t

        #pragma region // uint8_t
            __attribute__((target("default")))
            inline void divBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, size_t l);

            template <size_t S>
            void div(const std::array<uint8_t, S>& a, const std::array<uint8_t, S>& b, std::array<uint8_t, S>& c) {
                divBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // uint8_t

        #pragma region // uint16_t
            __attribute__((target("default")))
            inline void divBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, size_t l);

            template <size_t S>
            void div(const std::array<uint16_t, S>& a, const std::array<uint16_t, S>& b, std::array<uint16_t, S>& c) {
                divBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // uint16_t

        #pragma region // uint32_t
            __attribute__((target("default")))
            inline void divBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, size_t l);

            template <size_t S>
            void div(const std::array<uint32_t, S>& a, const std::array<uint32_t, S>& b, std::array<uint32_t, S>& c) {
                divBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // uint32_t

        #pragma region // uint64_t
            __attribute__((target("default")))
            inline void divBackend(const uint64_t* a, const uint64_t* b, uint64_t* c, size_t l);

            template <size_t S>
            void div(const std::array<uint64_t, S>& a, const std::array<uint64_t, S>& b, std::array<uint64_t, S>& c) {
                divBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // uint64_t

        #pragma region // __uint128_t
            __attribute__((target("default")))
            inline void divBackend(const __uint128_t* a, const __uint128_t* b, __uint128_t* c, size_t l);

            template <size_t S>
            void div(const std::array<__uint128_t, S>& a, const std::array<__uint128_t, S>& b, std::array<__uint128_t, S>& c) {
                divBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // __uint128_t

        #pragma region // float
            __attribute__((target("default")))
            inline void divBackend(const float* a, const float* b, float* c, size_t l);

            #ifdef __SSE__
                __attribute__((target("sse")))
                inline void divBackend(const float* a, const float* b, float* c, const size_t l);
            #endif // __SSE__

            #ifdef __AVX__
                __attribute__((target("avx")))
                inline void divBackend(const float* a, const float* b, float* c, const size_t l);
            #endif // __AVX__

            template <size_t S>
            void div(const std::array<float, S>& a, const std::array<float, S>& b, std::array<float, S>& c) {
                divBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // float

        #pragma region // double
            __attribute__((target("default")))
            inline void divBackend(const double* a, const double* b, double* c, size_t l);

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void divBackend(const double* a, const double* b, double* c, const size_t l);
            #endif // __SSE2__

            #ifdef __AVX__
                __attribute__((target("avx")))
                inline void divBackend(const double* a, const double* b, double* c, const size_t l);
            #endif // __AVX__

            template <size_t S>
            void div(const std::array<double, S>& a, const std::array<double, S>& b, std::array<double, S>& c) {
                divBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // double

        #pragma region // long double
            __attribute__((target("default")))
            inline void divBackend(const long double* a, const long double* b, long double* c, size_t l);

            template <size_t S>
            void div(const std::array<long double, S>& a, const std::array<long double, S>& b, std::array<long double, S>& c) {
                divBackend(a.data(), b.data(), c.data(), S);
            }
        #pragma endregion // long double

} // namespace ezsimd