#include <stdio.h>
#include "window.h"
#include "renderer.h"

void init() {
	rectangle();
}
void destroy() {

}
void tick() {
	
}
void update() {
}
void render() {
	rectangle();
}

int main(void)
{
	createWindow(init, destroy, tick, update, render);
}