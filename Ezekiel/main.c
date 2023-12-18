#include <stdio.h>
#include "state.h"
#include "player.h"
#include "ecs.h"

State state;
ECS ecs;

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
	testGCD.cdtLength = 2;
	testGCD.id = 0xdeadbeef;
	testGCD.dataTable = malloc(testGCD.cdtLength * sizeof(CDM));
	testGCD.dataTable[0] = (CDM){ 16, 76983, 4 };
	testGCD.dataTable[1] = (CDM){ 16, 76983, 16 };

	Component* testComponent = createComponent(&testGCD);
	Component* testComponent2 = createComponent(&testGCD);

	Entity* testEntity = createEntity(0, 0, 0, 0);
	Entity* testEntity2 = createEntity(0, 0, 0, 0);
	Entity* testEntity3 = createEntity(1, testComponent, 0, 0);

	addComponent(testEntity, testComponent2);
	
	u32 testId = addEntity(testEntity);
	testId = addEntity(testEntity2);
	removeEntity(testEntity2);
	testId = addEntity(testEntity3);

	freeEntity(testEntity2);

	createWindow(init, destroy, tick, update, render);
}