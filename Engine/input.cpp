#include "input.h"

InputInfo input;

void KeyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
		input.is_key_pressed = true;

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

	if (action == GLFW_RELEASE && action != GLFW_REPEAT)
		input.is_key_pressed = false;
}

void MouseMoveCallback(GLFWwindow * window, double xpos, double ypos) {
	glm::ivec2 current_mouse_position = glm::ivec2(xpos, ypos);
	glm::vec2 delta = glm::vec2(current_mouse_position - input.mouse_position); // calculate movement delta
	input.mouse_position = current_mouse_position; // update mouse position

	if (delta.x > 1 || delta.x < -1 || delta.y > 1 || delta.y < -1) { // calculate mouse rotation quaternions if there is a large enough delta movement
		input.mouse_rotation_x = glm::angleAxis<float>(-input.camera_rotation_speed * glm::radians(delta.x), input.local_up);
		input.mouse_rotation_y = glm::angleAxis<float>(-input.camera_rotation_speed * glm::radians(delta.y), input.local_right);
	}
	else { // zero out the rotation quaternions if the delta is not large enough
		input.mouse_rotation_x = glm::vec3();
		input.mouse_rotation_y = glm::vec3();
	}
}

void MousePressCallback(GLFWwindow * window, int button, int action, int mods) {
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	input.mouse_position = glm::ivec2(xpos, ypos);

	if (button == GLFW_MOUSE_BUTTON_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
		input.is_right_mouse_button_pressed = true;
	else
		input.is_right_mouse_button_pressed = false;
}
