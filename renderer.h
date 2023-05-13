#ifndef RENDERER_H
#define RENDERER_H

#include <cglm/cglm.h>
#include "scene.h"
#include "image.h"

typedef ivec2 Vertexi2;
typedef vec3 Vertex;
typedef vec4 Color;

/* main render function */
void render(Scene* scene, float time);

/* general pixel coloring */
void put_pixel(Image* img, int x, int y, Color color);
void fill(Image* img, Color color);

/* primitives 2D */
// todo: use normalized 
void draw_line_2D(Image* img, Vertexi2 p1, Vertexi2 p2, Color color);

/* primitives 3D */
void draw_line(Image* img, Vertex p1, Vertex p2, Color color);
void draw_filled_triangle(Image* img, Vertex v1, Vertex v2, Vertex v3, Color color);
void draw_wireframe_triangle(Image* img, Vertex v1, Vertex v2, Vertex v3, Color color);

/* triggered functions */
// int screenshot(const char* file_name);

#endif