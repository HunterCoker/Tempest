#ifndef IMAGE_H
#define IMAGE_H

#include <glad/glad.h>
#include <cglm/vec3.h>

typedef struct {
	int width, height;
	GLuint vertex_array, texture;
	unsigned int* data;	
} Image;

typedef vec4 Color;

/* setup */ 
Image* create_image(int width, int height);
void bind_image(Image* img);

/* filling image */
void put_pixel(Image* img, int x, int y, Color color);
void set_image_data(Image* img, const void* data);
void reset_image_texture(Image* img);
// void fill_subimage(Image* img, int x, int y, int w, int h, const void* data);

/* displaying image */
void draw_to_screen(Image* img);
// int draw_to_file(const char* file_name);

#endif