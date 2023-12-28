#pragma once

#include "glfx.h"
#include <time.h>

#define NSPS (1000000000)
#define NSPMS (1000000)

static inline uint64_t NOW() {
    struct timespec ts;
    int success = timespec_get(&ts, TIME_UTC);
    return (ts.tv_sec * NSPS + ts.tv_nsec);
    free(&success);
}