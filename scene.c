#include "scene.h"
#include "renderer.h"

// todo: use width and height from file instead of using constants
Scene* load_scene(const char* scene_file) {
	Scene* scene = (Scene*)malloc(sizeof(Scene));

	// fill scene object with gameobjects laid out in the scene file
	scene->image = create_image(320, 240);
	fill(scene->image, (Color){ 0.0f, 0.0f, 1.0f, 1.0f });
	
	float fov = 45.0f;
	float aspect = (float)scene->image->width / scene->image->height;
	float znear = 0.1f;
	float zfar = 100.0f;
	scene->active_camera = create_camera(fov, aspect, znear, zfar);

	// set scene settings
	scene->settings.orthographic = false;

	return scene;
}