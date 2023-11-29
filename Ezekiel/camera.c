#include "camera.h"
#include "state.h"

Window window;

void perspCamInit(PerspectiveCamera* self, f32 fov) {
	memset(self, 0, sizeof(PerspectiveCamera));
    self->fov = fov;
    self->znear = 0.01f;
    self->zfar = 1000.0f;
    perspCamUpdate(self);
}

void perspCamUpdate(PerspectiveCamera* self) {
    self->aspect = (f32)state.window->scrWidth / (f32)state.window->scrHeight; // window size is subject to change

    self->pitch = clamp(-PI_2, PI_2, self->pitch);
    self->yaw = (self->yaw < 0 ? TAU : 0.0f) + fmodf(self->yaw, TAU);

    self->direction[0] = cosf(self->pitch) * sinf(self->yaw);
    self->direction[1] = sinf(self->pitch);
    self->direction[2] = cosf(self->pitch) * cosf(self->yaw);

    glm_vec3_normalize(self->direction);

    glm_vec3_cross((vec3) { 0.0f, 1.0f, 0.0f }, self->direction, self->right);
    glm_vec3_cross(self->direction, self->right, self->up);

    glm_normalize(self->right);
    glm_normalize(self->up);

    vec3 lookAt;
    glm_vec3_add(self->position, self->direction, lookAt); // get the point we are looking at
    glm_lookat(self->position, lookAt, self->up, self->view_proj.view); // generate view matrix
    glm_perspective(glm_rad(self->fov), self->aspect, self->znear, self->zfar, self->view_proj.proj); // generate projection matrix
}

void orthoCamInit(OrthoCamera* self, vec2 min, vec2 max) {
    memset(self, 0, sizeof(OrthoCamera));
    glm_vec2_copy(min, self->min);
    glm_vec2_copy(max, self->max);
    orthoCamUpdate(self);
}

void orthoCamUpdate(OrthoCamera* self) {
    glm_mat4_identity(self->view_proj.view);
    // glm_translate_make(self->view_proj.view, self->position);
    glm_ortho(self->min[0], self->max[0], self->min[1], self->max[1], -100, 100, self->view_proj.proj);
}