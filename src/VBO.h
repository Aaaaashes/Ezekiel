#pragma once

#include <stdbool.h>

#include "utils.h"
#include "glfx.h"

u32 vboCreate();
void vboDestroy(u32 vbo);
void vboBind(u32 vbo);
void vboUnbind();
void vboBuffer(u32 vbo, void* data, usize offset, usize count);


