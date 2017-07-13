#include "window.h"
#include "camera.h"

int main(void)
{
	CreateWindow();
	InitializeCamera();
	SetPosition(glm::vec3(0, 0, 35));
	RenderScene(SceneLookup(PLANET_EARTH));
	TerminateWindow();
	return 0;
}