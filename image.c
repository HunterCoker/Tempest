#include "image.h"

#include <stdlib.h>

#include "shader.h"

unsigned int rgba_to_hex(float r, float g, float b, float a) {
	// clamp rgba values 0 >= r/g/b/a >= 1
	unsigned char _r = (unsigned char)(r * 0xff);
	unsigned char _g = (unsigned char)(g * 0xff);
	unsigned char _b = (unsigned char)(b * 0xff);
	unsigned char _a = (unsigned char)(a * 0xff);
	unsigned int result = (_a << 24) | (_b << 16) | (_g << 8) | _r;
	return result;
}

Image* create_image(int width, int height) {
	Image* img = malloc(sizeof(Image));
	img->width = width;
	img->height = height;
	img->data = (unsigned int*)malloc(width * height * sizeof(unsigned int));

	// generate vertex array for screen rendering
	glGenVertexArrays(1, &img->vertex_array);
	glBindVertexArray(img->vertex_array);
	glGenTextures(1, &img->texture);
	puts("gen vertex array OK");

	// generate texture to visualize data
	glBindTexture(GL_TEXTURE_2D, img->texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	puts("gen texture OK");

	// generate OpenGL shader program to render screen texture
	Shader* shader = create_shader();
	bind_shader(shader);
	puts("gen shader OK");

	return img;
}

void put_pixel(Image* img, int x, int y, unsigned int color) {
	img->data[y * img->width + x] = color;
}

void fill_image(Image* img, void* data) {

	for (int y = 0; y < img->height; y++) {
		for (int x = 0; x < img->width; x++) {
			unsigned int color = rgba_to_hex(0.5f, 0.0f, 1.0f, 0.0f);
			put_pixel(img, x, y, color);
		}
	}

	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, img->width, img->height, GL_RGBA, GL_UNSIGNED_BYTE, (void*)img->data);
	puts("image fill OK");
}

// int write_to_file(const char* file_name) {
// 	stbi_flip_vertically_on_write(1);
// 	if (!stbi_write_png(file_name, width, height, 4, data, width * sizeof(uint32_t)))
// 	{
// 		std::cout << "ERROR::Could not write output image file::" << std::endl;
// 		return -1;
// 	}
// 	return 1;
// }