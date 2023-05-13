#include "game.h"

#include <stdio.h>

#include "renderer.h"

int game_init(int width, int height) {
	return 0;
}

void game_update(Scene* scene, GameSettings* settings, double dt) {
	static double time;

	// don't update anything gameplay related if paused
	if (settings->paused)
		return;
	
	// poll for input

	// update oscillating movement using 'total_time'
	
	// update physics using 'dt'
	
	// render final output
	render(scene, time);

	time += dt * 1000.0;
}

void poll_input() {
	// return a queue of all keys pressed
	return;
}
