#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "window.hpp"
#include "../Input/Input.hpp"

#define ERROR_OUTPUT_ENABLED 1
#define DEBUG_OUTPUT_ENABLED 1
#include "../Utils/output.hpp"

#include "Shader.hpp";

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

		Window::~Window() {
			glDeleteBuffers(1, &vertexBuffer);
			glDeleteVertexArrays(1, &vertexArrayID);
			glDeleteProgram(programID);
			glfwTerminate();
		}

		void Window::update(GLfloat* vertices, size_t size, uint renderMode) const {
			glClear(GL_COLOR_BUFFER_BIT);
			
			glBufferData(GL_ARRAY_BUFFER, size * 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
			
			glUseProgram(programID);
			glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);


			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			if (renderMode == 0) {
				glDrawArrays(GL_TRIANGLES, 0, size);
			} else if (renderMode == 1) {
				glDrawArrays(GL_LINES, 0, size);
			}
			
			glDisableVertexAttribArray(0);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}


		bool Window::closed() const {
			return glfwWindowShouldClose(window);
		}

		void Window::setButtonCallback(GLFWmousebuttonfun func) {
			glfwSetMouseButtonCallback(window, func);
		}

		void Window::setKeyCallback(GLFWkeyfun func) {
			glfwSetKeyCallback(window, func);
		}


		bool Window::init() {
			if (!glfwInit()) {
				ERROR("Failed to initialize GLFW\n");
				return false;
			}

			glfwSetErrorCallback(error_callback);

			// Todo
			glfwWindowHint(GLFW_SAMPLES, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			window = glfwCreateWindow(width, height, title, NULL, NULL);

			if (!window) {
				glfwTerminate();
				ERROR("Failed to create window\n");
				return false;
			}

			glfwMakeContextCurrent(window);
			glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

			glewExperimental = true;
			if (glewInit() != GLEW_OK) {
				ERROR("Failed to initialize GLEW\n");
				return false;
			}

			glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
			glfwSetWindowUserPointer(window, this);
			glfwSetWindowSizeCallback(window, windowResize_callback);

			programID = Shader::loadShaders("Shader/simpleVertex.glsl", "Shader/simpleFragment.glsl");

			matrixID = glGetUniformLocation(programID, "MVP");

			projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
			view = lookAt(CAMERA_POSITION, vec3(0,0,0), vec3(0,1,0));
			model = mat4(1.0f, .0f, .0f, .0f, .0f, 1.0f, .0f, .0f, .0f, .0f, 1.0f, .0f, -.5f, -.5f, .0f, 1.0f);

			mvp = projection * view * model;

			glGenVertexArrays(1, &vertexArrayID);
			glBindVertexArray(vertexArrayID);

			glGenBuffers(1, &vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

			return true;
		}

		void error_callback(int error, const char* description) {
			ERROR(description);
		}

		void windowResize_callback(GLFWwindow* window, int width, int height) {
			Window* _window = (Window*)glfwGetWindowUserPointer(window);
			_window->setWidth(width);
			_window->setHeight(height);

			DEBUG(_window->getWidth());
			DEBUG(_window->getHeight());
		}
	}
}