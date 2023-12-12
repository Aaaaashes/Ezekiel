#include <stdio.h>
#include "state.h"
#include "player.h"
#include "ecs.h"

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

	GCD testGCD;
	testGCD.cdtSize = 2 * sizeof(CDM);
	testGCD.dataTable = malloc(testGCD.cdtSize);
	testGCD.dataTable[0] = (CDM){ 16, 76983, 4 };
	testGCD.dataTable[1] = (CDM){ 16, 76983, 16 };

	Component testComponent = { 46, &testGCD, malloc(0)};

	createEntity(1, &testComponent);
	createWindow(init, destroy, tick, update, render);
}