#include "window.h"

Window window;

bool CreateWindow(const uint_fast32_t width, const uint_fast32_t height, const char * title) {
	bool result = false;
	if (!glfwInit()) // initialize GLFW
		result = false;
	else {
		window.width = width;
		window.height = height;
		window.title = title;
		window.handle = glfwCreateWindow(window.width, window.height, window.title, NULL, NULL); // create GLFW Window
		if (!window.handle)
			result = false;
		else {
			glfwMakeContextCurrent(window.handle); // make OpenGL context current
			glfwSetWindowSizeCallback(window.handle, WindowResizeCallback);
			glfwSetKeyCallback(window.handle, KeyPressCallback);
			glewInit(); // initialize GLEW
		}
	}
	return result;
}

bool TerminateWindow() {
	glfwTerminate(); // Terminate window
	return true;
}

void WindowResizeCallback(GLFWwindow * window_handle, int width, int height) {
	window.width = width;
	window.height = height;
	float aspect_ratio = (float)width / (float)height;
	float angle = 45.0f, near_value = 0.1f, far_value = 1000.0f;
	SetProjectionMatrix(angle, aspect_ratio, near_value, far_value);
	SetViewport(0, 0, width, height);
}