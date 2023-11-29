#pragma once
#include "window.h"
#include "renderer.h"
#include "utils.h"

typedef struct State {
	Window* window;
	Renderer renderer;

	usize ticks;
} State;

extern State state;