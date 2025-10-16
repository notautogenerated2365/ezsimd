#pragma once

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
#elif defined(__SSE2__)
    #include <emmintrin.h>
#elif defined(__SSE__)
    #include <xmmintrin.h>
#elif defined(__MMX__)
    #include <mmintrin.h>
#endif

namespace ezsimd {
    template <typename T>
    bool isAligned(const T* ptr, size_t alignment) {
        return reinterpret_cast<std::uintptr_t>(static_cast<const void*>(ptr)) % alignment == 0;
    }
    
    #pragma region // add
        #pragma region // int8_t
            __attribute__((target("default")))
            inline void addBackend(const int8_t* a, const int8_t* b, int8_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") add\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void addBackend(const int8_t* a, const int8_t* b, int8_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"mmx\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m64 vec_a;
                    __m64 vec_b;
                    __m64 vec_c;
                    const bool isAlignedA = isAligned(a, 8);
                    const bool isAlignedB = isAligned(b, 8);
                    const bool isAlignedC = isAligned(c, 8);
                    
                    for (; i + 7 < l; i += 8) {
                        if (isAlignedA) {
                            vec_a = [](const int8_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(a + i);
                        } else {
                            vec_a = [](const int8_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int8_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(b + i);
                        } else {
                            vec_b = [](const int8_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(b + i);
                        }
                        
                        vec_c = _mm_add_pi8(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int8_t *ptr, const __m64 vec) {*reinterpret_cast<__m64*>(ptr) = vec;}(c + i, vec_c);
                        } else {
                            [](int8_t *ptr, const __m64 vec) {std::memcpy(ptr, &vec, sizeof(__m64));}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                    
                    _mm_empty();
                }
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void addBackend(const int8_t* a, const int8_t* b, int8_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse2\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m128i vec_a;
                    __m128i vec_b;
                    __m128i vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 15 < l; i += 16) {
                        if (isAlignedA) {
                            vec_a = [](const int8_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const int8_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int8_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const int8_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm_add_epi8(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int8_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](int8_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void addBackend(const int8_t* a, const int8_t* b, int8_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx2\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m256i vec_a;
                    __m256i vec_b;
                    __m256i vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 31 < l; i += 32) {
                        if (isAlignedA) {
                            vec_a = [](const int8_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const int8_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int8_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const int8_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm256_add_epi8(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int8_t* ptr, const __m256i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](int8_t* ptr, const __m256i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX2__

            void add(const std::vector<int8_t>& a, const std::vector<int8_t>& b, std::vector<int8_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void add(const int8_t* a, const int8_t* b, int8_t* c, size_t l) {
                addBackend(a, b, c, l);
            }
        #pragma endregion // int8_t

        #pragma region // int16_t
            __attribute__((target("default")))
            inline void addBackend(const int16_t* a, const int16_t* b, int16_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") add\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void addBackend(const int16_t* a, const int16_t* b, int16_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"mmx\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m64 vec_a;
                    __m64 vec_b;
                    __m64 vec_c;
                    const bool isAlignedA = isAligned(a, 8);
                    const bool isAlignedB = isAligned(b, 8);
                    const bool isAlignedC = isAligned(c, 8);
                    
                    for (; i + 3 < l; i += 4) {
                        if (isAlignedA) {
                            vec_a = [](const int16_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(a + i);
                        } else {
                            vec_a = [](const int16_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int16_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(b + i);
                        } else {
                            vec_b = [](const int16_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(b + i);
                        }
                        
                        vec_c = _mm_add_pi16(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int16_t *ptr, const __m64 vec) {*reinterpret_cast<__m64*>(ptr) = vec;}(c + i, vec_c);
                        } else {
                            [](int16_t *ptr, const __m64 vec) {std::memcpy(ptr, &vec, sizeof(__m64));}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                    
                    _mm_empty();
                }
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void addBackend(const int16_t* a, const int16_t* b, int16_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse2\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m128i vec_a;
                    __m128i vec_b;
                    __m128i vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 7 < l; i += 8) {
                        if (isAlignedA) {
                            vec_a = [](const int16_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const int16_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int16_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const int16_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm_add_epi16(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int16_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](int16_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void addBackend(const int16_t* a, const int16_t* b, int16_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx2\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m256i vec_a;
                    __m256i vec_b;
                    __m256i vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 15 < l; i += 16) {
                        if (isAlignedA) {
                            vec_a = [](const int16_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const int16_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int16_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const int16_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm256_add_epi16(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int16_t* ptr, const __m256i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](int16_t* ptr, const __m256i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX2__

            void add(const std::vector<int16_t>& a, const std::vector<int16_t>& b, std::vector<int16_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void add(const int16_t* a, const int16_t* b, int16_t* c, size_t l) {
                addBackend(a, b, c, l);
            }
        #pragma endregion // int16_t

        #pragma region // int32_t
            __attribute__((target("default")))
            inline void addBackend(const int32_t* a, const int32_t* b, int32_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") add\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void addBackend(const int32_t* a, const int32_t* b, int32_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"mmx\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m64 vec_a;
                    __m64 vec_b;
                    __m64 vec_c;
                    const bool isAlignedA = isAligned(a, 8);
                    const bool isAlignedB = isAligned(b, 8);
                    const bool isAlignedC = isAligned(c, 8);
                    
                    for (; i + 1 < l; i += 2) {
                        if (isAlignedA) {
                            vec_a = [](const int32_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(a + i);
                        } else {
                            vec_a = [](const int32_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int32_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(b + i);
                        } else {
                            vec_b = [](const int32_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(b + i);
                        }
                        
                        vec_c = _mm_add_pi32(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int32_t *ptr, const __m64 vec) {*reinterpret_cast<__m64*>(ptr) = vec;}(c + i, vec_c);
                        } else {
                            [](int32_t *ptr, const __m64 vec) {std::memcpy(ptr, &vec, sizeof(__m64));}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                    
                    _mm_empty();
                }
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void addBackend(const int32_t* a, const int32_t* b, int32_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse2\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m128i vec_a;
                    __m128i vec_b;
                    __m128i vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 3 < l; i += 4) {
                        if (isAlignedA) {
                            vec_a = [](const int32_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const int32_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int32_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const int32_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm_add_epi32(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int32_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](int32_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void addBackend(const int32_t* a, const int32_t* b, int32_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx2\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m256i vec_a;
                    __m256i vec_b;
                    __m256i vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 7 < l; i += 8) {
                        if (isAlignedA) {
                            vec_a = [](const int32_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const int32_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int32_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const int32_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm256_add_epi32(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int32_t* ptr, const __m256i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](int32_t* ptr, const __m256i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX2__

            void add(const std::vector<int32_t>& a, const std::vector<int32_t>& b, std::vector<int32_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void add(const int32_t* a, const int32_t* b, int32_t* c, size_t l) {
                addBackend(a, b, c, l);
            }
        #pragma endregion // int32_t

        #pragma region // int64_t
            __attribute__((target("default")))
            inline void addBackend(const int64_t* a, const int64_t* b, int64_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") add\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void addBackend(const int64_t* a, const int64_t* b, int64_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse2\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m128i vec_a;
                    __m128i vec_b;
                    __m128i vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 1 < l; i += 2) {
                        if (isAlignedA) {
                            vec_a = [](const int64_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const int64_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int64_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const int64_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm_add_epi64(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int64_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](int64_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void addBackend(const int64_t* a, const int64_t* b, int64_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx2\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m256i vec_a;
                    __m256i vec_b;
                    __m256i vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 3 < l; i += 4) {
                        if (isAlignedA) {
                            vec_a = [](const int64_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const int64_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int64_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const int64_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm256_add_epi64(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int64_t* ptr, const __m256i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](int64_t* ptr, const __m256i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX2__

            void add(const std::vector<int64_t>& a, const std::vector<int64_t>& b, std::vector<int64_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void add(const int64_t* a, const int64_t* b, int64_t* c, size_t l) {
                addBackend(a, b, c, l);
            }
        #pragma endregion // int64_t

        #pragma region // __int128_t
            __attribute__((target("default")))
            inline void addBackend(const __int128_t* a, const __int128_t* b, __int128_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") add\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void add(const std::vector<__int128_t>& a, const std::vector<__int128_t>& b, std::vector<__int128_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void add(const __int128_t* a, const __int128_t* b, __int128_t* c, size_t l) {
                addBackend(a, b, c, l);
            }
        #pragma endregion // __int128_t

        #pragma region // uint8_t
            __attribute__((target("default")))
            inline void addBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") add\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void addBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"mmx\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m64 vec_a;
                    __m64 vec_b;
                    __m64 vec_c;
                    const bool isAlignedA = isAligned(a, 8);
                    const bool isAlignedB = isAligned(b, 8);
                    const bool isAlignedC = isAligned(c, 8);
                    
                    for (; i + 7 < l; i += 8) {
                        if (isAlignedA) {
                            vec_a = [](const uint8_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(a + i);
                        } else {
                            vec_a = [](const uint8_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint8_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(b + i);
                        } else {
                            vec_b = [](const uint8_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(b + i);
                        }
                        
                        vec_c = _mm_add_pi8(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint8_t *ptr, const __m64 vec) {*reinterpret_cast<__m64*>(ptr) = vec;}(c + i, vec_c);
                        } else {
                            [](uint8_t *ptr, const __m64 vec) {std::memcpy(ptr, &vec, sizeof(__m64));}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                    
                    _mm_empty();
                }
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void addBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse2\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m128i vec_a;
                    __m128i vec_b;
                    __m128i vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 15 < l; i += 16) {
                        if (isAlignedA) {
                            vec_a = [](const uint8_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const uint8_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint8_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const uint8_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm_add_epi8(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint8_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](uint8_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void addBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx2\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m256i vec_a;
                    __m256i vec_b;
                    __m256i vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 31 < l; i += 32) {
                        if (isAlignedA) {
                            vec_a = [](const uint8_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const uint8_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint8_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const uint8_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm256_add_epi8(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint8_t* ptr, const __m256i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](uint8_t* ptr, const __m256i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX2__

            void add(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b, std::vector<uint8_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void add(const uint8_t* a, const uint8_t* b, uint8_t* c, size_t l) {
                addBackend(a, b, c, l);
            }
        #pragma endregion // uint8_t

        #pragma region // uint16_t
            __attribute__((target("default")))
            inline void addBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") add\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void addBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"mmx\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m64 vec_a;
                    __m64 vec_b;
                    __m64 vec_c;
                    const bool isAlignedA = isAligned(a, 8);
                    const bool isAlignedB = isAligned(b, 8);
                    const bool isAlignedC = isAligned(c, 8);
                    
                    for (; i + 3 < l; i += 4) {
                        if (isAlignedA) {
                            vec_a = [](const uint16_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(a + i);
                        } else {
                            vec_a = [](const uint16_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint16_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(b + i);
                        } else {
                            vec_b = [](const uint16_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(b + i);
                        }
                        
                        vec_c = _mm_add_pi16(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint16_t *ptr, const __m64 vec) {*reinterpret_cast<__m64*>(ptr) = vec;}(c + i, vec_c);
                        } else {
                            [](uint16_t *ptr, const __m64 vec) {std::memcpy(ptr, &vec, sizeof(__m64));}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                    
                    _mm_empty();
                }
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void addBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse2\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m128i vec_a;
                    __m128i vec_b;
                    __m128i vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 7 < l; i += 8) {
                        if (isAlignedA) {
                            vec_a = [](const uint16_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const uint16_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint16_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const uint16_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm_add_epi16(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint16_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](uint16_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void addBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx2\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m256i vec_a;
                    __m256i vec_b;
                    __m256i vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 15 < l; i += 16) {
                        if (isAlignedA) {
                            vec_a = [](const uint16_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const uint16_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint16_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const uint16_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm256_add_epi16(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint16_t* ptr, const __m256i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](uint16_t* ptr, const __m256i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX2__

            void add(const std::vector<uint16_t>& a, const std::vector<uint16_t>& b, std::vector<uint16_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void add(const uint16_t* a, const uint16_t* b, uint16_t* c, size_t l) {
                addBackend(a, b, c, l);
            }
        #pragma endregion // uint16_t

        #pragma region // uint32_t
            __attribute__((target("default")))
            inline void addBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") add\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void addBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"mmx\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m64 vec_a;
                    __m64 vec_b;
                    __m64 vec_c;
                    const bool isAlignedA = isAligned(a, 8);
                    const bool isAlignedB = isAligned(b, 8);
                    const bool isAlignedC = isAligned(c, 8);
                    
                    for (; i + 1 < l; i += 2) {
                        if (isAlignedA) {
                            vec_a = [](const uint32_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(a + i);
                        } else {
                            vec_a = [](const uint32_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint32_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(b + i);
                        } else {
                            vec_b = [](const uint32_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(b + i);
                        }
                        
                        vec_c = _mm_add_pi32(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint32_t *ptr, const __m64 vec) {*reinterpret_cast<__m64*>(ptr) = vec;}(c + i, vec_c);
                        } else {
                            [](uint32_t *ptr, const __m64 vec) {std::memcpy(ptr, &vec, sizeof(__m64));}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                    
                    _mm_empty();
                }
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void addBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse2\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m128i vec_a;
                    __m128i vec_b;
                    __m128i vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 3 < l; i += 4) {
                        if (isAlignedA) {
                            vec_a = [](const uint32_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const uint32_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint32_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const uint32_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm_add_epi32(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint32_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](uint32_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void addBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx2\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m256i vec_a;
                    __m256i vec_b;
                    __m256i vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 7 < l; i += 8) {
                        if (isAlignedA) {
                            vec_a = [](const uint32_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const uint32_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint32_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const uint32_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm256_add_epi32(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint32_t* ptr, const __m256i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](uint32_t* ptr, const __m256i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX2__

            void add(const std::vector<uint32_t>& a, const std::vector<uint32_t>& b, std::vector<uint32_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void add(const uint32_t* a, const uint32_t* b, uint32_t* c, size_t l) {
                addBackend(a, b, c, l);
            }
        #pragma endregion // uint32_t

        #pragma region // uint64_t
            __attribute__((target("default")))
            inline void addBackend(const uint64_t* a, const uint64_t* b, uint64_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") add\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void addBackend(const uint64_t* a, const uint64_t* b, uint64_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse2\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m128i vec_a;
                    __m128i vec_b;
                    __m128i vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 1 < l; i += 2) {
                        if (isAlignedA) {
                            vec_a = [](const uint64_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const uint64_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint64_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const uint64_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm_add_epi64(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint64_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](uint64_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void addBackend(const uint64_t* a, const uint64_t* b, uint64_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx2\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m256i vec_a;
                    __m256i vec_b;
                    __m256i vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 3 < l; i += 4) {
                        if (isAlignedA) {
                            vec_a = [](const uint64_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const uint64_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint64_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const uint64_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm256_add_epi64(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint64_t* ptr, const __m256i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](uint64_t* ptr, const __m256i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX2__

            void add(const std::vector<uint64_t>& a, const std::vector<uint64_t>& b, std::vector<uint64_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void add(const uint64_t* a, const uint64_t* b, uint64_t* c, size_t l) {
                addBackend(a, b, c, l);
            }
        #pragma endregion // uint64_t

        #pragma region // __uint128_t
            __attribute__((target("default")))
            inline void addBackend(const __uint128_t* a, const __uint128_t* b, __uint128_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") add\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void add(const std::vector<__uint128_t>& a, const std::vector<__uint128_t>& b, std::vector<__uint128_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void add(const __uint128_t* a, const __uint128_t* b, __uint128_t* c, size_t l) {
                addBackend(a, b, c, l);
            }
        #pragma endregion // __uint128_t

        #pragma region // float
            __attribute__((target("default")))
            inline void addBackend(const float* a, const float* b, float* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") add\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __SSE__
                __attribute__((target("sse")))
                inline void addBackend(const float* a, const float* b, float* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m128 vec_a;
                    __m128 vec_b;
                    __m128 vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 3 < l; i += 4) {
                        if (isAlignedA) {
                            vec_a = _mm_load_ps(a + i);
                        } else {
                            vec_a = _mm_loadu_ps(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = _mm_load_ps(b + i);
                        } else {
                            vec_b = _mm_loadu_ps(b + i);
                        }
                        
                        vec_c = _mm_add_ps(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            _mm_store_ps(c + i, vec_c);
                        } else {
                            _mm_storeu_ps(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE__

            #ifdef __AVX__
                __attribute__((target("avx")))
                inline void addBackend(const float* a, const float* b, float* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m256 vec_a;
                    __m256 vec_b;
                    __m256 vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 7 < l; i += 8) {
                        if (isAlignedA) {
                            vec_a = _mm256_load_ps(a + i);
                        } else {
                            vec_a = _mm256_loadu_ps(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = _mm256_load_ps(b + i);
                        } else {
                            vec_b = _mm256_loadu_ps(b + i);
                        }
                        
                        vec_c = _mm256_add_ps(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            _mm256_store_ps(c + i, vec_c);
                        } else {
                            _mm256_storeu_ps(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX__

            void add(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void add(const float* a, const float* b, float* c, size_t l) {
                addBackend(a, b, c, l);
            }
        #pragma endregion // float

        #pragma region // double
            __attribute__((target("default")))
            inline void addBackend(const double* a, const double* b, double* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") add\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void addBackend(const double* a, const double* b, double* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse2\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m128d vec_a;
                    __m128d vec_b;
                    __m128d vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 1 < l; i += 2) {
                        if (isAlignedA) {
                            vec_a = _mm_load_pd(a + i);
                        } else {
                            vec_a = _mm_loadu_pd(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = _mm_load_pd(b + i);
                        } else {
                            vec_b = _mm_loadu_pd(b + i);
                        }
                        
                        vec_c = _mm_add_pd(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            _mm_store_pd(c + i, vec_c);
                        } else {
                            _mm_storeu_pd(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE2__

            #ifdef __AVX__
                __attribute__((target("avx")))
                inline void addBackend(const double* a, const double* b, double* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx\") add\n";
                    #endif
                    
                    size_t i = 0;
                    __m256d vec_a;
                    __m256d vec_b;
                    __m256d vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 3 < l; i += 4) {
                        if (isAlignedA) {
                            vec_a = _mm256_load_pd(a + i);
                        } else {
                            vec_a = _mm256_loadu_pd(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = _mm256_load_pd(b + i);
                        } else {
                            vec_b = _mm256_loadu_pd(b + i);
                        }
                        
                        vec_c = _mm256_add_pd(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            _mm256_store_pd(c + i, vec_c);
                        } else {
                            _mm256_storeu_pd(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX__

            void add(const std::vector<double>& a, const std::vector<double>& b, std::vector<double>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void add(const double* a, const double* b, double* c, size_t l) {
                addBackend(a, b, c, l);
            }
        #pragma endregion // double

        #pragma region // long double
            __attribute__((target("default")))
            inline void addBackend(const long double* a, const long double* b, long double* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") add\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void add(const std::vector<long double>& a, const std::vector<long double>& b, std::vector<long double>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                addBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void add(const long double* a, const long double* b, long double* c, size_t l) {
                addBackend(a, b, c, l);
            }
        #pragma endregion // long double
    #pragma endregion // add
    
    #pragma region // sub
        #pragma region // int8_t
            __attribute__((target("default")))
            inline void subBackend(const int8_t* a, const int8_t* b, int8_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") sub\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void subBackend(const int8_t* a, const int8_t* b, int8_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"mmx\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m64 vec_a;
                    __m64 vec_b;
                    __m64 vec_c;
                    const bool isAlignedA = isAligned(a, 8);
                    const bool isAlignedB = isAligned(b, 8);
                    const bool isAlignedC = isAligned(c, 8);
                    
                    for (; i + 7 < l; i += 8) {
                        if (isAlignedA) {
                            vec_a = [](const int8_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(a + i);
                        } else {
                            vec_a = [](const int8_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int8_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(b + i);
                        } else {
                            vec_b = [](const int8_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(b + i);
                        }
                        
                        vec_c = _mm_sub_pi8(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int8_t *ptr, const __m64 vec) {*reinterpret_cast<__m64*>(ptr) = vec;}(c + i, vec_c);
                        } else {
                            [](int8_t *ptr, const __m64 vec) {std::memcpy(ptr, &vec, sizeof(__m64));}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                    
                    _mm_empty();
                }
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void subBackend(const int8_t* a, const int8_t* b, int8_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse2\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m128i vec_a;
                    __m128i vec_b;
                    __m128i vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 15 < l; i += 16) {
                        if (isAlignedA) {
                            vec_a = [](const int8_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const int8_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int8_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const int8_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm_sub_epi8(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int8_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](int8_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void subBackend(const int8_t* a, const int8_t* b, int8_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx2\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m256i vec_a;
                    __m256i vec_b;
                    __m256i vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 31 < l; i += 32) {
                        if (isAlignedA) {
                            vec_a = [](const int8_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const int8_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int8_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const int8_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm256_sub_epi8(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int8_t* ptr, const __m256i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](int8_t* ptr, const __m256i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX2__

            void sub(const std::vector<int8_t>& a, const std::vector<int8_t>& b, std::vector<int8_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void sub(const int8_t* a, const int8_t* b, int8_t* c, size_t l) {
                subBackend(a, b, c, l);
            }
        #pragma endregion // int8_t

        #pragma region // int16_t
            __attribute__((target("default")))
            inline void subBackend(const int16_t* a, const int16_t* b, int16_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") sub\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void subBackend(const int16_t* a, const int16_t* b, int16_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"mmx\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m64 vec_a;
                    __m64 vec_b;
                    __m64 vec_c;
                    const bool isAlignedA = isAligned(a, 8);
                    const bool isAlignedB = isAligned(b, 8);
                    const bool isAlignedC = isAligned(c, 8);
                    
                    for (; i + 3 < l; i += 4) {
                        if (isAlignedA) {
                            vec_a = [](const int16_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(a + i);
                        } else {
                            vec_a = [](const int16_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int16_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(b + i);
                        } else {
                            vec_b = [](const int16_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(b + i);
                        }
                        
                        vec_c = _mm_sub_pi16(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int16_t *ptr, const __m64 vec) {*reinterpret_cast<__m64*>(ptr) = vec;}(c + i, vec_c);
                        } else {
                            [](int16_t *ptr, const __m64 vec) {std::memcpy(ptr, &vec, sizeof(__m64));}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                    
                    _mm_empty();
                }
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void subBackend(const int16_t* a, const int16_t* b, int16_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse2\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m128i vec_a;
                    __m128i vec_b;
                    __m128i vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 7 < l; i += 8) {
                        if (isAlignedA) {
                            vec_a = [](const int16_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const int16_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int16_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const int16_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm_sub_epi16(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int16_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](int16_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void subBackend(const int16_t* a, const int16_t* b, int16_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx2\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m256i vec_a;
                    __m256i vec_b;
                    __m256i vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 15 < l; i += 16) {
                        if (isAlignedA) {
                            vec_a = [](const int16_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const int16_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int16_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const int16_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm256_sub_epi16(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int16_t* ptr, const __m256i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](int16_t* ptr, const __m256i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX2__

            void sub(const std::vector<int16_t>& a, const std::vector<int16_t>& b, std::vector<int16_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void sub(const int16_t* a, const int16_t* b, int16_t* c, size_t l) {
                subBackend(a, b, c, l);
            }
        #pragma endregion // int16_t

        #pragma region // int32_t
            __attribute__((target("default")))
            inline void subBackend(const int32_t* a, const int32_t* b, int32_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") sub\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void subBackend(const int32_t* a, const int32_t* b, int32_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"mmx\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m64 vec_a;
                    __m64 vec_b;
                    __m64 vec_c;
                    const bool isAlignedA = isAligned(a, 8);
                    const bool isAlignedB = isAligned(b, 8);
                    const bool isAlignedC = isAligned(c, 8);
                    
                    for (; i + 1 < l; i += 2) {
                        if (isAlignedA) {
                            vec_a = [](const int32_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(a + i);
                        } else {
                            vec_a = [](const int32_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int32_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(b + i);
                        } else {
                            vec_b = [](const int32_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(b + i);
                        }
                        
                        vec_c = _mm_sub_pi32(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int32_t *ptr, const __m64 vec) {*reinterpret_cast<__m64*>(ptr) = vec;}(c + i, vec_c);
                        } else {
                            [](int32_t *ptr, const __m64 vec) {std::memcpy(ptr, &vec, sizeof(__m64));}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                    
                    _mm_empty();
                }
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void subBackend(const int32_t* a, const int32_t* b, int32_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse2\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m128i vec_a;
                    __m128i vec_b;
                    __m128i vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 3 < l; i += 4) {
                        if (isAlignedA) {
                            vec_a = [](const int32_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const int32_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int32_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const int32_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm_sub_epi32(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int32_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](int32_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void subBackend(const int32_t* a, const int32_t* b, int32_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx2\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m256i vec_a;
                    __m256i vec_b;
                    __m256i vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 7 < l; i += 8) {
                        if (isAlignedA) {
                            vec_a = [](const int32_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const int32_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int32_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const int32_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm256_sub_epi32(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int32_t* ptr, const __m256i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](int32_t* ptr, const __m256i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX2__

            void sub(const std::vector<int32_t>& a, const std::vector<int32_t>& b, std::vector<int32_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void sub(const int32_t* a, const int32_t* b, int32_t* c, size_t l) {
                subBackend(a, b, c, l);
            }
        #pragma endregion // int32_t

        #pragma region // int64_t
            __attribute__((target("default")))
            inline void subBackend(const int64_t* a, const int64_t* b, int64_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") sub\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void subBackend(const int64_t* a, const int64_t* b, int64_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse2\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m128i vec_a;
                    __m128i vec_b;
                    __m128i vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 1 < l; i += 2) {
                        if (isAlignedA) {
                            vec_a = [](const int64_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const int64_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int64_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const int64_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm_sub_epi64(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int64_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](int64_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void subBackend(const int64_t* a, const int64_t* b, int64_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx2\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m256i vec_a;
                    __m256i vec_b;
                    __m256i vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 3 < l; i += 4) {
                        if (isAlignedA) {
                            vec_a = [](const int64_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const int64_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int64_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const int64_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm256_sub_epi64(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int64_t* ptr, const __m256i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](int64_t* ptr, const __m256i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX2__

            void sub(const std::vector<int64_t>& a, const std::vector<int64_t>& b, std::vector<int64_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void sub(const int64_t* a, const int64_t* b, int64_t* c, size_t l) {
                subBackend(a, b, c, l);
            }
        #pragma endregion // int64_t

        #pragma region // __int128_t
            __attribute__((target("default")))
            inline void subBackend(const __int128_t* a, const __int128_t* b, __int128_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") sub\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void sub(const std::vector<__int128_t>& a, const std::vector<__int128_t>& b, std::vector<__int128_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void sub(const __int128_t* a, const __int128_t* b, __int128_t* c, size_t l) {
                subBackend(a, b, c, l);
            }
        #pragma endregion // __int128_t

        #pragma region // uint8_t
            __attribute__((target("default")))
            inline void subBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") sub\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void subBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"mmx\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m64 vec_a;
                    __m64 vec_b;
                    __m64 vec_c;
                    const bool isAlignedA = isAligned(a, 8);
                    const bool isAlignedB = isAligned(b, 8);
                    const bool isAlignedC = isAligned(c, 8);
                    
                    for (; i + 7 < l; i += 8) {
                        if (isAlignedA) {
                            vec_a = [](const uint8_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(a + i);
                        } else {
                            vec_a = [](const uint8_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint8_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(b + i);
                        } else {
                            vec_b = [](const uint8_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(b + i);
                        }
                        
                        vec_c = _mm_sub_pi8(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint8_t *ptr, const __m64 vec) {*reinterpret_cast<__m64*>(ptr) = vec;}(c + i, vec_c);
                        } else {
                            [](uint8_t *ptr, const __m64 vec) {std::memcpy(ptr, &vec, sizeof(__m64));}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                    
                    _mm_empty();
                }
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void subBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse2\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m128i vec_a;
                    __m128i vec_b;
                    __m128i vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 15 < l; i += 16) {
                        if (isAlignedA) {
                            vec_a = [](const uint8_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const uint8_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint8_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const uint8_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm_sub_epi8(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint8_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](uint8_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void subBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx2\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m256i vec_a;
                    __m256i vec_b;
                    __m256i vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 31 < l; i += 32) {
                        if (isAlignedA) {
                            vec_a = [](const uint8_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const uint8_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint8_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const uint8_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm256_sub_epi8(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint8_t* ptr, const __m256i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](uint8_t* ptr, const __m256i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX2__

            void sub(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b, std::vector<uint8_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void sub(const uint8_t* a, const uint8_t* b, uint8_t* c, size_t l) {
                subBackend(a, b, c, l);
            }
        #pragma endregion // uint8_t

        #pragma region // uint16_t
            __attribute__((target("default")))
            inline void subBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") sub\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void subBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"mmx\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m64 vec_a;
                    __m64 vec_b;
                    __m64 vec_c;
                    const bool isAlignedA = isAligned(a, 8);
                    const bool isAlignedB = isAligned(b, 8);
                    const bool isAlignedC = isAligned(c, 8);
                    
                    for (; i + 3 < l; i += 4) {
                        if (isAlignedA) {
                            vec_a = [](const uint16_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(a + i);
                        } else {
                            vec_a = [](const uint16_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint16_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(b + i);
                        } else {
                            vec_b = [](const uint16_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(b + i);
                        }
                        
                        vec_c = _mm_sub_pi16(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint16_t *ptr, const __m64 vec) {*reinterpret_cast<__m64*>(ptr) = vec;}(c + i, vec_c);
                        } else {
                            [](uint16_t *ptr, const __m64 vec) {std::memcpy(ptr, &vec, sizeof(__m64));}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                    
                    _mm_empty();
                }
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void subBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse2\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m128i vec_a;
                    __m128i vec_b;
                    __m128i vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 7 < l; i += 8) {
                        if (isAlignedA) {
                            vec_a = [](const uint16_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const uint16_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint16_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const uint16_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm_sub_epi16(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint16_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](uint16_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void subBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx2\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m256i vec_a;
                    __m256i vec_b;
                    __m256i vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 15 < l; i += 16) {
                        if (isAlignedA) {
                            vec_a = [](const uint16_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const uint16_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint16_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const uint16_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm256_sub_epi16(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint16_t* ptr, const __m256i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](uint16_t* ptr, const __m256i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX2__

            void sub(const std::vector<uint16_t>& a, const std::vector<uint16_t>& b, std::vector<uint16_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void sub(const uint16_t* a, const uint16_t* b, uint16_t* c, size_t l) {
                subBackend(a, b, c, l);
            }
        #pragma endregion // uint16_t

        #pragma region // uint32_t
            __attribute__((target("default")))
            inline void subBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") sub\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void subBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"mmx\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m64 vec_a;
                    __m64 vec_b;
                    __m64 vec_c;
                    const bool isAlignedA = isAligned(a, 8);
                    const bool isAlignedB = isAligned(b, 8);
                    const bool isAlignedC = isAligned(c, 8);
                    
                    for (; i + 1 < l; i += 2) {
                        if (isAlignedA) {
                            vec_a = [](const uint32_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(a + i);
                        } else {
                            vec_a = [](const uint32_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint32_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(b + i);
                        } else {
                            vec_b = [](const uint32_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(b + i);
                        }
                        
                        vec_c = _mm_sub_pi32(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint32_t *ptr, const __m64 vec) {*reinterpret_cast<__m64*>(ptr) = vec;}(c + i, vec_c);
                        } else {
                            [](uint32_t *ptr, const __m64 vec) {std::memcpy(ptr, &vec, sizeof(__m64));}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                    
                    _mm_empty();
                }
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void subBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse2\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m128i vec_a;
                    __m128i vec_b;
                    __m128i vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 3 < l; i += 4) {
                        if (isAlignedA) {
                            vec_a = [](const uint32_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const uint32_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint32_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const uint32_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm_sub_epi32(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint32_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](uint32_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void subBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx2\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m256i vec_a;
                    __m256i vec_b;
                    __m256i vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 7 < l; i += 8) {
                        if (isAlignedA) {
                            vec_a = [](const uint32_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const uint32_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint32_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const uint32_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm256_sub_epi32(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint32_t* ptr, const __m256i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](uint32_t* ptr, const __m256i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX2__

            void sub(const std::vector<uint32_t>& a, const std::vector<uint32_t>& b, std::vector<uint32_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void sub(const uint32_t* a, const uint32_t* b, uint32_t* c, size_t l) {
                subBackend(a, b, c, l);
            }
        #pragma endregion // uint32_t

        #pragma region // uint64_t
            __attribute__((target("default")))
            inline void subBackend(const uint64_t* a, const uint64_t* b, uint64_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") sub\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void subBackend(const uint64_t* a, const uint64_t* b, uint64_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse2\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m128i vec_a;
                    __m128i vec_b;
                    __m128i vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 1 < l; i += 2) {
                        if (isAlignedA) {
                            vec_a = [](const uint64_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const uint64_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint64_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const uint64_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm_sub_epi64(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint64_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](uint64_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void subBackend(const uint64_t* a, const uint64_t* b, uint64_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx2\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m256i vec_a;
                    __m256i vec_b;
                    __m256i vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 3 < l; i += 4) {
                        if (isAlignedA) {
                            vec_a = [](const uint64_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const uint64_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint64_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const uint64_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm256_sub_epi64(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint64_t* ptr, const __m256i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](uint64_t* ptr, const __m256i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX2__

            void sub(const std::vector<uint64_t>& a, const std::vector<uint64_t>& b, std::vector<uint64_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void sub(const uint64_t* a, const uint64_t* b, uint64_t* c, size_t l) {
                subBackend(a, b, c, l);
            }
        #pragma endregion // uint64_t

        #pragma region // __uint128_t
            __attribute__((target("default")))
            inline void subBackend(const __uint128_t* a, const __uint128_t* b, __uint128_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") sub\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void sub(const std::vector<__uint128_t>& a, const std::vector<__uint128_t>& b, std::vector<__uint128_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void sub(const __uint128_t* a, const __uint128_t* b, __uint128_t* c, size_t l) {
                subBackend(a, b, c, l);
            }
        #pragma endregion // __uint128_t

        #pragma region // float
            __attribute__((target("default")))
            inline void subBackend(const float* a, const float* b, float* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") sub\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __SSE__
                __attribute__((target("sse")))
                inline void subBackend(const float* a, const float* b, float* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m128 vec_a;
                    __m128 vec_b;
                    __m128 vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 3 < l; i += 4) {
                        if (isAlignedA) {
                            vec_a = _mm_load_ps(a + i);
                        } else {
                            vec_a = _mm_loadu_ps(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = _mm_load_ps(b + i);
                        } else {
                            vec_b = _mm_loadu_ps(b + i);
                        }
                        
                        vec_c = _mm_sub_ps(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            _mm_store_ps(c + i, vec_c);
                        } else {
                            _mm_storeu_ps(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE__

            #ifdef __AVX__
                __attribute__((target("avx")))
                inline void subBackend(const float* a, const float* b, float* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m256 vec_a;
                    __m256 vec_b;
                    __m256 vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 7 < l; i += 8) {
                        if (isAlignedA) {
                            vec_a = _mm256_load_ps(a + i);
                        } else {
                            vec_a = _mm256_loadu_ps(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = _mm256_load_ps(b + i);
                        } else {
                            vec_b = _mm256_loadu_ps(b + i);
                        }
                        
                        vec_c = _mm256_sub_ps(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            _mm256_store_ps(c + i, vec_c);
                        } else {
                            _mm256_storeu_ps(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX__

            void sub(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void sub(const float* a, const float* b, float* c, size_t l) {
                subBackend(a, b, c, l);
            }
        #pragma endregion // float

        #pragma region // double
            __attribute__((target("default")))
            inline void subBackend(const double* a, const double* b, double* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") sub\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void subBackend(const double* a, const double* b, double* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse2\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m128d vec_a;
                    __m128d vec_b;
                    __m128d vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 1 < l; i += 2) {
                        if (isAlignedA) {
                            vec_a = _mm_load_pd(a + i);
                        } else {
                            vec_a = _mm_loadu_pd(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = _mm_load_pd(b + i);
                        } else {
                            vec_b = _mm_loadu_pd(b + i);
                        }
                        
                        vec_c = _mm_sub_pd(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            _mm_store_pd(c + i, vec_c);
                        } else {
                            _mm_storeu_pd(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE2__

            #ifdef __AVX__
                __attribute__((target("avx")))
                inline void subBackend(const double* a, const double* b, double* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx\") sub\n";
                    #endif
                    
                    size_t i = 0;
                    __m256d vec_a;
                    __m256d vec_b;
                    __m256d vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 3 < l; i += 4) {
                        if (isAlignedA) {
                            vec_a = _mm256_load_pd(a + i);
                        } else {
                            vec_a = _mm256_loadu_pd(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = _mm256_load_pd(b + i);
                        } else {
                            vec_b = _mm256_loadu_pd(b + i);
                        }
                        
                        vec_c = _mm256_sub_pd(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            _mm256_store_pd(c + i, vec_c);
                        } else {
                            _mm256_storeu_pd(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX__

            void sub(const std::vector<double>& a, const std::vector<double>& b, std::vector<double>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void sub(const double* a, const double* b, double* c, size_t l) {
                subBackend(a, b, c, l);
            }
        #pragma endregion // double

        #pragma region // long double
            __attribute__((target("default")))
            inline void subBackend(const long double* a, const long double* b, long double* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") sub\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void sub(const std::vector<long double>& a, const std::vector<long double>& b, std::vector<long double>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                subBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void sub(const long double* a, const long double* b, long double* c, size_t l) {
                subBackend(a, b, c, l);
            }
        #pragma endregion // long double
    #pragma endregion // sub
    
    #pragma region // mul
        #pragma region // int8_t
            __attribute__((target("default")))
            inline void mulBackend(const int8_t* a, const int8_t* b, int8_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") mul\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void mul(const std::vector<int8_t>& a, const std::vector<int8_t>& b, std::vector<int8_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void mul(const int8_t* a, const int8_t* b, int8_t* c, size_t l) {
                mulBackend(a, b, c, l);
            }
        #pragma endregion // int8_t

        #pragma region // int16_t
            __attribute__((target("default")))
            inline void mulBackend(const int16_t* a, const int16_t* b, int16_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") mul\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void mulBackend(const int16_t* a, const int16_t* b, int16_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"mmx\") mul\n";
                    #endif
                    
                    size_t i = 0;
                    __m64 vec_a;
                    __m64 vec_b;
                    __m64 vec_c;
                    const bool isAlignedA = isAligned(a, 8);
                    const bool isAlignedB = isAligned(b, 8);
                    const bool isAlignedC = isAligned(c, 8);
                    
                    for (; i + 3 < l; i += 4) {
                        if (isAlignedA) {
                            vec_a = [](const int16_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(a + i);
                        } else {
                            vec_a = [](const int16_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int16_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(b + i);
                        } else {
                            vec_b = [](const int16_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(b + i);
                        }
                        
                        vec_c = _mm_mullo_pi16(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int16_t *ptr, const __m64 vec) {*reinterpret_cast<__m64*>(ptr) = vec;}(c + i, vec_c);
                        } else {
                            [](int16_t *ptr, const __m64 vec) {std::memcpy(ptr, &vec, sizeof(__m64));}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                    
                    _mm_empty();
                }
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void mulBackend(const int16_t* a, const int16_t* b, int16_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse2\") mul\n";
                    #endif
                    
                    size_t i = 0;
                    __m128i vec_a;
                    __m128i vec_b;
                    __m128i vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 7 < l; i += 8) {
                        if (isAlignedA) {
                            vec_a = [](const int16_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const int16_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int16_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const int16_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm_mullo_epi16(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int16_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](int16_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void mulBackend(const int16_t* a, const int16_t* b, int16_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx2\") mul\n";
                    #endif
                    
                    size_t i = 0;
                    __m256i vec_a;
                    __m256i vec_b;
                    __m256i vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 15 < l; i += 16) {
                        if (isAlignedA) {
                            vec_a = [](const int16_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const int16_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int16_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const int16_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm256_mullo_epi16(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int16_t* ptr, const __m256i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](int16_t* ptr, const __m256i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX2__

            void mul(const std::vector<int16_t>& a, const std::vector<int16_t>& b, std::vector<int16_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void mul(const int16_t* a, const int16_t* b, int16_t* c, size_t l) {
                mulBackend(a, b, c, l);
            }
        #pragma endregion // int16_t

        #pragma region // int32_t
            __attribute__((target("default")))
            inline void mulBackend(const int32_t* a, const int32_t* b, int32_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") mul\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void mulBackend(const int32_t* a, const int32_t* b, int32_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx2\") mul\n";
                    #endif
                    
                    size_t i = 0;
                    __m256i vec_a;
                    __m256i vec_b;
                    __m256i vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 7 < l; i += 8) {
                        if (isAlignedA) {
                            vec_a = [](const int32_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const int32_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const int32_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const int32_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm256_mullo_epi32(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](int32_t* ptr, const __m256i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](int32_t* ptr, const __m256i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX2__

            void mul(const std::vector<int32_t>& a, const std::vector<int32_t>& b, std::vector<int32_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void mul(const int32_t* a, const int32_t* b, int32_t* c, size_t l) {
                mulBackend(a, b, c, l);
            }
        #pragma endregion // int32_t

        #pragma region // int64_t
            __attribute__((target("default")))
            inline void mulBackend(const int64_t* a, const int64_t* b, int64_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") mul\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void mul(const std::vector<int64_t>& a, const std::vector<int64_t>& b, std::vector<int64_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void mul(const int64_t* a, const int64_t* b, int64_t* c, size_t l) {
                mulBackend(a, b, c, l);
            }
        #pragma endregion // int64_t

        #pragma region // __int128_t
            __attribute__((target("default")))
            inline void mulBackend(const __int128_t* a, const __int128_t* b, __int128_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") mul\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void mul(const std::vector<__int128_t>& a, const std::vector<__int128_t>& b, std::vector<__int128_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void mul(const __int128_t* a, const __int128_t* b, __int128_t* c, size_t l) {
                mulBackend(a, b, c, l);
            }
        #pragma endregion // __int128_t

        #pragma region // uint8_t
            __attribute__((target("default")))
            inline void mulBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") mul\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void mul(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b, std::vector<uint8_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void mul(const uint8_t* a, const uint8_t* b, uint8_t* c, size_t l) {
                mulBackend(a, b, c, l);
            }
        #pragma endregion // uint8_t

        #pragma region // uint16_t
            __attribute__((target("default")))
            inline void mulBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") mul\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __MMX__
                __attribute__((target("mmx")))
                inline void mulBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"mmx\") mul\n";
                    #endif
                    
                    size_t i = 0;
                    __m64 vec_a;
                    __m64 vec_b;
                    __m64 vec_c;
                    const bool isAlignedA = isAligned(a, 8);
                    const bool isAlignedB = isAligned(b, 8);
                    const bool isAlignedC = isAligned(c, 8);
                    
                    for (; i + 3 < l; i += 4) {
                        if (isAlignedA) {
                            vec_a = [](const uint16_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(a + i);
                        } else {
                            vec_a = [](const uint16_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint16_t* ptr) {return *reinterpret_cast<const __m64*>(ptr);}(b + i);
                        } else {
                            vec_b = [](const uint16_t* ptr) {uint64_t temp; std::memcpy(&temp, ptr, sizeof(temp)); return *reinterpret_cast<__m64*>(&temp);}(b + i);
                        }
                        
                        vec_c = _mm_mullo_pi16(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint16_t *ptr, const __m64 vec) {*reinterpret_cast<__m64*>(ptr) = vec;}(c + i, vec_c);
                        } else {
                            [](uint16_t *ptr, const __m64 vec) {std::memcpy(ptr, &vec, sizeof(__m64));}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                    
                    _mm_empty();
                }
            #endif // __MMX__

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void mulBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse2\") mul\n";
                    #endif
                    
                    size_t i = 0;
                    __m128i vec_a;
                    __m128i vec_b;
                    __m128i vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 7 < l; i += 8) {
                        if (isAlignedA) {
                            vec_a = [](const uint16_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const uint16_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint16_t* ptr) {return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const uint16_t* ptr) {return _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm_mullo_epi16(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint16_t* ptr, const __m128i vec) {_mm_store_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](uint16_t* ptr, const __m128i vec) {_mm_storeu_si128(reinterpret_cast<__m128i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE2__

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void mulBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx2\") mul\n";
                    #endif
                    
                    size_t i = 0;
                    __m256i vec_a;
                    __m256i vec_b;
                    __m256i vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 15 < l; i += 16) {
                        if (isAlignedA) {
                            vec_a = [](const uint16_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const uint16_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint16_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const uint16_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm256_mullo_epi16(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint16_t* ptr, const __m256i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](uint16_t* ptr, const __m256i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX2__

            void mul(const std::vector<uint16_t>& a, const std::vector<uint16_t>& b, std::vector<uint16_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void mul(const uint16_t* a, const uint16_t* b, uint16_t* c, size_t l) {
                mulBackend(a, b, c, l);
            }
        #pragma endregion // uint16_t

        #pragma region // uint32_t
            __attribute__((target("default")))
            inline void mulBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") mul\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __AVX2__
                __attribute__((target("avx2")))
                inline void mulBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx2\") mul\n";
                    #endif
                    
                    size_t i = 0;
                    __m256i vec_a;
                    __m256i vec_b;
                    __m256i vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 7 < l; i += 8) {
                        if (isAlignedA) {
                            vec_a = [](const uint32_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        } else {
                            vec_a = [](const uint32_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = [](const uint32_t* ptr) {return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        } else {
                            vec_b = [](const uint32_t* ptr) {return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));}(b + i);
                        }
                        
                        vec_c = _mm256_mullo_epi32(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            [](uint32_t* ptr, const __m256i vec) {_mm256_store_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        } else {
                            [](uint32_t* ptr, const __m256i vec) {_mm256_storeu_si256(reinterpret_cast<__m256i*>(ptr), vec);}(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX2__

            void mul(const std::vector<uint32_t>& a, const std::vector<uint32_t>& b, std::vector<uint32_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void mul(const uint32_t* a, const uint32_t* b, uint32_t* c, size_t l) {
                mulBackend(a, b, c, l);
            }
        #pragma endregion // uint32_t

        #pragma region // uint64_t
            __attribute__((target("default")))
            inline void mulBackend(const uint64_t* a, const uint64_t* b, uint64_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") mul\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void mul(const std::vector<uint64_t>& a, const std::vector<uint64_t>& b, std::vector<uint64_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void mul(const uint64_t* a, const uint64_t* b, uint64_t* c, size_t l) {
                mulBackend(a, b, c, l);
            }
        #pragma endregion // uint64_t

        #pragma region // __uint128_t
            __attribute__((target("default")))
            inline void mulBackend(const __uint128_t* a, const __uint128_t* b, __uint128_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") mul\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void mul(const std::vector<__uint128_t>& a, const std::vector<__uint128_t>& b, std::vector<__uint128_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void mul(const __uint128_t* a, const __uint128_t* b, __uint128_t* c, size_t l) {
                mulBackend(a, b, c, l);
            }
        #pragma endregion // __uint128_t

        #pragma region // float
            __attribute__((target("default")))
            inline void mulBackend(const float* a, const float* b, float* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") mul\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __SSE__
                __attribute__((target("sse")))
                inline void mulBackend(const float* a, const float* b, float* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse\") mul\n";
                    #endif
                    
                    size_t i = 0;
                    __m128 vec_a;
                    __m128 vec_b;
                    __m128 vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 3 < l; i += 4) {
                        if (isAlignedA) {
                            vec_a = _mm_load_ps(a + i);
                        } else {
                            vec_a = _mm_loadu_ps(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = _mm_load_ps(b + i);
                        } else {
                            vec_b = _mm_loadu_ps(b + i);
                        }
                        
                        vec_c = _mm_mul_ps(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            _mm_store_ps(c + i, vec_c);
                        } else {
                            _mm_storeu_ps(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE__

            #ifdef __AVX__
                __attribute__((target("avx")))
                inline void mulBackend(const float* a, const float* b, float* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx\") mul\n";
                    #endif
                    
                    size_t i = 0;
                    __m256 vec_a;
                    __m256 vec_b;
                    __m256 vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 7 < l; i += 8) {
                        if (isAlignedA) {
                            vec_a = _mm256_load_ps(a + i);
                        } else {
                            vec_a = _mm256_loadu_ps(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = _mm256_load_ps(b + i);
                        } else {
                            vec_b = _mm256_loadu_ps(b + i);
                        }
                        
                        vec_c = _mm256_mul_ps(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            _mm256_store_ps(c + i, vec_c);
                        } else {
                            _mm256_storeu_ps(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX__

            void mul(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void mul(const float* a, const float* b, float* c, size_t l) {
                mulBackend(a, b, c, l);
            }
        #pragma endregion // float

        #pragma region // double
            __attribute__((target("default")))
            inline void mulBackend(const double* a, const double* b, double* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") mul\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void mulBackend(const double* a, const double* b, double* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse2\") mul\n";
                    #endif
                    
                    size_t i = 0;
                    __m128d vec_a;
                    __m128d vec_b;
                    __m128d vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 1 < l; i += 2) {
                        if (isAlignedA) {
                            vec_a = _mm_load_pd(a + i);
                        } else {
                            vec_a = _mm_loadu_pd(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = _mm_load_pd(b + i);
                        } else {
                            vec_b = _mm_loadu_pd(b + i);
                        }
                        
                        vec_c = _mm_mul_pd(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            _mm_store_pd(c + i, vec_c);
                        } else {
                            _mm_storeu_pd(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE2__

            #ifdef __AVX__
                __attribute__((target("avx")))
                inline void mulBackend(const double* a, const double* b, double* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx\") mul\n";
                    #endif
                    
                    size_t i = 0;
                    __m256d vec_a;
                    __m256d vec_b;
                    __m256d vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 3 < l; i += 4) {
                        if (isAlignedA) {
                            vec_a = _mm256_load_pd(a + i);
                        } else {
                            vec_a = _mm256_loadu_pd(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = _mm256_load_pd(b + i);
                        } else {
                            vec_b = _mm256_loadu_pd(b + i);
                        }
                        
                        vec_c = _mm256_mul_pd(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            _mm256_store_pd(c + i, vec_c);
                        } else {
                            _mm256_storeu_pd(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX__

            void mul(const std::vector<double>& a, const std::vector<double>& b, std::vector<double>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void mul(const double* a, const double* b, double* c, size_t l) {
                mulBackend(a, b, c, l);
            }
        #pragma endregion // double

        #pragma region // long double
            __attribute__((target("default")))
            inline void mulBackend(const long double* a, const long double* b, long double* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") mul\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void mul(const std::vector<long double>& a, const std::vector<long double>& b, std::vector<long double>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                mulBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void mul(const long double* a, const long double* b, long double* c, size_t l) {
                mulBackend(a, b, c, l);
            }
        #pragma endregion // long double
    #pragma endregion // mul
    
    #pragma region // div
        #pragma region // int8_t
            __attribute__((target("default")))
            inline void divBackend(const int8_t* a, const int8_t* b, int8_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") div\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void div(const std::vector<int8_t>& a, const std::vector<int8_t>& b, std::vector<int8_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void div(const int8_t* a, const int8_t* b, int8_t* c, size_t l) {
                divBackend(a, b, c, l);
            }
        #pragma endregion // int8_t

        #pragma region // int16_t
            __attribute__((target("default")))
            inline void divBackend(const int16_t* a, const int16_t* b, int16_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") div\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void div(const std::vector<int16_t>& a, const std::vector<int16_t>& b, std::vector<int16_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void div(const int16_t* a, const int16_t* b, int16_t* c, size_t l) {
                divBackend(a, b, c, l);
            }
        #pragma endregion // int16_t

        #pragma region // int32_t
            __attribute__((target("default")))
            inline void divBackend(const int32_t* a, const int32_t* b, int32_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") div\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void div(const std::vector<int32_t>& a, const std::vector<int32_t>& b, std::vector<int32_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void div(const int32_t* a, const int32_t* b, int32_t* c, size_t l) {
                divBackend(a, b, c, l);
            }
        #pragma endregion // int32_t

        #pragma region // int64_t
            __attribute__((target("default")))
            inline void divBackend(const int64_t* a, const int64_t* b, int64_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") div\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void div(const std::vector<int64_t>& a, const std::vector<int64_t>& b, std::vector<int64_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void div(const int64_t* a, const int64_t* b, int64_t* c, size_t l) {
                divBackend(a, b, c, l);
            }
        #pragma endregion // int64_t

        #pragma region // __int128_t
            __attribute__((target("default")))
            inline void divBackend(const __int128_t* a, const __int128_t* b, __int128_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") div\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void div(const std::vector<__int128_t>& a, const std::vector<__int128_t>& b, std::vector<__int128_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void div(const __int128_t* a, const __int128_t* b, __int128_t* c, size_t l) {
                divBackend(a, b, c, l);
            }
        #pragma endregion // __int128_t

        #pragma region // uint8_t
            __attribute__((target("default")))
            inline void divBackend(const uint8_t* a, const uint8_t* b, uint8_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") div\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void div(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b, std::vector<uint8_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void div(const uint8_t* a, const uint8_t* b, uint8_t* c, size_t l) {
                divBackend(a, b, c, l);
            }
        #pragma endregion // uint8_t

        #pragma region // uint16_t
            __attribute__((target("default")))
            inline void divBackend(const uint16_t* a, const uint16_t* b, uint16_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") div\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void div(const std::vector<uint16_t>& a, const std::vector<uint16_t>& b, std::vector<uint16_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void div(const uint16_t* a, const uint16_t* b, uint16_t* c, size_t l) {
                divBackend(a, b, c, l);
            }
        #pragma endregion // uint16_t

        #pragma region // uint32_t
            __attribute__((target("default")))
            inline void divBackend(const uint32_t* a, const uint32_t* b, uint32_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") div\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void div(const std::vector<uint32_t>& a, const std::vector<uint32_t>& b, std::vector<uint32_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void div(const uint32_t* a, const uint32_t* b, uint32_t* c, size_t l) {
                divBackend(a, b, c, l);
            }
        #pragma endregion // uint32_t

        #pragma region // uint64_t
            __attribute__((target("default")))
            inline void divBackend(const uint64_t* a, const uint64_t* b, uint64_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") div\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void div(const std::vector<uint64_t>& a, const std::vector<uint64_t>& b, std::vector<uint64_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void div(const uint64_t* a, const uint64_t* b, uint64_t* c, size_t l) {
                divBackend(a, b, c, l);
            }
        #pragma endregion // uint64_t

        #pragma region // __uint128_t
            __attribute__((target("default")))
            inline void divBackend(const __uint128_t* a, const __uint128_t* b, __uint128_t* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") div\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void div(const std::vector<__uint128_t>& a, const std::vector<__uint128_t>& b, std::vector<__uint128_t>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void div(const __uint128_t* a, const __uint128_t* b, __uint128_t* c, size_t l) {
                divBackend(a, b, c, l);
            }
        #pragma endregion // __uint128_t

        #pragma region // float
            __attribute__((target("default")))
            inline void divBackend(const float* a, const float* b, float* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") div\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __SSE__
                __attribute__((target("sse")))
                inline void divBackend(const float* a, const float* b, float* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse\") div\n";
                    #endif
                    
                    size_t i = 0;
                    __m128 vec_a;
                    __m128 vec_b;
                    __m128 vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 3 < l; i += 4) {
                        if (isAlignedA) {
                            vec_a = _mm_load_ps(a + i);
                        } else {
                            vec_a = _mm_loadu_ps(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = _mm_load_ps(b + i);
                        } else {
                            vec_b = _mm_loadu_ps(b + i);
                        }
                        
                        vec_c = _mm_div_ps(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            _mm_store_ps(c + i, vec_c);
                        } else {
                            _mm_storeu_ps(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE__

            #ifdef __AVX__
                __attribute__((target("avx")))
                inline void divBackend(const float* a, const float* b, float* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx\") div\n";
                    #endif
                    
                    size_t i = 0;
                    __m256 vec_a;
                    __m256 vec_b;
                    __m256 vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 7 < l; i += 8) {
                        if (isAlignedA) {
                            vec_a = _mm256_load_ps(a + i);
                        } else {
                            vec_a = _mm256_loadu_ps(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = _mm256_load_ps(b + i);
                        } else {
                            vec_b = _mm256_loadu_ps(b + i);
                        }
                        
                        vec_c = _mm256_div_ps(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            _mm256_store_ps(c + i, vec_c);
                        } else {
                            _mm256_storeu_ps(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX__

            void div(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void div(const float* a, const float* b, float* c, size_t l) {
                divBackend(a, b, c, l);
            }
        #pragma endregion // float

        #pragma region // double
            __attribute__((target("default")))
            inline void divBackend(const double* a, const double* b, double* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") div\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            #ifdef __SSE2__
                __attribute__((target("sse2")))
                inline void divBackend(const double* a, const double* b, double* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"sse2\") div\n";
                    #endif
                    
                    size_t i = 0;
                    __m128d vec_a;
                    __m128d vec_b;
                    __m128d vec_c;
                    const bool isAlignedA = isAligned(a, 16);
                    const bool isAlignedB = isAligned(b, 16);
                    const bool isAlignedC = isAligned(c, 16);
                    
                    for (; i + 1 < l; i += 2) {
                        if (isAlignedA) {
                            vec_a = _mm_load_pd(a + i);
                        } else {
                            vec_a = _mm_loadu_pd(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = _mm_load_pd(b + i);
                        } else {
                            vec_b = _mm_loadu_pd(b + i);
                        }
                        
                        vec_c = _mm_div_pd(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            _mm_store_pd(c + i, vec_c);
                        } else {
                            _mm_storeu_pd(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __SSE2__

            #ifdef __AVX__
                __attribute__((target("avx")))
                inline void divBackend(const double* a, const double* b, double* c, const size_t l) {
                    #ifdef EZSIMD_SHOW_FUNC
                        EZSIMD_SHOW_FUNC << "target(\"avx\") div\n";
                    #endif
                    
                    size_t i = 0;
                    __m256d vec_a;
                    __m256d vec_b;
                    __m256d vec_c;
                    const bool isAlignedA = isAligned(a, 32);
                    const bool isAlignedB = isAligned(b, 32);
                    const bool isAlignedC = isAligned(c, 32);
                    
                    for (; i + 3 < l; i += 4) {
                        if (isAlignedA) {
                            vec_a = _mm256_load_pd(a + i);
                        } else {
                            vec_a = _mm256_loadu_pd(a + i);
                        }
                        
                        if (isAlignedB) {
                            vec_b = _mm256_load_pd(b + i);
                        } else {
                            vec_b = _mm256_loadu_pd(b + i);
                        }
                        
                        vec_c = _mm256_div_pd(vec_a, vec_b);
                        
                        if (isAlignedC) {
                            _mm256_store_pd(c + i, vec_c);
                        } else {
                            _mm256_storeu_pd(c + i, vec_c);
                        }
                    }
                    
                    for (; i < l; i++) {
                        c[i] = a[i] + b[i];
                    }
                }
            #endif // __AVX__

            void div(const std::vector<double>& a, const std::vector<double>& b, std::vector<double>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void div(const double* a, const double* b, double* c, size_t l) {
                divBackend(a, b, c, l);
            }
        #pragma endregion // double

        #pragma region // long double
            __attribute__((target("default")))
            inline void divBackend(const long double* a, const long double* b, long double* c, size_t l) {
                #ifdef EZSIMD_SHOW_FUNC
                    EZSIMD_SHOW_FUNC << "target(\"default\") div\n";
                #endif
                
                for (size_t i = 0; i < l; i++) {
                    c[i] = a[i] + b[i];
                }
            }

            void div(const std::vector<long double>& a, const std::vector<long double>& b, std::vector<long double>& c) {
                assert(a.size() == b.size());
                assert(c.size() >= a.size());
                divBackend(a.data(), b.data(), c.data(), a.size());
            }
            
            void div(const long double* a, const long double* b, long double* c, size_t l) {
                divBackend(a, b, c, l);
            }
        #pragma endregion // long double
    #pragma endregion // div
} // namespace ezsimd