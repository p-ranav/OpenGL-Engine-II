#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <memory>

typedef struct Window {
	uint_fast16_t width;
	uint_fast16_t height;
	char * title;
	GLFWwindow * handle;
} Window;

static Window window;

bool CreateWindow(); // Creates a GLFW window
bool RenderScene(); // Run application's render loop
bool TerminateWindow(); // Terminates window