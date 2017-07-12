#pragma once

#include "shader.h"
#include "camera.h"

#include <GL/glew.h>
#include <glm.hpp>
#include <SOIL2.h>

#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

void InitializeCube(); // initializes cube vertices, indices, shaders, textures
void RenderCube(); // draws the cube using glDrawElements with cube's shader program
