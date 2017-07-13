#pragma once

#include "shader.h"
#include "camera.h"

#include <GL/glew.h>
#include <glm.hpp>
#include <SOIL2.h>

#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

typedef struct CubeVertexFormat {
	CubeVertexFormat(glm::vec3 vertex_position, glm::vec2 vertex_texture) :
		position(vertex_position), texture(vertex_texture) {}
	glm::vec3 position;
	glm::vec2 texture;
} CubeVertexFormat;

typedef struct Cube {
	std::vector<CubeVertexFormat> vertices; // cube vertices
	std::vector<unsigned int> indices; // indices for cube triangles
	glm::vec3 rotation, rotation_speed; // rotation speed
	glm::vec3 rotation_sin; // sine of the rotation
	GLuint program, vao, vbo, ibo; // rendering variables
	unsigned int texture_id; // bmp texture id
} Cube;

void InitializeCube(); // initializes cube vertices, indices, shaders, textures
void RenderCube(); // draws the cube using glDrawElements with cube's shader program
