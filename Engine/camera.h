#pragma once

#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm.hpp>
#include <gtx/quaternion.hpp>
#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>

typedef struct Camera {
	glm::vec4 view_port; // view port of the camera
	glm::vec3 position; // camera position
	glm::quat rotation; // camera rotation
	glm::mat4 view_matrix; // view matrix
	glm::mat4 projection_matrix; // projection matrix
	bool is_view_dirty; // should the view matrix be updated?
} Camera;

static Camera camera;

void InitializeCamera(); // initialize camera struct members

void SetViewport(int x, int y, int width, int height); // set camera view port
void SetPosition(const glm::vec3& position); // set camera position
void SetProjectionMatrix(float field_of_view, float aspect_ratio, float z_near_value, float z_far_value); // set projection matrix
void SetRotation(const glm::quat& rotation); // set camera rotation
void SetEulerAngles(const glm::vec3& euler_angles); // set camera rotation from euler angles

void Translate(const glm::vec3& delta, bool local = true); // translate camera
void Rotate(const glm::quat& rotate_by); // rotate camera

glm::vec3 GetEulerAngles(); // get euler angles
glm::mat4 GetViewMatrix(); // get view matrix
void UpdateViewMatrix(); // update the camera view matrix based on position & rotation
glm::mat4 GetProjectionMatrix(); // get projection matrix