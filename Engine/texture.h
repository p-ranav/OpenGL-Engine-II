#pragma once

#include <stb_image.h>
#include <GL/glew.h>
#include <SOIL2.h>

#include <iostream>
#include <vector>
#include <string>

unsigned int LoadCubeMapTexture(std::vector<std::string> faces);
