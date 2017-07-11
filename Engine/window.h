#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <memory>

static GLFWwindow* handle; // GLFW window handle

bool CreateWindow(const uint_fast16_t width = 800, const uint_fast16_t height = 600, const char * title = "Engine"); // Creates a GLFW window
bool Render(); // Run application's render loop
bool TerminateWindow(); // Terminates window