#pragma once
#include <stdbool.h>

#include "glfx.h"

typedef struct Button {
	bool down, last, last_tick, pressed, pressed_tick;
} Button;

typedef struct Mouse {
    struct Button buttons[GLFW_MOUSE_BUTTON_LAST];
    vec2 position, delta;
} Mouse;

typedef struct Keyboard {
    struct Button keys[GLFW_KEY_LAST];
} Keyboard;

void buttonArrayTick(size_t n, struct Button* buttons);
void buttonArrayUpdate(size_t n, struct Button* buttons);
