#ifndef CAMERA_H
#define CAMERA_H

#include "cglm/cglm.h"
#include "image.h"

typedef struct {
	float fov, aspect, znear, zfar;
	vec3 position, up, forward;
	mat4 view_projection;
} Camera;

Camera* create_camera(float fov, float aspect, float znear, float zfar);
void update_view_projection(Camera* camera);

void move_camera_to_position(Camera* camera, vec3 position);
void move_camera(Camera* camera, vec3 direction, float factor);
void move_forward(Camera* camera, float factor);
void move_up(Camera* camera, float factor);

#endif // CAMERA_H