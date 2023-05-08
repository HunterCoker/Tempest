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
	fill(scene->image, (Color){ 0.2f, 0.5f, 0.2f, 1.0f });
	// get objects in view (copy them)
	draw_triangle(scene->image, (Vertex){-1.0f, -1.0f, 0.0f}, (Vertex){1.0f, -1.0f, 0.0f}, (Vertex){0.0f, 1.0f, 0.0f}, (Color){ 0.5f, 1.0f, 1.0f, 1.0f});
	// transform them into 3D space

	// draw final image
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

void draw_line_2D(Image* img, Vertexi2 p1, Vertexi2 p2, Color color) {
	int dx = p2[0] - p1[0];
	int dy = p2[1] - p1[1];

	if (dx == 0 && dy == 0) {
		if (0 <= p1[0] && p1[0] < img->width && 0 <= p1[1] && p1[1] < img->height)
			put_pixel(img, (int)p1[0], (int)p1[1], color);
		return;
	}

	if (abs(dx) > abs(dy)) {
		// draw lines from left to right
		if (p1[0] > p2[0]) {
			Vertexi2 tmp = { p1[0], p1[1] };
			p1[0] = p2[0]; p1[1] = p2[1];
			p2[0] = tmp[0]; p2[1] = tmp[1];
		}
		// cull lines out of view
		if (p1[0] > img->width) return;
		if (p2[0] < 0) return;

		for (int x = p1[0]; x <= p2[0]; x++) {
			if (x < 0 || x > img->width - 1) continue;
			int y = (dy * (x - p1[0]) / dx) + p1[1];
			if (0 <= y && y < img->height)
				put_pixel(img, x, y, color);
		}
	}
	else {
		// draw lines from bottom to top
		if (p1[1] > p2[1]) {
			Vertexi2 tmp = { p1[0], p1[1] };
			p1[0] = p2[0]; p1[1] = p2[1];
			p2[0] = tmp[0]; p2[1] = tmp[1];
		}
		// cull lines out of view
		if (p1[1] > img->height - 1) return;
		if (p2[1] < 0) return;

		for (int y = p1[1]; y <= p2[1]; y++) {
			if (y < 0 || y > img->height) continue;
			int x = (dx * (y - p1[1]) / dy) + p1[0];
			if (0 <= x && x < img->height)
				put_pixel(img, x, y, color);
		}
	}
}

void draw_triangle(Image* img, Vertex v1, Vertex v2, Vertex v3) {
	// transform vertices onto plane (3D projection)


}

void draw_line(Image* img, Vertex p1, Vertex p2, Color color) {
	return;
}


triangle_bounding_box(Vertex v1, Vertex v2, Vertex v3, int* left, int* right, int* top, int* bottom) {

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
