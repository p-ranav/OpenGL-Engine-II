#include "shader.h"

std::string ReadFile(std::string file_path) {
	std::ifstream t(file_path);	
	std::string file_contents;

	t.seekg(0, std::ios::end);	// Find size of the file
	file_contents.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	file_contents.assign((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());
	return file_contents;
}

GLuint CreateShader(GLenum shader_type, std::string shader_path)
{
	int compile_result = 0;
	GLuint shader = glCreateShader(shader_type);
	std::string source = ReadFile(shader_path);
	const char *shader_code_ptr = source.c_str();
	const int shader_code_size = static_cast<int>(source.size());
	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	if (compile_result == GL_FALSE) { // check for shader compilation errors
		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		std::cout << "Error compiling shader " << shader_path << std::endl;
		std::cout << &shader_log[0] << std::endl;
		return 0;
	}
	return shader;
}

GLuint CreateShaderProgram(std::map<GLenum, std::string> shader_pipeline) {
	int link_result = 0;
	GLuint program = glCreateProgram();
	for (auto const &shader : shader_pipeline) {
		GLuint shader_id = CreateShader(shader.first, shader.second);
		glAttachShader(program, shader_id);
	}
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);

	if (link_result == GL_FALSE) { // check for shader program linking errors
		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		std::cout << "Error linking shader program!" << std::endl;
		std::cout << &program_log[0] << std::endl;
	}
	return program;
}
