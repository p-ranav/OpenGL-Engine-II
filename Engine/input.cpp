#include "input.h"

InputInfo input;

void KeyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
		input.is_key_pressed = true;
	else if (action == GLFW_RELEASE)
		input.is_key_pressed = false;

	if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
		input.key_w = 1; // W key pressed
	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		input.key_w = 0; // W key released

	if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
		input.key_a = 1; // A key pressed
	if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		input.key_a = 0; // A key released

	if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
		input.key_s = 1; // S key pressed
	if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		input.key_s = 0; // S key released

	if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
		input.key_d = 1; // D key pressed
	if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		input.key_d = 0; // D key released

	if (key == GLFW_KEY_Q && (action == GLFW_PRESS || action == GLFW_REPEAT))
		input.key_q = 1; // Q key pressed
	if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
		input.key_q = 0; // Q key released

	if (key == GLFW_KEY_E && (action == GLFW_PRESS || action == GLFW_REPEAT))
		input.key_e = 1; // E key pressed
	if (key == GLFW_KEY_E && action == GLFW_RELEASE)
		input.key_e = 0; // E key released

	input.camera_translation = glm::vec3(input.key_d - input.key_a, input.key_q - input.key_e, input.key_s - input.key_w) * input.camera_translation_speed;
}