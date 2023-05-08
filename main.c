#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <time.h>

#include "shader.h"
#include "game.h"
#include "scene.h"

#define WIDTH 320
#define HEIGHT 240

// render pipeline in a nutshell
// 0. load scene (everything meant to be loaded)
//  - lights (position/direction/type)
//  - meshes & animations (.gltf files)
//  - sprites (.png files)
//  - audio (.ogg files)
// |---- per frame --------------------------------------|
// 1. calculate physics
// 2. generate pixel data based on current scene geometry
//  - steps...
// 3. render frame (Image)
// |-----------------------------------------------------|

int main(void) {
	/* initialize glfw and create window */
	if (!glfwInit()) {
		puts("Failed to initialize GLFW");
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Tempest", NULL, NULL);
	glfwMakeContextCurrent(window);
	
	/* initialize glad */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		puts("Failed to initialize GLAD");
		return -1;
	}
	glViewport(0, 0, WIDTH, HEIGHT);
	glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	/* generate and bind shader */
	Shader* shader = create_shader();
	bind_shader(shader);

	/* initialize the game settings */
	GameSettings settings;
	settings.paused = false;

	/* load main menu scene */
	Scene* scene = load_scene("main_menu.yaml");

	/* initialize timers */
	double start, stop, dt;
	start = glfwGetTime();

	/* game loop */
	while (!glfwWindowShouldClose(window)) {
		/* poll for window events */
		glfwPollEvents();

		/* update deltatime (milliseconds) */
		stop = glfwGetTime();
		dt = (double)(stop - start) / 1000.0;
		start = stop;

		/* update game */
		game_update(scene, &settings, dt);		

		glfwSwapBuffers(window);
	}
	
	return 0;
}