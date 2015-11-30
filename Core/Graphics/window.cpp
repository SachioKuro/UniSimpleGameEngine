#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "window.hpp"

#define ERROR_OUTPUT_ENABLED 1
#define DEBUG_OUTPUT_ENABLED 0

#if ERROR_OUTPUT_ENABLED
	#define ERROR(error) fprintf(stderr, error)
#else
	#define ERROR(error)
#endif

#if DEBUG_OUTPUT_ENABLED
	#define DEBUG(debug) std::cout << debug << std::endl
#else
	#define DEBUG(debug)
#endif

namespace Graphics {
	Window* _window;

	void error_callback(int, const char*);
	void windowResize_callback(GLFWwindow*, int, int);

	Window::Window(const char* title, int width, int height, glm::vec4 clearColor)
		: title(title), width(width), height(height), clearColor(clearColor)
	{
		if (!init()) {
			ERROR("Failed to init Window!");
			glfwTerminate();
		}

		_window = this;
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

	bool Window::closed() const
	{
		return glfwWindowShouldClose(window);
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

		glfwSetWindowSizeCallback(window, windowResize_callback);

		return true;
	}
	
	void error_callback(int error, const char* description)
	{
		ERROR(description);
	}

	void windowResize_callback(GLFWwindow* window, int width, int height)
	{
		_window->setWidth(width);
		_window->setHeight(height);

		DEBUG(_window->getWidth());
		DEBUG(_window->getHeight());
	}
}