#include "shader.h"

#include <stdio.h>

const char* v_shader_code =
	"#version 330 core\n"
	"out vec2 texcoord;\n"
	"void main()\n"
	"{\n"
	"	vec2 vertices[3]=vec2[3](vec2(-1,-1), vec2(3,-1), vec2(-1, 3));\n"
	"	gl_Position = vec4(vertices[gl_VertexID],0,1);\n"
	"	texcoord = 0.5 * gl_Position.xy + vec2(0.5);\n"
	"}\0";
const char* f_shader_code =
	"#version 330 core\n"
	"out vec4 outcolor;\n"
	"in vec2 texcoord;\n"
	"uniform sampler2D sampler;\n"
	"void main()\n"
	"{\n"
	"	outcolor = texture(sampler, texcoord);\n"
	"}\0";

Shader* create_shader() {
	Shader* shader = (Shader*)malloc(sizeof(Shader));
    unsigned int vertex_shader, fragment_shader;
    // vertex shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &v_shader_code, NULL);
    glCompileShader(vertex_shader);
    // fragment shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &f_shader_code, NULL);
    glCompileShader(fragment_shader);

    // shader program
    shader->program = glCreateProgram();
    glAttachShader(shader->program, vertex_shader);
    glAttachShader(shader->program, fragment_shader);
    glLinkProgram(shader->program);
    // delete shaders
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

	return shader;
}

void bind_shader(Shader* shader) {
	glUseProgram(shader->program);
}

void unbind_shader(Shader* shader) {
	glUseProgram(0);
}

// void set_uniform_1i(Shader* shader, const char* name, int value) {
//     glUniform1i(glGetUniformLocation(shader->program, name), value);
// }

// void set_uniform_1f(Shader* shader, const char* name, float value) {
//     glUniform1f(glGetUniformLocation(shader->program, name), value);
// }

// void set_uniform_2f(Shader* shader, const char* name, const vec2* value) {
//     glUniform2f(glGetUniformLocation(shader->program, name), *value[0], *value[1]);
// }

// void set_uniform_3f(Shader* shader, const char* name, const vec3* value) {
//     glUniform3f(glGetUniformLocation(shader->program, name), *value[0], *value[1], *value[2]);
// }

// void set_uniform_4f(Shader* shader, const char* name, const vec4* value) {
//     glUniform4f(glGetUniformLocation(shader->program, name), *value[0], *value[1], *value[2], *value[3]);
// }

// void set_uniform_mat4(Shader* shader, const char* name, const mat4* value) {
//     glUniformMatrix4fv(glGetUniformLocation(shader->program, name), 1, GL_FALSE, value);
// }