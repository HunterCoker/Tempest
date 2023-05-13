#include "renderer.h"

/* private functions */ 
unsigned int rgba_to_hex(float r, float g, float b, float a) {
	// clamp rgba values 0 >= r/g/b/a >= 1
	unsigned char _r = (unsigned char)(r * 0xff);
	unsigned char _g = (unsigned char)(g * 0xff);
	unsigned char _b = (unsigned char)(b * 0xff);
	unsigned char _a = (unsigned char)(a * 0xff);
	unsigned int result = (_a << 24) | (_b << 16) | (_g << 8) | _r;
	return result;
}

void project(vec3 vertex) {

}

void ndc_to_pixel_space(Image* img, Vertex vertex) {
	/* formula to convert NDC to pixel space
	X = (X + 1) * Viewport.Width * 0.5 + Viewport.TopLeftX
	Y = (1 - Y) * Viewport.Height * 0.5 + Viewport.TopLeftY
	Z = Viewport.MinDepth + Z * (Viewport.MaxDepth - Viewport.MinDepth) */
	
	vertex[0] = (vertex[0] + 1.0f) * img->width * 0.5f;
	vertex[1] = (vertex[1] + 1.0f) * img->height * 0.5f;
	vertex[2] = 0.0f;
}

bool triangle_bounding_box(Image* img, vec3 v1, vec3 v2, vec3 v3, int* l, int* r, int* t, int* b) {
	// left bound
	*l = v1[0];
	if (*l > v2[0]) *l = v2[0];
	if (*l > v3[0]) *l = v3[0];
	if (*l > img->width) return false;
	if (*l < 0) *l = 0;
	// right bound
	*r = v1[0];
	if (*r < v2[0]) *r = v2[0];
	if (*r < v3[0]) *r = v3[0];
	if (*r < 0) return false;
	if (*r > img->width) *r = img->width;
	// top bound
	*t = v1[1];
	if (*t < v2[1]) *t = v2[1];
	if (*t < v3[1]) *t = v3[1];
	if (*t < 0) return false;
	if (*t > img->height) *t = img->height;
	// bottom bound
	*b = v1[1];
	if (*b > v2[1]) *b = v2[1];
	if (*b > v3[1]) *b = v3[1];
	if (*b > img->height) return false;
	if (*b < 0) *b = 0;
	return true;
}

void render(Scene* scene, float time) {
	// clear color
	fill(scene->image, (Color){ 0.2f, 0.5f, 0.2f, 1.0f });
	// get objects in view (copy them)

	// project coordinates from 3D space onto screen space
	Vertex v1 = { (float)cos(time) / 2.0f,  (float)cos(time) / 2.0f, -3.0f };
	Vertex v2 = { -0.5f, 0.5f, -5.0f };
	Vertex v3 = {  0.5f, -0.5f, -1.0f };

	Color color = { 1.0f, 0.0f, 0.0f, 1.0f };
	
	/* draw_line_2D example: */
	// Vertexi2 p1 = { 500, 30 };
	// Vertexi2 p2 = { -20, 300 };
	// draw_line_2D(scene->image, p1, p2, color);

	/* draw_triangle example */
	draw_filled_triangle(scene->image, v1, v2, v3, color);
	
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
		
		int x = p1[0] < 0 ? 0 : p1[0];
		for (; x <= p2[0]; x++) {
			if (x > img->width - 1) break;
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

		int y = p1[1] < 0 ? 0 : p1[1];
		for (; y <= p2[1]; y++) {
			if (y > img->height) break;
			int x = (dx * (y - p1[1]) / dy) + p1[0];
			if (0 <= x && x < img->height)
				put_pixel(img, x, y, color);
		}
	}
}

void draw_line(Image* img, Vertex p1, Vertex p2, Color color) {
	return;
}

bool barycentric_coordinates(vec3 v1, vec3 v2, vec3 v3, int x, int y, int* u1, int* u2, int* u3, int* det) {
    *det = ((v1[0] - v3[0])*(v2[1] - v3[1]) - (v2[0] - v3[0])*(v1[1] - v3[1]));
    *u1  = ((v2[1] - v3[1])*(x - v3[0]) + (v3[0] - v2[0])*(y - v3[1]));
    *u2  = ((v3[1] - v1[1])*(x - v3[0]) + (v1[0] - v3[0])*(y - v3[1]));
    *u3 = *det - *u1 - *u2;
	// if u1, u2, and u3 are all the same sign as the determinant, then point x, y is within the triangle
	return (
		((*u1 ^ *det) >= 0 || *u1 == 0) &&
		((*u2 ^ *det) >= 0 || *u2 == 0) &&
		((*u3 ^ *det) >= 0 || *u3 == 0)
	);
}

void draw_filled_triangle(Image* img, Vertex v1, Vertex v2, Vertex v3, Color color) {
	// convert normalized device coordinates into pixel coordinates
	ndc_to_pixel_space(img, v1);
	ndc_to_pixel_space(img, v2);
	ndc_to_pixel_space(img, v3);

	// cull triangle if backfacing
	int sum = 0;
	sum += (v2[0] - v1[0]) * (v2[1] + v1[1]);
	sum += (v3[0] - v2[0]) * (v3[1] + v2[1]);
	sum += (v1[0] - v3[0]) * (v1[1] + v3[1]);
	if (sum < 0) return;

	// use barycentric coordinates to determing whether a point is in the triangle
	int l, r, t, b;
	if (triangle_bounding_box(img, v1, v2, v3, &l, &r, &t, &b)) {
		for (int y = b; y < t; ++y) {
			for (int x = l; x < r; ++x) {
				int u1, u2, u3, det; 
				if (barycentric_coordinates(v1, v2, v3, x, y, &u1, &u2, &u3, &det)) {
					put_pixel(img, x, y, color);
				}
			}
		}
	}
}

void draw_wireframe_triangle(Image* img, Vertex v1, Vertex v2, Vertex v3, Color color) {
	ndc_to_pixel_space(img, v1);
	ndc_to_pixel_space(img, v2);
	ndc_to_pixel_space(img, v3);
	draw_line_2D(img, (ivec2){ (int)v1[0], (int)v1[1] }, (ivec2){ (int)v2[0], (int)v2[1] }, color);
	draw_line_2D(img, (ivec2){ (int)v2[0], (int)v2[1] }, (ivec2){ (int)v3[0], (int)v3[1] }, color);
	draw_line_2D(img, (ivec2){ (int)v1[0], (int)v1[1] }, (ivec2){ (int)v3[0], (int)v3[1] }, color);
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
