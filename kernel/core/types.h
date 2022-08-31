/*
    Copyright (c) 2022 thatOneArchUser
    All rights reserverd
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define null 0

typedef enum {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHT_GREY = 7,
    DARK_GREY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    LIGHT_BROWN = 14,
    WHITE = 15
} colors_t;

typedef enum {
    CHAR,
    INT,
    VOID,
    PCHAR
} TYPE_t;

typedef struct {
    float Re, Im;
} complex32_t;

typedef struct {
    double Re, Im;
} complex64_t;

typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;