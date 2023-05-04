#ifndef RENDERER_H
#define RENDERER_H

#include <cglm/cglm.h>
#include "scene.h"
#include "image.h"

typedef vec3 Vertex;
typedef vec4 Color;

/* main render function */
void render(Scene* scene);

/* general pixel coloring */
void put_pixel(Image* img, int x, int y, Color color);
void fill(Image* img, Color color);

/* primitives */
void draw_triangle(Image* img, Vertex v1, Vertex v2, Vertex v3);

/* triggered functions */
// int screenshot(const char* file_name);

#endif