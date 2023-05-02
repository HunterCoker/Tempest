#include "image.h"

#include <stdlib.h>

/* utility functions */ 
unsigned int rgba_to_hex(float r, float g, float b, float a) {
	// clamp rgba values 0 >= r/g/b/a >= 1
	unsigned char _r = (unsigned char)(r * 0xff);
	unsigned char _g = (unsigned char)(g * 0xff);
	unsigned char _b = (unsigned char)(b * 0xff);
	unsigned char _a = (unsigned char)(a * 0xff);
	unsigned int result = (_a << 24) | (_b << 16) | (_g << 8) | _r;
	return result;
}

/* implementations */
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
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

void put_pixel(Image* img, int x, int y, Color color) {
	unsigned int result = rgba_to_hex(color[0], color[1], color[2], color[3]);
	img->data[y * img->width + x] = result;
}

void set_image_data(Image* img, void* data) {
	free(img->data);
	img->data = (unsigned int*)data;
}

void reset_image_texture(Image* img) {
	bind_image(img);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, img->width, img->height, GL_RGBA, GL_UNSIGNED_BYTE, (void*)img->data);
}

// int draw_to_file(const char* file_name) {
// 	stbi_flip_vertically_on_write(1);
// 	if (!stbi_write_png(file_name, width, height, 4, data, width * sizeof(uint32_t)))
// 	{
// 		std::cout << "ERROR::Could not write output image file::" << std::endl;
// 		return -1;
// 	}
// 	return 1;
// }