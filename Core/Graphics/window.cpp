#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "window.hpp"
#include "../Input/Input.hpp"

#define ERROR_OUTPUT_ENABLED 1
#define DEBUG_OUTPUT_ENABLED 1
#include "../Utils/output.hpp"

namespace Core {
	namespace Graphics {

		void error_callback(int, const char*);
		void windowResize_callback(GLFWwindow*, int, int);

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

		bool Window::closed() const
		{
			return glfwWindowShouldClose(window);
		}

		void Window::setButtonCallback(GLFWmousebuttonfun func)
		{
			glfwSetMouseButtonCallback(window, func);
		}

		void Window::setKeyCallback(GLFWkeyfun func)
		{
			glfwSetKeyCallback(window, func);
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
			glfwSetWindowUserPointer(window, this);
			glfwSetWindowSizeCallback(window, windowResize_callback);

			return true;
		}

		void error_callback(int error, const char* description)
		{
			ERROR(description);
		}

		void windowResize_callback(GLFWwindow* window, int width, int height)
		{
			Window* _window = (Window*)glfwGetWindowUserPointer(window);
			_window->setWidth(width);
			_window->setHeight(height);

			DEBUG(_window->getWidth());
			DEBUG(_window->getHeight());
		}
	}
}