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

typedef struct Renderer {
	u32 VBO, VAO, EBO, shaderProgram;
	char infoLog[512];
	Texture texture1;
	vec3 camPos, camDir, camUp, camRight;
	mat4 view, projection;
} Renderer;

void initRenderer();

void updateCamDirs(vec3 lookAt);
void updateCamPos(vec3 pos);
void addCamPos(vec3 inc);
void updateCamMat();
void updateCam(vec3 pos, vec3 lookAt);
void updateProjectionMatrix(u32 w, u32 h);

void rectangle();