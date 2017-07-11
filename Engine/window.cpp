#include "window.h"

bool CreateWindow(const uint_fast16_t width, const uint_fast16_t height, const char * title) {
	bool result = false;
	if (!glfwInit()) // Initialize GLFW
		result = false;
	else {
		handle = glfwCreateWindow(width, height, title, NULL, NULL); // Create GLFW Window
		if (!handle)
			result = false;
		else {
			glfwMakeContextCurrent(handle); // Make OpenGL context current
			glewInit(); // Initialize GLEW
		}
	}
	return result;
}

bool TerminateWindow() {
	glfwTerminate(); // Terminate window
	return true;
}

bool RenderScene() {
	bool result = false;
	if (!handle)
		result = false;
	else {
		while (!glfwWindowShouldClose(handle)) {
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(handle);
			glfwPollEvents();
		}
		result = true;
	}
	return result;
}