#include "scene.h"
#include "renderer.h"

// todo: use width and height from file instead of using constants
Scene* load_scene(const char* scene_file) {
	Scene* scene = malloc(sizeof(Scene));

	// fill scene object with gameobjects laid out in the scene file
	scene->image = create_image(320, 240);
	fill(scene->image, (Color){ 0.0f, 0.0f, 1.0f, 1.0f });
	
	// set scene settings
	scene->settings.orthographic = false;

	return scene;
}