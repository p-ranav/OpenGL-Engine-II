#include "window.h"

bool CreateWindow() {
	bool result = false;
	if (!glfwInit()) // initialize GLFW
		result = false;
	else {
		window.handle = glfwCreateWindow(800, 600, "Engine", NULL, NULL); // create GLFW Window
		if (!window.handle)
			result = false;
		else {
			glfwMakeContextCurrent(window.handle); // make OpenGL context current
			glfwSetWindowSizeCallback(window.handle, WindowResizeCallback);
			glewInit(); // initialize GLEW
		}
	}
	return result;
}

bool TerminateWindow() {
	glfwTerminate(); // Terminate window
	return true;
}

void WindowResizeCallback(GLFWwindow * window, int width, int height)
{
	float aspect_ratio = (float)width / (float)height;
	float angle = 45.0f, near_value = 0.1f, far_value = 5000.0f;
	SetProjectionMatrix(angle, aspect_ratio, near_value, far_value);
	SetViewport(0, 0, width, height);
}

bool RenderScene() {
	bool result = false;
	if (!window.handle) // If handle is null, do nothing
		result = false;
	else {
		while (!glfwWindowShouldClose(window.handle)) { // check if window should close
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window
			glClearColor(0.0, 0.0, 0.0, 1.0);
			UpdateCube();
			RenderCube();
			glfwSwapBuffers(window.handle); // swap front and back buffers
			glfwPollEvents(); // poll for events
		}
		result = true;
	}
	return result;
}