#include "window.h"
#include "camera.h"

int main(void)
{
	CreateWindow();
	InitializeCamera();
	RenderScene(PrepareScene(ROTATING_CUBE));
	TerminateWindow();
	return 0;
}