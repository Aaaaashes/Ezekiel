#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void texCreateGl(Texture* tex) {
	glGenTextures(1, &(tex->glTex));
}

void texBindGl(Texture tex, u32 texNum) {
	glActiveTexture(texNum);
	glBindTexture(GL_TEXTURE_2D, tex.glTex);
}

void texLoadFromFile(Texture* tex, const char* path, u32 colorMode) {
	unsigned char* data = stbi_load(path, &tex->width, &tex->height, &tex->nrChannels, 0);
	tex->colorMode = colorMode;
	if (!data) {
		tex->success = false;
		return;
	}
	tex->success = true;
	tex->data = data;
}

void texGlLoadData(Texture tex) {
	glTexImage2D(GL_TEXTURE_2D, 0, tex.colorMode, tex.width, tex.height, 0, tex.colorMode, GL_UNSIGNED_BYTE, tex.data);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void texFreeData(Texture *tex) {
	stbi_image_free(tex->data);
}