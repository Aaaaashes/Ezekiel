#pragma once
#include "utils.h"
#include "glfx.h"

GLuint vaoCreate();
void vaoDestroy(u32 vao);
void vaoBind(u32 vao);
void vaoUnbind();

