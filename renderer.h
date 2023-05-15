#ifndef RENDERER_H
#define RENDERER_H

#include <cglm/cglm.h>
#include "scene.h"
#include "image.h"
#include "camera.h"

typedef struct {
	bool wireframe;
	bool anti_aliasing;
	bool bloom;
	// add more...
} RenderSettings;

typedef struct {
	vec3 v1;
	vec3 v2;
} Line;


typedef vec4 Color;

/* main render function */
void render(Scene* scene, float time);

/* general pixel coloring */
void put_pixel(Image* img, int x, int y, Color color);
void fill(Image* img, Color color);

void project_scene(Scene* scene);
void clip_scene(Scene* scene);
void draw_scene_data(Scene* scene);

/* primitives */
void draw_line(Image* img, vec2 p1, vec2 p2, vec2 color);
void draw_line_2D(Image* img, vec2 p1, vec2 p2, Color color);
void draw_filled_triangle(Image* img, vec2 v1, vec2 v2, vec2 v3, Color color);
void draw_wireframe_triangle(Image* img, vec2 v1, vec2 v2, vec2 v3, Color color);

/* UI */

/* triggered functions */
// int screenshot(const char* file_name);

#endif