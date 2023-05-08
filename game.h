#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "scene.h"
#include "image.h"

typedef struct {
	bool paused;
} GameSettings;

int  game_init(int width, int height);
void game_update(Scene* scene, GameSettings* settings, double dt);

void poll_input();

#endif