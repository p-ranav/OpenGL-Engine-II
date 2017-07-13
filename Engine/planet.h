#pragma once

#include "shader.h"
#include "camera.h"

#include <GL/glew.h>
#include <glm.hpp>
#include <SOIL2.h>

#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>
#include <stdarg.h>
#include <cmath>

typedef struct Planet {

	float rotation, rotation_rate, days_per_year; // planet rotation (not revolution around sun)
	std::clock_t previous_ticks, current_ticks; // ticks to handle rotation

	std::vector<glm::vec3> positions; // vertex positions
	std::vector<glm::vec3> normals; // vertex normals
	std::vector<glm::vec2> texture_coordinates; // texture coordinates
	std::vector<unsigned int> indices; // indices for triangles

	GLuint program, vao, vbo, ibo; // rendering variables
	unsigned int texture_id, topography_texture_id; // bmp texture id
} Planet;

void InitializePlanet(Planet& planet, float radius, float slices, float stacks, const char * texture_path);
void RenderPlanets();
