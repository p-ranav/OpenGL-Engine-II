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
			glewInit(); // initialize GLEW
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
	if (!window.handle) // If handle is null, do nothing
		result = false;
	else {
		while (!glfwWindowShouldClose(window.handle)) { // check if window should close
			glClear(GL_COLOR_BUFFER_BIT); // clear window
			glfwSwapBuffers(window.handle); // swap front and back buffers
			glfwPollEvents(); // poll for events
		}
		result = true;
	}
	return result;
}