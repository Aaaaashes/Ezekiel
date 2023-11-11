#pragma once

#include "glfx.h"
#include "utils.h"
#include "error.h"
#include "input.h"

typedef struct Window {
	GLFWwindow* handle;
	vec2 size;
	callback_t init, destroy, tick, update, render;
	f64 lastTime, currentTime;
	u32 frameCount, tickCount;

	u16 scrWidth, scrHeight;

	Keyboard keyboard;
	Mouse mouse;
} Window;

static void _errorCallback(int error, const char* description);
static void _keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void _resizeCallback();

void createWindow(callback_t init, callback_t destroy, callback_t tick, callback_t update, callback_t render);
void windowLoop();

void showFPS();

extern Window window; // GLOBAL global window