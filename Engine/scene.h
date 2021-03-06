#pragma once

#include "input.h" // get input state and update camera before drawing frame
#include "cube.h" // rotating cube scene
#include "earth.h" // planets!
#include "skybox.h" // milky way skybox

#include <vector>
#include <functional>

typedef enum Scene {
	ROTATING_CUBE,
	PLANET_EARTH
} Scene; // enum of scenes

typedef std::vector<std::function<void(void)>> RenderFunctions; // a vector of function pointers - each function responsible for rendering some object in the scene
RenderFunctions SceneLookup(Scene scene_name); // initialize the object(s) to render and setup the RenderFunctions vector
bool RenderScene(std::vector<std::function<void(void)>> render_functions); // application's render loop
