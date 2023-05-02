#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#define WIDTH 320
#define HEIGHT 240

int main(void) {
	
	if (!glfwInit()) {
		puts("Failed to initialize GLFW");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Tempest", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		puts("Failed to initialize GLAD");
		return -1;
	}
	glViewport(0, 0, WIDTH, HEIGHT);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		/* Render Here */
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

		glfwSwapBuffers(window);
	}
	
	return 0;
}