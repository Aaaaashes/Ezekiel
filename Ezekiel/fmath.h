#pragma once

#define PI   3.14159265358979323846264338327950288
#define PI_2 1.57079632679489661923132169163975144
#define TAU  6.28318530717958647692528676655900576

#define rad(_x) ((_x) * (__typeof__(_x)) (PI / 180.0f))
#define clamp(n,x,v) (v < n ? n : (v > x ? x : v))