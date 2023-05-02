#ifndef IMAGE_H
#define IMAGE_H

#include <glad/glad.h>

typedef struct
{
	int width, height;
	GLuint vertex_array, texture;
	unsigned int* data;	
} Image;

/* setup */ 
Image* create_image(int width, int height);

/* filling image */
void put_pixel(Image* img, int x, int y, unsigned int color);
void fill_image(Image* img, const void* data);
// void fill_subimage(Image* img, int x, int y, int w, int h, const void* data);

/* displaying image */
void draw_image(Image* img);
// int write_to_file(const char* file_name);

#endif