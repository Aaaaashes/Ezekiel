#pragma once
#include "utils.h"
#include "glfx.h"


u32 eboCreate();
void eboDestroy(u32 ebo);
void eboBind(u32 ebo);
void eboUnbind();
void eboBuffer(u32 ebo, void* data, usize offset, usize count);
