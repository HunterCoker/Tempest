#ifndef IMAGE_H
#define IMAGE_H

#include <glad/glad.h>
#include <cglm/vec3.h>

typedef struct {
	int width, height;
	GLuint vertex_array, texture;
	unsigned int* data;	
} Image;

/* setup */ 
Image* create_image(int width, int height);
void bind_image(Image* img);

/* image utility functions */
void set_image_data(Image* img, const void* data);
void reset_image_texture(Image* img);

#endif