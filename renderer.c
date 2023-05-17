#include "renderer.h"

void render(Scene* scene, float time) {
	// clear color
	fill(scene->image, (Color){ 0.2f, 0.5f, 0.2f, 1.0f });
	update_view_projection(scene->active_camera);

	// project & clip scene geometry data
	project_scene(scene);
	clip_scene(scene);

	Color line_color = { 0.25f, 0.25f, 0.25f, 1.0f };
	vec4 vp = { 0.0f, 0.0f, (float)scene->image->width, (float)scene->image->height };
	for (int i = -10; i <= 10; i++) {
		Line line;
		line.v1[0] = -10.0f;
		line.v1[1] =  0.0f;
		line.v1[2] =  (float)i;
		line.v2[0] =  10.0f;
		line.v2[1] =  0.0f;
		line.v2[2] =  (float)i;
		glm_project(line.v1, scene->active_camera->view_projection, vp, line.v1);
		glm_project(line.v2, scene->active_camera->view_projection, vp, line.v2);
		draw_line(scene->image, line.v1, line.v2, line_color);
	}
	for (int i = -10; i <= 10; i++) {
		Line line;
		line.v1[0] =  (float)i;
		line.v1[1] =  0.0f;
		line.v1[2] =  10.0f;
		line.v2[0] =  (float)i;
		line.v2[1] =  0.0f;
		line.v2[2] = -10.0f;
		glm_project(line.v1, scene->active_camera->view_projection, vp, line.v1);
		glm_project(line.v2, scene->active_camera->view_projection, vp, line.v2);
		draw_line(scene->image, line.v1, line.v2, line_color);
	}

	// draw final image
	reset_image_texture(scene->image);
	bind_image(scene->image);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

unsigned int rgba_to_hex(float r, float g, float b, float a) {
	// clamp rgba values 0 >= r/g/b/a >= 1
	unsigned char _r = (unsigned char)(r * 0xff);
	unsigned char _g = (unsigned char)(g * 0xff);
	unsigned char _b = (unsigned char)(b * 0xff);
	unsigned char _a = (unsigned char)(a * 0xff);
	unsigned int result = (_a << 24) | (_b << 16) | (_g << 8) | _r;
	return result;
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

void project_scene(Scene* scene) {
	/* go through every scene object and project it into 3d space
	vec4 vp = { 0.0f, 0.0f, (float)scene->image->width, (float)scene->image->height };
	for mesh in scene {
		for triangle in mesh {
			for vertex in triangle {
				glm_project(vertex, scene->active_camera->view_projection, vp, vertex);
			}
		}
	}
	*/
}

void clip_scene(Scene* scene) {
	/* test if projected vertex lies outside of the clip coordinate frustum
	if (0.0f < proj[0] && proj[0] < 1.0f * img->width  && 
		0.0f < proj[1] && proj[1] < 1.0f * img->height &&
		0.0f < proj[2] && proj[2] < 1.0f) {
		// inside frustum
	}
	*/
}

// fix so that start and end do not need to be converted to vec3
void draw_line_2D(Image* img, vec2 start, vec2 end, Color color) {
	return;
}

void draw_line(Image* img, vec3 v1, vec3 v2, Color color) {
	ivec2 p1, p2;
	p1[0] = (int)v1[0];
	p1[1] = (int)v1[1];
	p2[0] = (int)v2[0];
	p2[1] = (int)v2[1];

	int dx = p2[0] - p1[0];
	int dy = p2[1] - p1[1];
	if (dx == 0 && dy == 0) {
		if (0 <= p1[0] && p1[0] < img->width && 0 <= p1[1] && p1[1] < img->height)
			put_pixel(img, (int)p1[0], (int)p1[1], color);
		return;
	}

	if (abs(dx) > abs(dy)) {
		// draw line from left to right
		if (p1[0] > p2[0]) {
			ivec2 tmp = { p1[0], p1[1] };
			p1[0] = p2[0]; p1[1] = p2[1];
			p2[0] = tmp[0]; p2[1] = tmp[1];
		}
		// cull line out of view
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
		// draw line from bottom to top
		if (p1[1] > p2[1]) {
			ivec2 tmp = { p1[0], p1[1] };
			p1[0] = p2[0]; p1[1] = p2[1];
			p2[0] = tmp[0]; p2[1] = tmp[1];
		}
		// cull line out of view
		if (p1[1] > img->height - 1) return;
		if (p2[1] < 0) return;

		int y = p1[1] < 0 ? 0 : p1[1];
		for (; y <= p2[1]; y++) {
			if (y > img->height) break;
			int x = (dx * (y - p1[1]) / dy) + p1[0];
			if (0 <= x && x < img->width)
				put_pixel(img, x, y, color);
		}
	}
}

bool triangle_bounding_box(Image* img, ivec2 v1, ivec2 v2, ivec2 v3, int* l, int* r, int* t, int* b) {
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

bool barycentric_coordinates(ivec2 v1, ivec2 v2, ivec2 v3, int x, int y, int* u1, int* u2, int* u3, int* det) {
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

// TODO: change method of drawing triangles (brasenham scanline method)
void draw_filled_triangle(Image* img, vec3 v1, vec3 v2, vec3 v3, Color color) {
	// convert normalized device coordinates into pixel coordinates
	ivec2 p1, p2, p3;
	// ndc_to_pixel_triangle(img, v1, v2, v3, p1, p2, p3);

	// cull triangle if backfacing
	// int sum = 0;
	// sum += (p2[0] - p1[0]) * (p2[1] + p1[1]);
	// sum += (p3[0] - p2[0]) * (p3[1] + p2[1]);
	// sum += (p1[0] - p3[0]) * (p1[1] + p3[1]);
	// if (sum < 0) return;

	// use barycentric coordinates to determing whether a point is in the triangle
	int l, r, t, b;
	if (triangle_bounding_box(img, p1, p2, p3, &l, &r, &t, &b)) {
		for (int y = b; y < t; ++y) {
			for (int x = l; x < r; ++x) {
				int u1, u2, u3, det; 
				if (barycentric_coordinates(p1, p2, p3, x, y, &u1, &u2, &u3, &det)) {
					put_pixel(img, x, y, color);
				}
			}
		}
	}
}

void draw_wireframe_triangle(Image* img, vec3 v1, vec3 v2, vec3 v3, Color color) {
	draw_line(img, v1, v2, color);
	draw_line(img, v2, v3, color);
	draw_line(img, v1, v3, color);
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
