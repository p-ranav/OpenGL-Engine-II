#include "window.h"
#include "camera.h"
#include "cube.h"

int main(void)
{
	CreateWindow();
	InitializeCamera();

	InitializeCube();

	RenderScene();
	TerminateWindow();
	return 0;
}