#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <cglm/cglm.h>

typedef struct {
	GLuint program;
} Shader;

/* setup */
Shader* create_shader();

/* bind / unbind */
void bind_shader(Shader* shader);
void unbind_shader(Shader* shader);

/* set uniforms */
// void set_uniform_1i(Shader* shader, const char* name, int value);
// void set_uniform_1f(Shader* shader, const char* name, float value);
// void set_uniform_2f(Shader* shader, const char* name, const vec2* value);
// void set_uniform_3f(Shader* shader, const char* name, const vec3* value);
// void set_uniform_4f(Shader* shader, const char* name, const vec4* value);
// void set_uniform_mat4(Shader* shader, const char* name, const mat4* value);

#endif