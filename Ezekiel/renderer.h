#pragma once
#include <math.h>

#include "utils.h"
#include "error.h"
#include "glfx.h"
#include "EBO.h"
#include "VBO.h"
#include "VAO.h"
#include "shader.h"
#include "texture.h"
#include "player.h"

typedef struct Renderer {
	u32 VBO, VAO, EBO, shaderProgram;
	char infoLog[512];
	Texture texture1;
} Renderer;

void initRenderer();

void rectangle();