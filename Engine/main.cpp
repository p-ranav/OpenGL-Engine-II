#include "window.h"
#include "camera.h"
#include "cube.h"

int main(void)
{
	CreateWindow();
	InitializeCamera();
	SetPosition(glm::vec3(0, 0, 50));
	InitializeCube();
	RenderScene();
	TerminateWindow();
	return 0;
}