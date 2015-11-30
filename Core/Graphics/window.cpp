#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "window.hpp"

#define ERROR_OUTPUT_ENABLED 1

#if ERROR_OUTPUT_ENABLED
	#define ERROR(error) fprintf(stderr, error)
#else
	#define ERROR(error)
#endif

namespace Graphics {
	void error_callback(int, const char*);

	Window::Window(const char* title, int width, int height, glm::vec4 clearColor)
		: title(title), width(width), height(height), clearColor(clearColor)
	{
		if (!init()) {
			ERROR("Failed to init Window!");
			glfwTerminate();
		}
	}

	Window::~Window() 
	{
		glfwTerminate();
	}

	void Window::update() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	bool Window::init()
	{
		if (!glfwInit()) {
			ERROR("Failed to initialize GLFW\n");
			return false;
		}

		glfwSetErrorCallback(error_callback);

		window = glfwCreateWindow(width, height, title, NULL, NULL);

		if (!window) {
			glfwTerminate();
			ERROR("Failed to create window\n");
			return false;
		}

		glfwMakeContextCurrent(window);
		glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
		return true;
	}
	
	void error_callback(int error, const char* description)
	{
		ERROR(description);
	}
}