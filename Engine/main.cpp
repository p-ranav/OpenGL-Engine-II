#include "window.h"
#include "camera.h"

int main(void)
{
	CreateWindow();
	InitializeCamera();
	RenderScene(SceneLookup(PLANET_EARTH));
	TerminateWindow();
	return 0;
}