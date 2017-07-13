#pragma once

#include "camera.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include "gtx\quaternion.hpp"

typedef struct InputInfo {
	int key_w, key_a, key_s, key_d, key_q, key_e; // list of keys supported
	bool is_key_pressed; // is some key pressed?

	const float camera_translation_speed = 0.1f; // translation speed of the camera
	glm::vec3 camera_translation; // camera translation to be applied when key is pressed

	glm::ivec2 mouse_position; // mouse position saved in the MouseMoveCallback
	const float camera_rotation_speed = 0.3f; // camera rotation speed

	const glm::vec3 local_forward = glm::vec3(0.0f, 0.0f, -1.0f); // local forward vector
	const glm::vec3 local_up = glm::vec3(0.0f, 1.0f, 0.0f); // local up vector
	const glm::vec3 local_right = glm::vec3(1.0f, 0.0f, 0.0f); // local right vector
	glm::quat mouse_rotation_x, mouse_rotation_y; // mouse rotation quaternions
	bool is_right_mouse_button_pressed; // is right mouse button pressed?

	InputInfo() {
		camera_translation = glm::vec3();
	}
} InputInfo;

extern InputInfo input;

void KeyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods); // key press callback
void MouseMoveCallback(GLFWwindow* window, double xpos, double ypos); // mouse movement callback
void MousePressCallback(GLFWwindow* window, int button, int action, int mods); // mouse button press callback