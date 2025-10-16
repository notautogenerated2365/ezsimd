#pragma once

#include <cstdint>
#include <vector>
#include <array>

namespace ezsimd {
    template <typename T, size_t N>
    constexpr inline size_t arrayLength(T (&)[N]) noexcept {
        return N;
    }
    
    #pragma region // add
        #pragma region // int8_t
            extern inline void addBackend(const int8_t* a, const int8_t* b, int8_t* c, size_t l);
            void add(const std::vector<int8_t>& a, const std::vector<int8_t>& b, std::vector<int8_t>& c);
            template <size_t S>
            void add(const std::array<int8_t, S>& a, const std::array<int8_t, S>& b, std::array<int8_t, S>& c) {
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            void add(const int8_t* a, const int8_t* b, int8_t* c, size_t l);
            #define ADD(a, b, c) add(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // int8_t

        #pragma region // int16_t
            extern inline void addBackend(const int16_t* a, const int16_t* b, int16_t* c, size_t l);
            void add(const std::vector<int16_t>& a, const std::vector<int16_t>& b, std::vector<int16_t>& c);
            template <size_t S>
            void add(const std::array<int16_t, S>& a, const std::array<int16_t, S>& b, std::array<int16_t, S>& c) {
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            void add(const int16_t* a, const int16_t* b, int16_t* c, size_t l);
            #define ADD(a, b, c) add(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // int16_t

        #pragma region // int32_t
            extern inline void addBackend(const int32_t* a, const int32_t* b, int32_t* c, size_t l);
            void add(const std::vector<int32_t>& a, const std::vector<int32_t>& b, std::vector<int32_t>& c);
            template <size_t S>
            void add(const std::array<int32_t, S>& a, const std::array<int32_t, S>& b, std::array<int32_t, S>& c) {
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            void add(const int32_t* a, const int32_t* b, int32_t* c, size_t l);
            #define ADD(a, b, c) add(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // int32_t

        #pragma region // int64_t
            extern inline void addBackend(const int64_t* a, const int64_t* b, int64_t* c, size_t l);
            void add(const std::vector<int64_t>& a, const std::vector<int64_t>& b, std::vector<int64_t>& c);
            template <size_t S>
            void add(const std::array<int64_t, S>& a, const std::array<int64_t, S>& b, std::array<int64_t, S>& c) {
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            void add(const int64_t* a, const int64_t* b, int64_t* c, size_t l);
            #define ADD(a, b, c) add(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // int64_t

        #pragma region // __int128_t
            extern inline void addBackend(const __int128_t* a, const __int128_t* b, __int128_t* c, size_t l);
            void add(const std::vector<__int128_t>& a, const std::vector<__int128_t>& b, std::vector<__int128_t>& c);
            template <size_t S>
            void add(const std::array<__int128_t, S>& a, const std::array<__int128_t, S>& b, std::array<__int128_t, S>& c) {
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            void add(const __int128_t* a, const __int128_t* b, __int128_t* c, size_t l);
            #define ADD(a, b, c) add(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // __int128_t

        #pragma region // uint8_t
            extern inline void addBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, size_t l);
            void add(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b, std::vector<uint8_t>& c);
            template <size_t S>
            void add(const std::array<uint8_t, S>& a, const std::array<uint8_t, S>& b, std::array<uint8_t, S>& c) {
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            void add(const uint8_t* a, const uint8_t* b, uint8_t* c, size_t l);
            #define ADD(a, b, c) add(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // uint8_t

        #pragma region // uint16_t
            extern inline void addBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, size_t l);
            void add(const std::vector<uint16_t>& a, const std::vector<uint16_t>& b, std::vector<uint16_t>& c);
            template <size_t S>
            void add(const std::array<uint16_t, S>& a, const std::array<uint16_t, S>& b, std::array<uint16_t, S>& c) {
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            void add(const uint16_t* a, const uint16_t* b, uint16_t* c, size_t l);
            #define ADD(a, b, c) add(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // uint16_t

        #pragma region // uint32_t
            extern inline void addBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, size_t l);
            void add(const std::vector<uint32_t>& a, const std::vector<uint32_t>& b, std::vector<uint32_t>& c);
            template <size_t S>
            void add(const std::array<uint32_t, S>& a, const std::array<uint32_t, S>& b, std::array<uint32_t, S>& c) {
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            void add(const uint32_t* a, const uint32_t* b, uint32_t* c, size_t l);
            #define ADD(a, b, c) add(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // uint32_t

        #pragma region // uint64_t
            extern inline void addBackend(const uint64_t* a, const uint64_t* b, uint64_t* c, size_t l);
            void add(const std::vector<uint64_t>& a, const std::vector<uint64_t>& b, std::vector<uint64_t>& c);
            template <size_t S>
            void add(const std::array<uint64_t, S>& a, const std::array<uint64_t, S>& b, std::array<uint64_t, S>& c) {
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            void add(const uint64_t* a, const uint64_t* b, uint64_t* c, size_t l);
            #define ADD(a, b, c) add(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // uint64_t

        #pragma region // __uint128_t
            extern inline void addBackend(const __uint128_t* a, const __uint128_t* b, __uint128_t* c, size_t l);
            void add(const std::vector<__uint128_t>& a, const std::vector<__uint128_t>& b, std::vector<__uint128_t>& c);
            template <size_t S>
            void add(const std::array<__uint128_t, S>& a, const std::array<__uint128_t, S>& b, std::array<__uint128_t, S>& c) {
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            void add(const __uint128_t* a, const __uint128_t* b, __uint128_t* c, size_t l);
            #define ADD(a, b, c) add(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // __uint128_t

        #pragma region // float
            extern inline void addBackend(const float* a, const float* b, float* c, size_t l);
            void add(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& c);
            template <size_t S>
            void add(const std::array<float, S>& a, const std::array<float, S>& b, std::array<float, S>& c) {
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            void add(const float* a, const float* b, float* c, size_t l);
            #define ADD(a, b, c) add(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // float

        #pragma region // double
            extern inline void addBackend(const double* a, const double* b, double* c, size_t l);
            void add(const std::vector<double>& a, const std::vector<double>& b, std::vector<double>& c);
            template <size_t S>
            void add(const std::array<double, S>& a, const std::array<double, S>& b, std::array<double, S>& c) {
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            void add(const double* a, const double* b, double* c, size_t l);
            #define ADD(a, b, c) add(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // double

        #pragma region // long double
            extern inline void addBackend(const long double* a, const long double* b, long double* c, size_t l);
            void add(const std::vector<long double>& a, const std::vector<long double>& b, std::vector<long double>& c);
            template <size_t S>
            void add(const std::array<long double, S>& a, const std::array<long double, S>& b, std::array<long double, S>& c) {
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            void add(const long double* a, const long double* b, long double* c, size_t l);
            #define ADD(a, b, c) add(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // long double
    #pragma endregion // add
    
    #pragma region // sub
        #pragma region // int8_t
            extern inline void subBackend(const int8_t* a, const int8_t* b, int8_t* c, size_t l);
            void sub(const std::vector<int8_t>& a, const std::vector<int8_t>& b, std::vector<int8_t>& c);
            template <size_t S>
            void sub(const std::array<int8_t, S>& a, const std::array<int8_t, S>& b, std::array<int8_t, S>& c) {
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            void sub(const int8_t* a, const int8_t* b, int8_t* c, size_t l);
            #define SUB(a, b, c) sub(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // int8_t

        #pragma region // int16_t
            extern inline void subBackend(const int16_t* a, const int16_t* b, int16_t* c, size_t l);
            void sub(const std::vector<int16_t>& a, const std::vector<int16_t>& b, std::vector<int16_t>& c);
            template <size_t S>
            void sub(const std::array<int16_t, S>& a, const std::array<int16_t, S>& b, std::array<int16_t, S>& c) {
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            void sub(const int16_t* a, const int16_t* b, int16_t* c, size_t l);
            #define SUB(a, b, c) sub(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // int16_t

        #pragma region // int32_t
            extern inline void subBackend(const int32_t* a, const int32_t* b, int32_t* c, size_t l);
            void sub(const std::vector<int32_t>& a, const std::vector<int32_t>& b, std::vector<int32_t>& c);
            template <size_t S>
            void sub(const std::array<int32_t, S>& a, const std::array<int32_t, S>& b, std::array<int32_t, S>& c) {
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            void sub(const int32_t* a, const int32_t* b, int32_t* c, size_t l);
            #define SUB(a, b, c) sub(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // int32_t

        #pragma region // int64_t
            extern inline void subBackend(const int64_t* a, const int64_t* b, int64_t* c, size_t l);
            void sub(const std::vector<int64_t>& a, const std::vector<int64_t>& b, std::vector<int64_t>& c);
            template <size_t S>
            void sub(const std::array<int64_t, S>& a, const std::array<int64_t, S>& b, std::array<int64_t, S>& c) {
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            void sub(const int64_t* a, const int64_t* b, int64_t* c, size_t l);
            #define SUB(a, b, c) sub(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // int64_t

        #pragma region // __int128_t
            extern inline void subBackend(const __int128_t* a, const __int128_t* b, __int128_t* c, size_t l);
            void sub(const std::vector<__int128_t>& a, const std::vector<__int128_t>& b, std::vector<__int128_t>& c);
            template <size_t S>
            void sub(const std::array<__int128_t, S>& a, const std::array<__int128_t, S>& b, std::array<__int128_t, S>& c) {
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            void sub(const __int128_t* a, const __int128_t* b, __int128_t* c, size_t l);
            #define SUB(a, b, c) sub(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // __int128_t

        #pragma region // uint8_t
            extern inline void subBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, size_t l);
            void sub(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b, std::vector<uint8_t>& c);
            template <size_t S>
            void sub(const std::array<uint8_t, S>& a, const std::array<uint8_t, S>& b, std::array<uint8_t, S>& c) {
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            void sub(const uint8_t* a, const uint8_t* b, uint8_t* c, size_t l);
            #define SUB(a, b, c) sub(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // uint8_t

        #pragma region // uint16_t
            extern inline void subBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, size_t l);
            void sub(const std::vector<uint16_t>& a, const std::vector<uint16_t>& b, std::vector<uint16_t>& c);
            template <size_t S>
            void sub(const std::array<uint16_t, S>& a, const std::array<uint16_t, S>& b, std::array<uint16_t, S>& c) {
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            void sub(const uint16_t* a, const uint16_t* b, uint16_t* c, size_t l);
            #define SUB(a, b, c) sub(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // uint16_t

        #pragma region // uint32_t
            extern inline void subBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, size_t l);
            void sub(const std::vector<uint32_t>& a, const std::vector<uint32_t>& b, std::vector<uint32_t>& c);
            template <size_t S>
            void sub(const std::array<uint32_t, S>& a, const std::array<uint32_t, S>& b, std::array<uint32_t, S>& c) {
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            void sub(const uint32_t* a, const uint32_t* b, uint32_t* c, size_t l);
            #define SUB(a, b, c) sub(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // uint32_t

        #pragma region // uint64_t
            extern inline void subBackend(const uint64_t* a, const uint64_t* b, uint64_t* c, size_t l);
            void sub(const std::vector<uint64_t>& a, const std::vector<uint64_t>& b, std::vector<uint64_t>& c);
            template <size_t S>
            void sub(const std::array<uint64_t, S>& a, const std::array<uint64_t, S>& b, std::array<uint64_t, S>& c) {
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            void sub(const uint64_t* a, const uint64_t* b, uint64_t* c, size_t l);
            #define SUB(a, b, c) sub(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // uint64_t

        #pragma region // __uint128_t
            extern inline void subBackend(const __uint128_t* a, const __uint128_t* b, __uint128_t* c, size_t l);
            void sub(const std::vector<__uint128_t>& a, const std::vector<__uint128_t>& b, std::vector<__uint128_t>& c);
            template <size_t S>
            void sub(const std::array<__uint128_t, S>& a, const std::array<__uint128_t, S>& b, std::array<__uint128_t, S>& c) {
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            void sub(const __uint128_t* a, const __uint128_t* b, __uint128_t* c, size_t l);
            #define SUB(a, b, c) sub(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // __uint128_t

        #pragma region // float
            extern inline void subBackend(const float* a, const float* b, float* c, size_t l);
            void sub(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& c);
            template <size_t S>
            void sub(const std::array<float, S>& a, const std::array<float, S>& b, std::array<float, S>& c) {
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            void sub(const float* a, const float* b, float* c, size_t l);
            #define SUB(a, b, c) sub(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // float

        #pragma region // double
            extern inline void subBackend(const double* a, const double* b, double* c, size_t l);
            void sub(const std::vector<double>& a, const std::vector<double>& b, std::vector<double>& c);
            template <size_t S>
            void sub(const std::array<double, S>& a, const std::array<double, S>& b, std::array<double, S>& c) {
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            void sub(const double* a, const double* b, double* c, size_t l);
            #define SUB(a, b, c) sub(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // double

        #pragma region // long double
            extern inline void subBackend(const long double* a, const long double* b, long double* c, size_t l);
            void sub(const std::vector<long double>& a, const std::vector<long double>& b, std::vector<long double>& c);
            template <size_t S>
            void sub(const std::array<long double, S>& a, const std::array<long double, S>& b, std::array<long double, S>& c) {
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            void sub(const long double* a, const long double* b, long double* c, size_t l);
            #define SUB(a, b, c) sub(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // long double
    #pragma endregion // sub
    
    #pragma region // mul
        #pragma region // int8_t
            extern inline void mulBackend(const int8_t* a, const int8_t* b, int8_t* c, size_t l);
            void mul(const std::vector<int8_t>& a, const std::vector<int8_t>& b, std::vector<int8_t>& c);
            template <size_t S>
            void mul(const std::array<int8_t, S>& a, const std::array<int8_t, S>& b, std::array<int8_t, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            void mul(const int8_t* a, const int8_t* b, int8_t* c, size_t l);
            #define MUL(a, b, c) mul(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // int8_t

        #pragma region // int16_t
            extern inline void mulBackend(const int16_t* a, const int16_t* b, int16_t* c, size_t l);
            void mul(const std::vector<int16_t>& a, const std::vector<int16_t>& b, std::vector<int16_t>& c);
            template <size_t S>
            void mul(const std::array<int16_t, S>& a, const std::array<int16_t, S>& b, std::array<int16_t, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            void mul(const int16_t* a, const int16_t* b, int16_t* c, size_t l);
            #define MUL(a, b, c) mul(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // int16_t

        #pragma region // int32_t
            extern inline void mulBackend(const int32_t* a, const int32_t* b, int32_t* c, size_t l);
            void mul(const std::vector<int32_t>& a, const std::vector<int32_t>& b, std::vector<int32_t>& c);
            template <size_t S>
            void mul(const std::array<int32_t, S>& a, const std::array<int32_t, S>& b, std::array<int32_t, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            void mul(const int32_t* a, const int32_t* b, int32_t* c, size_t l);
            #define MUL(a, b, c) mul(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // int32_t

        #pragma region // int64_t
            extern inline void mulBackend(const int64_t* a, const int64_t* b, int64_t* c, size_t l);
            void mul(const std::vector<int64_t>& a, const std::vector<int64_t>& b, std::vector<int64_t>& c);
            template <size_t S>
            void mul(const std::array<int64_t, S>& a, const std::array<int64_t, S>& b, std::array<int64_t, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            void mul(const int64_t* a, const int64_t* b, int64_t* c, size_t l);
            #define MUL(a, b, c) mul(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // int64_t

        #pragma region // __int128_t
            extern inline void mulBackend(const __int128_t* a, const __int128_t* b, __int128_t* c, size_t l);
            void mul(const std::vector<__int128_t>& a, const std::vector<__int128_t>& b, std::vector<__int128_t>& c);
            template <size_t S>
            void mul(const std::array<__int128_t, S>& a, const std::array<__int128_t, S>& b, std::array<__int128_t, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            void mul(const __int128_t* a, const __int128_t* b, __int128_t* c, size_t l);
            #define MUL(a, b, c) mul(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // __int128_t

        #pragma region // uint8_t
            extern inline void mulBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, size_t l);
            void mul(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b, std::vector<uint8_t>& c);
            template <size_t S>
            void mul(const std::array<uint8_t, S>& a, const std::array<uint8_t, S>& b, std::array<uint8_t, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            void mul(const uint8_t* a, const uint8_t* b, uint8_t* c, size_t l);
            #define MUL(a, b, c) mul(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // uint8_t

        #pragma region // uint16_t
            extern inline void mulBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, size_t l);
            void mul(const std::vector<uint16_t>& a, const std::vector<uint16_t>& b, std::vector<uint16_t>& c);
            template <size_t S>
            void mul(const std::array<uint16_t, S>& a, const std::array<uint16_t, S>& b, std::array<uint16_t, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            void mul(const uint16_t* a, const uint16_t* b, uint16_t* c, size_t l);
            #define MUL(a, b, c) mul(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // uint16_t

        #pragma region // uint32_t
            extern inline void mulBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, size_t l);
            void mul(const std::vector<uint32_t>& a, const std::vector<uint32_t>& b, std::vector<uint32_t>& c);
            template <size_t S>
            void mul(const std::array<uint32_t, S>& a, const std::array<uint32_t, S>& b, std::array<uint32_t, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            void mul(const uint32_t* a, const uint32_t* b, uint32_t* c, size_t l);
            #define MUL(a, b, c) mul(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // uint32_t

        #pragma region // uint64_t
            extern inline void mulBackend(const uint64_t* a, const uint64_t* b, uint64_t* c, size_t l);
            void mul(const std::vector<uint64_t>& a, const std::vector<uint64_t>& b, std::vector<uint64_t>& c);
            template <size_t S>
            void mul(const std::array<uint64_t, S>& a, const std::array<uint64_t, S>& b, std::array<uint64_t, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            void mul(const uint64_t* a, const uint64_t* b, uint64_t* c, size_t l);
            #define MUL(a, b, c) mul(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // uint64_t

        #pragma region // __uint128_t
            extern inline void mulBackend(const __uint128_t* a, const __uint128_t* b, __uint128_t* c, size_t l);
            void mul(const std::vector<__uint128_t>& a, const std::vector<__uint128_t>& b, std::vector<__uint128_t>& c);
            template <size_t S>
            void mul(const std::array<__uint128_t, S>& a, const std::array<__uint128_t, S>& b, std::array<__uint128_t, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            void mul(const __uint128_t* a, const __uint128_t* b, __uint128_t* c, size_t l);
            #define MUL(a, b, c) mul(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // __uint128_t

        #pragma region // float
            extern inline void mulBackend(const float* a, const float* b, float* c, size_t l);
            void mul(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& c);
            template <size_t S>
            void mul(const std::array<float, S>& a, const std::array<float, S>& b, std::array<float, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            void mul(const float* a, const float* b, float* c, size_t l);
            #define MUL(a, b, c) mul(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // float

        #pragma region // double
            extern inline void mulBackend(const double* a, const double* b, double* c, size_t l);
            void mul(const std::vector<double>& a, const std::vector<double>& b, std::vector<double>& c);
            template <size_t S>
            void mul(const std::array<double, S>& a, const std::array<double, S>& b, std::array<double, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            void mul(const double* a, const double* b, double* c, size_t l);
            #define MUL(a, b, c) mul(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // double

        #pragma region // long double
            extern inline void mulBackend(const long double* a, const long double* b, long double* c, size_t l);
            void mul(const std::vector<long double>& a, const std::vector<long double>& b, std::vector<long double>& c);
            template <size_t S>
            void mul(const std::array<long double, S>& a, const std::array<long double, S>& b, std::array<long double, S>& c) {
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            void mul(const long double* a, const long double* b, long double* c, size_t l);
            #define MUL(a, b, c) mul(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // long double
    #pragma endregion // mul
    
    #pragma region // div
        #pragma region // int8_t
            extern inline void divBackend(const int8_t* a, const int8_t* b, int8_t* c, size_t l);
            void div(const std::vector<int8_t>& a, const std::vector<int8_t>& b, std::vector<int8_t>& c);
            template <size_t S>
            void div(const std::array<int8_t, S>& a, const std::array<int8_t, S>& b, std::array<int8_t, S>& c) {
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            void div(const int8_t* a, const int8_t* b, int8_t* c, size_t l);
            #define DIV(a, b, c) div(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // int8_t

        #pragma region // int16_t
            extern inline void divBackend(const int16_t* a, const int16_t* b, int16_t* c, size_t l);
            void div(const std::vector<int16_t>& a, const std::vector<int16_t>& b, std::vector<int16_t>& c);
            template <size_t S>
            void div(const std::array<int16_t, S>& a, const std::array<int16_t, S>& b, std::array<int16_t, S>& c) {
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            void div(const int16_t* a, const int16_t* b, int16_t* c, size_t l);
            #define DIV(a, b, c) div(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // int16_t

        #pragma region // int32_t
            extern inline void divBackend(const int32_t* a, const int32_t* b, int32_t* c, size_t l);
            void div(const std::vector<int32_t>& a, const std::vector<int32_t>& b, std::vector<int32_t>& c);
            template <size_t S>
            void div(const std::array<int32_t, S>& a, const std::array<int32_t, S>& b, std::array<int32_t, S>& c) {
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            void div(const int32_t* a, const int32_t* b, int32_t* c, size_t l);
            #define DIV(a, b, c) div(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // int32_t

        #pragma region // int64_t
            extern inline void divBackend(const int64_t* a, const int64_t* b, int64_t* c, size_t l);
            void div(const std::vector<int64_t>& a, const std::vector<int64_t>& b, std::vector<int64_t>& c);
            template <size_t S>
            void div(const std::array<int64_t, S>& a, const std::array<int64_t, S>& b, std::array<int64_t, S>& c) {
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            void div(const int64_t* a, const int64_t* b, int64_t* c, size_t l);
            #define DIV(a, b, c) div(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // int64_t

        #pragma region // __int128_t
            extern inline void divBackend(const __int128_t* a, const __int128_t* b, __int128_t* c, size_t l);
            void div(const std::vector<__int128_t>& a, const std::vector<__int128_t>& b, std::vector<__int128_t>& c);
            template <size_t S>
            void div(const std::array<__int128_t, S>& a, const std::array<__int128_t, S>& b, std::array<__int128_t, S>& c) {
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            void div(const __int128_t* a, const __int128_t* b, __int128_t* c, size_t l);
            #define DIV(a, b, c) div(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // __int128_t

        #pragma region // uint8_t
            extern inline void divBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, size_t l);
            void div(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b, std::vector<uint8_t>& c);
            template <size_t S>
            void div(const std::array<uint8_t, S>& a, const std::array<uint8_t, S>& b, std::array<uint8_t, S>& c) {
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            void div(const uint8_t* a, const uint8_t* b, uint8_t* c, size_t l);
            #define DIV(a, b, c) div(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // uint8_t

        #pragma region // uint16_t
            extern inline void divBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, size_t l);
            void div(const std::vector<uint16_t>& a, const std::vector<uint16_t>& b, std::vector<uint16_t>& c);
            template <size_t S>
            void div(const std::array<uint16_t, S>& a, const std::array<uint16_t, S>& b, std::array<uint16_t, S>& c) {
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            void div(const uint16_t* a, const uint16_t* b, uint16_t* c, size_t l);
            #define DIV(a, b, c) div(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // uint16_t

        #pragma region // uint32_t
            extern inline void divBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, size_t l);
            void div(const std::vector<uint32_t>& a, const std::vector<uint32_t>& b, std::vector<uint32_t>& c);
            template <size_t S>
            void div(const std::array<uint32_t, S>& a, const std::array<uint32_t, S>& b, std::array<uint32_t, S>& c) {
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            void div(const uint32_t* a, const uint32_t* b, uint32_t* c, size_t l);
            #define DIV(a, b, c) div(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // uint32_t

        #pragma region // uint64_t
            extern inline void divBackend(const uint64_t* a, const uint64_t* b, uint64_t* c, size_t l);
            void div(const std::vector<uint64_t>& a, const std::vector<uint64_t>& b, std::vector<uint64_t>& c);
            template <size_t S>
            void div(const std::array<uint64_t, S>& a, const std::array<uint64_t, S>& b, std::array<uint64_t, S>& c) {
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            void div(const uint64_t* a, const uint64_t* b, uint64_t* c, size_t l);
            #define DIV(a, b, c) div(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // uint64_t

        #pragma region // __uint128_t
            extern inline void divBackend(const __uint128_t* a, const __uint128_t* b, __uint128_t* c, size_t l);
            void div(const std::vector<__uint128_t>& a, const std::vector<__uint128_t>& b, std::vector<__uint128_t>& c);
            template <size_t S>
            void div(const std::array<__uint128_t, S>& a, const std::array<__uint128_t, S>& b, std::array<__uint128_t, S>& c) {
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            void div(const __uint128_t* a, const __uint128_t* b, __uint128_t* c, size_t l);
            #define DIV(a, b, c) div(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // __uint128_t

        #pragma region // float
            extern inline void divBackend(const float* a, const float* b, float* c, size_t l);
            void div(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& c);
            template <size_t S>
            void div(const std::array<float, S>& a, const std::array<float, S>& b, std::array<float, S>& c) {
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            void div(const float* a, const float* b, float* c, size_t l);
            #define DIV(a, b, c) div(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // float

        #pragma region // double
            extern inline void divBackend(const double* a, const double* b, double* c, size_t l);
            void div(const std::vector<double>& a, const std::vector<double>& b, std::vector<double>& c);
            template <size_t S>
            void div(const std::array<double, S>& a, const std::array<double, S>& b, std::array<double, S>& c) {
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            void div(const double* a, const double* b, double* c, size_t l);
            #define DIV(a, b, c) div(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // double

        #pragma region // long double
            extern inline void divBackend(const long double* a, const long double* b, long double* c, size_t l);
            void div(const std::vector<long double>& a, const std::vector<long double>& b, std::vector<long double>& c);
            template <size_t S>
            void div(const std::array<long double, S>& a, const std::array<long double, S>& b, std::array<long double, S>& c) {
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            void div(const long double* a, const long double* b, long double* c, size_t l);
            #define DIV(a, b, c) div(a, b, c, ezsimd::arrayLength(a))
        #pragma endregion // long double
    #pragma endregion // div
} // namespace ezsimd