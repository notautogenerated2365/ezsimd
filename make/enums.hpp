#pragma once

enum arrayType : char {
    ARRAY,
    VECTOR,
};

enum simdType : char {
    MMX,
    SSE,
    SSE2,
    AVX,
    AVX2,
};

enum opType : char {
    ADD,
    SUB,
    MUL,
    DIV,
    PACK_ALIGNED,
    PACK_UNALIGNED,
    UNPACK_ALIGNED,
    UNPACK_UNALIGNED,
};

enum numType : char {
    INT8,
    INT16,
    INT32,
    INT64,
    INT128,
    UINT8,
    UINT16,
    UINT32,
    UINT64,
    UINT128,
    FLOAT16,
    FLOAT32,
    FLOAT64,
    FLOAT128,
};