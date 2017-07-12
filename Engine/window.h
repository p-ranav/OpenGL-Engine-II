#pragma once

#include "scene.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <memory>
#include <functional>

typedef struct Window {
	uint_fast16_t width;
	uint_fast16_t height;
	char * title;
	GLFWwindow * handle;
} Window;

bool CreateWindow(); // create a GLFW window
bool TerminateWindow(); // terminate the GLFW window
void WindowResizeCallback(GLFWwindow* window, int width, int height); // called when window is resized
bool RenderScene(std::vector<std::function<void(void)>> render_functions); // application's render loop