#pragma once

#include "camera.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

typedef struct InputInfo {
	int key_w, key_a, key_s, key_d, key_q, key_e;
	bool is_key_pressed;
	const float camera_translation_speed = 0.1f;
	glm::vec3 camera_translation;

	InputInfo() {
		camera_translation = glm::vec3();
	}
} InputInfo;

extern InputInfo input;

void KeyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods); // key press callback