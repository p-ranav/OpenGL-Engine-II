#include "window.h"
#include "shader.h"

int main(void)
{
	CreateWindow();
	GLuint program = CreateShaderProgram({
		{ GL_VERTEX_SHADER, "Shaders/cube.vert" },
		{ GL_FRAGMENT_SHADER, "Shaders/cube.frag"}
	});
	RenderScene();
	TerminateWindow();
	return 0;
}