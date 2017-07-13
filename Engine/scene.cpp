#include "scene.h"

RenderFunctions SceneLookup(Scene scene_name) {
	RenderFunctions functions;
	if (scene_name == ROTATING_CUBE) {
		InitializeCube();
		functions.push_back(RenderCube);
	}
	else if (scene_name == PLANET_EARTH) {
		Planet earth;
		earth.days_per_year = 365;
		earth.rotation_rate = 10.0f;
		InitializePlanet(earth, 1, 128, 128, "Textures\\Earth.dds");
		functions.push_back(RenderPlanets);
	}
	return functions;
}

bool RenderScene(std::vector<std::function<void(void)>> render_functions) {
	bool result = false;
	if (!window.handle) // If handle is null, do nothing
		result = false;
	else {
		result = true;
		while (result && !glfwWindowShouldClose(window.handle)) { // check if window should close
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window
			glClearColor(0.0, 0.0, 0.0, 1.0);
			float aspect_ratio = (float)window.width / (float)window.height;
			float angle = 45.0f, near_value = 0.1f, far_value = 1000.0f;
			SetProjectionMatrix(angle, aspect_ratio, near_value, far_value);
			SetViewport(0, 0, window.width, window.height);

			if (input.is_key_pressed) // handle keyboard input
				Translate(input.camera_translation);

			if (input.is_right_mouse_button_pressed) { // handle right mouse button + mouse movement
				Rotate(input.mouse_rotation_x);
				Rotate(input.mouse_rotation_y);
			}

			for (auto render_function : render_functions) {
				try {
					render_function();
				}
				catch (std::bad_function_call& e) {
					std::cout << "Error calling rendering function: " << e.what() << std::endl;
					result = false;
				}
			}

			glfwSwapBuffers(window.handle); // swap front and back buffers
			glfwPollEvents(); // poll for events
		}
	}
	return result;
}