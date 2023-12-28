#include "EBO.h"


u32 eboCreate() {
	u32 ebo;
	glGenBuffers(1, &ebo);
	return ebo;
}

void eboDestroy(u32 ebo) {
	glDeleteBuffers(1, &ebo);
}

void eboBind(u32 ebo) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void eboUnbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void eboBuffer(u32 ebo, void* data, usize offset, usize count) {
	eboBind(ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count - offset, data, GL_STATIC_DRAW);
}