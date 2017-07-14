#pragma once

#include "texture.h"
#include "shader.h"
#include "camera.h"

#include <GL/glew.h>
#include <glm.hpp>
#include <SOIL2.h>

typedef struct Skybox {
	std::vector<glm::vec3> vertices; // cube vertices
	std::vector<unsigned int> indices; // indices for cube triangles
	GLuint program, vao, vbo, ibo; // rendering variables
	unsigned int texture_id; // bmp texture id
} Skybox;

void InitializeSkybox();
void RenderSkybox();
