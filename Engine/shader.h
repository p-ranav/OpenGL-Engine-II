#pragma once

#include <GL/glew.h>

#include <vector>
#include <map>
#include <fstream>
#include <streambuf>
#include <string>
#include <utility>

std::string ReadFile(std::string file_path); // read from file and return string
GLuint CreateShader(GLenum shader_type, std::string shader_path); // create OpenGL shader and return id
GLuint CreateShaderProgram(std::map<GLenum, std::string> shader_pipeline); // create OpenGL shader program and return id