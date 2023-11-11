#include "VAO.h"

GLuint vaoCreate() {
	u32 vao;
	glGenVertexArrays(1, &vao);
	return vao;
}
void vaoDestroy(GLuint vao) {
	glDeleteVertexArrays(1, vao);
}
void vaoBind(u32 vao) {
	glBindVertexArray(vao);
}
void vaoUnbind() {
	glBindVertexArray(0);
}