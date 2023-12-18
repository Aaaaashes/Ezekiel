#pragma once

#define PI         3.14159265358979323846264338327950288
#define PI_2       1.57079632679489661923132169163975144
#define TAU        6.28318530717958647692528676655900576
#define DEG_TO_RAD 0.01745329251994329576923690768488612
#define RAD_TO_DEG 57.2957795130823208767981548141051703

#define rad(_x) ((_x) * (__typeof__(_x)) (DEG_TO_RAD))
#define deg(_x) ((_x) * (__typeof__(_x)) (RAG_TO_DEG))
#define clamp(n,x,v) (v < n ? n : (v > x ? x : v))