#include <stdio.h>
#include "state.h"
#include "player.h"

State state;

void init() {
	state.window = &window;
	playerInit();
	initRenderer();
	rectangle();
}
void destroy() {

}
void tick() {
	playerTick();
}
void update() {
	playerUpdate();
}
void render() {
	rectangle();
}

int main(void)
{
	createWindow(init, destroy, tick, update, render);
}