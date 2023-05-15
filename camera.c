#include "camera.h"

Camera* create_camera(float fov, float aspect, float znear, float zfar) {
	Camera* camera = (Camera*)malloc(sizeof(Camera));

	camera->fov = fov;
	camera->aspect = aspect;
	camera->znear = znear;
	camera->zfar = zfar;
	
	camera->position[0] = 0.0f;
	camera->position[1] = 0.0f;
	camera->position[2] = 0.0f;

	camera->up[0] = 0.0f;
	camera->up[1] = 1.0f;
	camera->up[2] = 0.0f;

	camera->forward[0] =  0.0f;
	camera->forward[1] =  0.0f;
	camera->forward[2] = -1.0f;

	mat4 p; glm_perspective(fov, aspect, znear, zfar, p);
	mat4 v; glm_lookat(camera->position, camera->forward, camera->up, v);
	glm_mat4_mul(p, v, camera->view_projection);

	return camera;
}

void update_view_projection(Camera* camera) {
	mat4 p; glm_perspective(camera->fov, camera->aspect, camera->znear, camera->zfar, p);
	mat4 v; glm_lookat(camera->position, camera->forward, camera->up, v);
	glm_mat4_mul(p, v, camera->view_projection);
}

void move_camera_to_position(Camera* camera, vec3 position) {
	camera->position[0] = position[0];
	camera->position[1] = position[1];
	camera->position[2] = position[2];
}

void move_camera(Camera* camera, vec3 direction, float factor) {
	glm_vec3_scale(direction, factor, direction);
	glm_vec3_add(camera->position, direction, camera->position);
}

void move_forward(Camera* camera, float factor) {
	vec3 tmp;
	glm_vec3_scale(camera->forward, factor, tmp);
	glm_vec3_add(camera->position, tmp, camera->position);
}

void move_up(Camera* camera, float factor) {
	vec3 tmp;
	glm_vec3_scale(camera->up, factor, tmp);
	glm_vec3_add(camera->position, tmp, camera->position);
}
