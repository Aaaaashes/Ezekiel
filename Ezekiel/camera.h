#pragma once

#include <stdbool.h>

#include "glfx.h"
#include "utils.h"
#include "window.h"


enum CameraType {
	CAMERA_ORTHO, CAMERA_PERSPECTIVE
};

typedef struct ViewProj {
    mat4 view, proj;
} ViewProj;

typedef struct OrthoCamera {
    ViewProj view_proj;
    vec2 position, min, max;
} OrthoCamera;

typedef struct PerspectiveCamera {
    ViewProj view_proj;
    vec3 position, direction, up, right;
    f32 pitch, yaw, roll, fov, aspect, znear, zfar;
} PerspectiveCamera;

void perspCamInit(PerspectiveCamera* self, f32 fov);
void perspCamUpdate(PerspectiveCamera* self);

void orthoCamInit(OrthoCamera* self, vec2 min, vec2 max);
void orthoCamUpdate(OrthoCamera* self);
