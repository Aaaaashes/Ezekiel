#include "VBO.h"

u32 vboCreate() {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    return vbo;
}

void vboDestroy(GLuint vbo) {
    glDeleteBuffers(1, &vbo);
}

void vboBind(GLuint vbo) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void vboUnbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vboBuffer(GLuint vbo, void *data, usize offset, usize count) {
    vboBind(vbo);
    glBufferData(GL_ARRAY_BUFFER, count - offset, data, GL_STATIC_DRAW);
}