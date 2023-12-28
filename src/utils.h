#pragma once

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "fmath.h"

typedef float f32;
typedef float f64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef size_t usize;

typedef void (*callback_t)();

#define print_vec(v) {printf("X: %f, Y: %f, Z: %f\n", v[0], v[1], v[2]);}

#define print_mat4(m)                                                              \
    printf("{\n");                                                                 \
    printf("  { %.2f, %.2f, %.2f, %.2f },\n", m[0][0], m[1][0], m[2][0], m[3][0]); \
    printf("  { %.2f, %.2f, %.2f, %.2f },\n", m[0][1], m[1][1], m[2][1], m[3][1]); \
    printf("  { %.2f, %.2f, %.2f, %.2f },\n", m[0][2], m[1][2], m[2][2], m[3][2]); \
    printf("  { %.2f, %.2f, %.2f, %.2f }\n", m[0][3], m[1][3], m[2][3], m[3][3]);  \
    printf("}\n");
