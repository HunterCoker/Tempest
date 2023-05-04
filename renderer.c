#include "renderer.h"

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

void render(Scene* scene) {
	// clear color
	fill(scene->image, (Color){ 1.0f, 0.5f, 1.0f, 1.0f });
	// render primitives
	draw_triangle(scene->image, (Vertex){-1.0f, -1.0f, 0.0f}, (Vertex){1.0f, -1.0f, 0.0f}, (Vertex){0.0f, 1.0f, 0.0f});
	// draws final image
	reset_image_texture(scene->image);
	bind_image(scene->image);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void put_pixel(Image* img, int x, int y, Color color) {
	unsigned int result = rgba_to_hex(color[0], color[1], color[2], color[3]);
	img->data[y * img->width + x] = result;
}

void fill(Image* img, Color color) {
	unsigned int result = rgba_to_hex(color[0], color[1], color[2], color[3]);
	for (int i = 0; i < img->width * img->height; i++)
		img->data[i] = result;
}

void draw_triangle(Image* img, Vertex v1, Vertex v2, Vertex v3) {
	// for (int y = 0; y < img->height; y++) {
	// 	for (int x = 0; x < img->width; x++) {
	// 		// calculate barycentric cooridantes
  
	// 	}	
	// }
}

// int screenshot(const char* file_name) {
// 	stbi_flip_vertically_on_write(1);
// 	if (!stbi_write_png(file_name, width, height, 4, data, width * sizeof(uint32_t)))
// 	{
// 		std::cout << "ERROR::Could not write output image file::" << std::endl;
// 		return -1;
// 	}
// 	return 1;
// }
