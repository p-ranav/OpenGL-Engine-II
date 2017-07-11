#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <memory>

typedef unsigned int UINT;
static GLFWwindow* handle;

bool CreateWindow(const uint_fast16_t width = 800, 
	const uint_fast16_t height = 600, 
	const char * title = "Engine");
bool Render();
bool TerminateWindow();