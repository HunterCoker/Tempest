#ifndef SCENE_H
#define SCENE_H

#include "image.h"

typedef struct {
	bool orthographic;
} SceneSettings;

typedef struct {
	Image* image;
	SceneSettings settings;
} Scene;

Scene* load_scene(const char* scene_file);

#endif