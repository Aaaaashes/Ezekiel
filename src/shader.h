#pragma once

#include <stdbool.h>
#include <stdio.h>

#include "utils.h"
#include "error.h"
#include "glfx.h"

u32 shaderCreate(const char* vertexPath, const char* fragmentPath);

u32 shaderCompile(const char* source, u32 type, const char* name);

void shaderUse(u32 shaderId);

void shaderSetBool(u32 shaderId, const char* name, bool value);
void shaderSetInt(u32 shaderId, const char* name, i32 value);
void shaderSetFloat(u32 shaderId, const char* name, f32 value);

void shaderSetVec2(u32 shaderId, const char* name, vec2 value);
void shaderSetVec3(u32 shaderId, const char* name, vec3 value);
void shaderSetVec4(u32 shaderId, const char* name, vec4 value);

void shaderSetMat2(u32 shaderId, const char* name, mat2 value);
void shaderSetMat3(u32 shaderId, const char* name, mat3 value);
void shaderSetMat4(u32 shaderId, const char* name, mat4 value);

