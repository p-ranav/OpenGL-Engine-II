#pragma once

#include "scene.h"
#include "input.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <memory>
#include <functional>

typedef struct Window {
	uint_fast16_t width;
	uint_fast16_t height;
	const char * title;
	GLFWwindow * handle;
} Window;

extern Window window; // global window object

bool CreateWindow(const uint_fast32_t width = 800, const uint_fast32_t height = 600, const char * title = "Engine"); // create a GLFW window
bool TerminateWindow(); // terminate the GLFW window
void WindowResizeCallback(GLFWwindow* window, int width, int height); // called when window is resized