#include "player.h"
#include "state.h"

Player player;

void playerUpdate() {
	player.cam.pitch -= state.window->mouse.delta[1] / ((f32)state.window->dFrame / 45000.0f);
	player.cam.pitch = clamp(-PI_2 + 0.01, PI_2 - 0.01, player.cam.pitch);
	player.cam.yaw -= state.window->mouse.delta[0] / ((f32)state.window->dFrame / 45000.0f);

	perspCamUpdate(&player.cam);
}

void playerInit() {
	perspCamInit(&player.cam, 90.0f);
	player.cam.yaw = 180.0f;
}

void playerTick() {
	f32 cameraSpeed = 0.1;
	vec3 dir;
	glm_vec3_zero(dir);
	if (state.window->keyboard.keys[GLFW_KEY_W].down) {
		glm_vec3_muladds(player.cam.direction, cameraSpeed, dir);
	}
	if (state.window->keyboard.keys[GLFW_KEY_S].down) {
		glm_vec3_muladds(player.cam.direction, -cameraSpeed, dir);
	}
	if (state.window->keyboard.keys[GLFW_KEY_A].down) {
		glm_vec3_muladds(player.cam.right, cameraSpeed, dir);
	}
	if (state.window->keyboard.keys[GLFW_KEY_D].down) {
		glm_vec3_muladds(player.cam.right, -cameraSpeed, dir);
	}

	glm_vec3_add(player.cam.position, dir, player.cam.position);
}
