#include "image.h"

#include <stdlib.h>

Image* create_image(int width, int height) {
	Image* img = malloc(sizeof(Image));
	img->width = width;
	img->height = height;
	img->data = (unsigned int*)malloc(width * height * sizeof(unsigned int));

	// generate vertex array for screen rendering
	glGenVertexArrays(1, &img->vertex_array);
	glBindVertexArray(img->vertex_array);

	// generate texture to visualize data
	glGenTextures(1, &img->texture);
	glBindTexture(GL_TEXTURE_2D, img->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	
	return img;
}

void bind_image(Image* img) {
	// unbind any other bound image
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	// bind this image
	glBindVertexArray(img->vertex_array);
	glBindTexture(GL_TEXTURE_2D, img->texture);
}

void set_image_data(Image* img, void* data) {
	free(img->data);
	img->data = (unsigned int*)data;
}

void reset_image_texture(Image* img) {
	bind_image(img);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, img->width, img->height, GL_RGBA, GL_UNSIGNED_BYTE, (void*)img->data);
}