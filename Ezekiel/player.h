#pragma once
#include <stdio.h>
#include "utils.h"
#include "camera.h"
#include "window.h"

typedef struct Player {
	PerspectiveCamera cam;
	vec3 pos, dir;
} Player;

extern Player player; // global player, probably change this

void playerUpdate();

void playerInit();

void playerTick();
