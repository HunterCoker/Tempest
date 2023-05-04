#include "game.h"

#include <stdio.h>

#include "renderer.h"

Scene* game_init(int width, int height) {
	/* load main menu scene */
	Scene* scene = load_scene("main_menu.yaml");

	return scene;
}

void game_update(Scene* scene, GameSettings* settings, double dt) {
	static double total_time;

	// don't update anything gameplay related if paused
	if (settings->paused)
		return;

	render(scene);

	total_time += dt * 1000.0;
}
