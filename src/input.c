#include "input.h"

void buttonArrayTick(size_t n, struct Button* buttons) {
    for (size_t i = 0; i < n; i++) {
        buttons[i].pressed_tick = buttons[i].down && !buttons[i].last_tick;
        buttons[i].last_tick = buttons[i].down;
    }
}

void buttonArrayUpdate(size_t n, struct Button* buttons) {
    for (size_t i = 0; i < n; i++) {
        buttons[i].pressed = buttons[i].down && !buttons[i].last;
        buttons[i].last = buttons[i].down;
    }
}