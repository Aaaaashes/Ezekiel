#pragma once
#include <stdbool.h>

#include "utils.h"
#include "glfx.h"

typedef struct Texture {
	u32 width, height, nrChannels, glTex, colorMode;
	unsigned char* data;
	bool success;
} Texture;

void texCreateGl(Texture* tex);
void texBindGl(Texture tex, u32 texNum);
void texLoadFromFile(Texture* tex, const char* path, u32 colorMode);
void texGlLoadData(Texture tex);
void texFreeData(Texture* tex);
