#include "window.h"
#include "shader.h"

int main(void)
{
	CreateWindow();
	GLuint program = CreateShaderProgram({
		std::make_pair(GL_VERTEX_SHADER, "Shaders/cube.vert"),
		std::make_pair(GL_FRAGMENT_SHADER, "Shaders/cube.frag")
	});
	RenderScene();
	TerminateWindow();
	return 0;
}