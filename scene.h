#ifndef SCENE_H
#define SCENE_H

#include "image.h"
#include "camera.h"

#define MAX_LINES 100

typedef struct {
	bool orthographic;
} SceneSettings;

typedef struct {
	Image* image;
	Camera* active_camera;
	SceneSettings settings;
} Scene;

Scene* load_scene(const char* scene_file);

#endif