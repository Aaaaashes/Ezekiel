#pragma once

#include <time.h>

#define NS_PER_SECOND (1000000000)
#define NS_PER_MS (1000000)

#define NOW() ({\
    struct timespec ts;\
    timespec_get(&ts, TIME_UTC);\
    ((ts.tv_sec * NS_PER_SECOND) + ts.tv_nsec);})