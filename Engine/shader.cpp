#include "shader.h"

std::string ReadFile(std::string file_path) {
	std::ifstream t(file_path);
	std::string file_contents;

	t.seekg(0, std::ios::end);
	file_contents.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	file_contents.assign((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());
	return file_contents;
}

GLuint CreateShader(GLenum shader_type, std::string shader_path)
{
	GLuint shader = glCreateShader(GL_VERTEX_SHADER);
	const char * shader_cstr = ReadFile(shader_path).c_str();
	glShaderSource(shader, 1, &shader_cstr, NULL);
	glCompileShader(shader);
	return shader;
}

GLuint CreateShaderProgram(std::map<GLenum, std::string> shader_pipeline)
{
	GLuint program = glCreateProgram();
	for (auto const &shader : shader_pipeline) {
		GLuint shader_id = CreateShader(shader.first, shader.second);
		glAttachShader(program, shader_id);
	}
	glLinkProgram(program);
	return program;
}
