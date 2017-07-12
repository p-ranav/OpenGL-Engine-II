#include "scene.h"

RenderFunctions PrepareScene(Scene scene_name) {
	RenderFunctions functions;
	if (scene_name == ROTATING_CUBE) {
		InitializeCube();
		functions.push_back(RenderCube);
	}
	return functions;
}