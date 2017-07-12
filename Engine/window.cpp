#include "window.h"

Window window;

bool CreateWindow(const uint_fast32_t width, const uint_fast32_t height, const char * title) {
	bool result = false;
	if (!glfwInit()) // initialize GLFW
		result = false;
	else {
		window.width = width;
		window.height = height;
		window.title = title;
		window.handle = glfwCreateWindow(window.width, window.height, window.title, NULL, NULL); // create GLFW Window
		if (!window.handle)
			result = false;
		else {
			glfwMakeContextCurrent(window.handle); // make OpenGL context current
			glfwSetWindowSizeCallback(window.handle, WindowResizeCallback);
			glewInit(); // initialize GLEW
		}
	}
	return result;
}

bool TerminateWindow() {
	glfwTerminate(); // Terminate window
	return true;
}

void WindowResizeCallback(GLFWwindow * window_handle, int width, int height) {
	window.width = width;
	window.height = height;
	float aspect_ratio = (float)width / (float)height;
	float angle = 45.0f, near_value = 0.1f, far_value = 1000.0f;
	SetProjectionMatrix(angle, aspect_ratio, near_value, far_value);
	SetViewport(0, 0, width, height);
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