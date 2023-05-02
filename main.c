#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "shader.h"
#include "image.h"

#define WIDTH 320
#define HEIGHT 240

int main(void) {
	
	/* initialize glfw and create window */
	if (!glfwInit()) {
		puts("Failed to initialize GLFW");
		return -1;
	}

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Tempest", NULL, NULL);
	glfwMakeContextCurrent(window);
	
	/* initialize glad */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		puts("Failed to initialize GLAD");
		return -1;
	}

	glViewport(0, 0, WIDTH, HEIGHT);

	/* generate and bind shader */
	Shader* shader = create_shader();
	bind_shader(shader);

	/* create and fill image */
	Image* img = create_image(WIDTH, HEIGHT);
	for (int y = 0; y < img->height; y++) {
		for (int x = 0; x < img->width; x++) {
			float r = (float)x / img->width;
			float g = (float)y / img->height;
			Color color = { r, g, 0.0f, 1.0f };
			put_pixel(img, x, y, color);
		}
	}
	reset_image_texture(img);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		/* render image onto screen */
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		bind_image(img);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
	}
	
	return 0;
}