#include "camera.h"

// Initialize CameraManager
void InitializeCamera() {
	camera.view_port = glm::vec4(0);
	camera.position = glm::vec3(0);
	camera.rotation = glm::quat();
	camera.view_matrix = glm::mat4x4(1);
	camera.projection_matrix = glm::mat4x4(1);
	camera.is_view_dirty = false;
}

// Sets the camera view port
void SetViewport(int x, int y, int width, int height) {
	camera.view_port = glm::vec4(x, y, width, height);
	glViewport(x, y, width, height);
}

// Set the camera position
void SetPosition(const glm::vec3& position) {
	camera.position = position;
	camera.is_view_dirty = true;
}

// Sets the internal projection matrix
void SetProjectionMatrix(float field_of_view, float aspect_ratio, float z_near_value, float z_far_value) {
	camera.projection_matrix = glm::perspective(glm::radians(field_of_view), aspect_ratio, z_near_value, z_far_value);
}

// Sets the camera rotation
void SetRotation(const glm::quat& rotation) {
	camera.rotation = rotation;
	camera.is_view_dirty = true;
}

// Set the Euler Angles
void SetEulerAngles(const glm::vec3& euler_angles) {
	camera.rotation = glm::quat(glm::radians(euler_angles));
}

// Translate the camera by delta
void Translate(const glm::vec3& delta, bool local) {
	if (local)
		camera.position += camera.rotation * delta;
	else
		camera.position += delta;
	camera.is_view_dirty = true;
}

// Rotates the camera by provided quaternion
void Rotate(const glm::quat& rotate_by) {
	camera.rotation *= rotate_by;
	camera.is_view_dirty = true;
}

// Returns the Euler Angles
glm::vec3 GetEulerAngles() {
	return glm::degrees(glm::eulerAngles(camera.rotation));
}

// Updates the view matrix
glm::mat4 GetViewMatrix() {
	if (camera.is_view_dirty) {
		glm::mat4 translate = glm::translate(-camera.position);
		glm::mat4 rotate = glm::transpose(glm::toMat4(camera.rotation));
		camera.view_matrix = rotate * translate;
		camera.is_view_dirty = false;
	}
	return camera.view_matrix;
}

// Returns the projection matrix
glm::mat4 GetProjectionMatrix() {
	return camera.projection_matrix;
}