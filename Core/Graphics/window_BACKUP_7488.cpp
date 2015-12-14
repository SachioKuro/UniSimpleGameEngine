#include "Window.hpp"
#include "Texture.hpp"

#include <glm\gtc\matrix_transform.hpp>

#include "../Input/Input.hpp"

#define ERROR_OUTPUT_ENABLED 1
#define DEBUG_OUTPUT_ENABLED 1
#include "../Utils/Output.hpp"

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
			delete shader;
			glfwTerminate();
		}

<<<<<<< HEAD
		void Window::update(Terrain::Chunk* chunks, size_t nrOfChunks, Terrain::RenderMode renderMode) const {
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
=======
		void Window::updateCamera() {

			// Compute new orientation
			double horizontalAngle = 0.0f;
			double verticalAngle = 0.0f;
			float mouseSpeed = 2.0f;
			float deltaTime = 0.05f;
			horizontalAngle += mouseSpeed * deltaTime / 10 * float(1024 / 2 - xpos);
			verticalAngle += mouseSpeed * deltaTime / 10 * float(768 / 2 - ypos);

			// Direction : Spherical coordinates to Cartesian coordinates conversion
			glm::vec3 direction(
				cos(verticalAngle) * sin(horizontalAngle),
				sin(verticalAngle),
				cos(verticalAngle) * cos(horizontalAngle)
				);

			// Right vector
			glm::vec3 right = glm::vec3(
				sin(horizontalAngle - 3.14f / 2.0f),
				0,
				cos(horizontalAngle - 3.14f / 2.0f)
				);

			// Up vector : perpendicular to both direction and right
			glm::vec3 up = glm::cross(right, direction);

			// Move forward
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
				cameraPosition += direction * deltaTime * mouseSpeed;
			}

			// Move backward
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
				cameraPosition -= direction * deltaTime * mouseSpeed;
			}

			// Strafe right
			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
				cameraPosition += right * deltaTime * mouseSpeed;
			}

			// Strafe left
			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
				cameraPosition -= right * deltaTime * mouseSpeed;
			}

			view = lookAt(cameraPosition, cameraPosition+direction, vec3(0, 1, 0));
			mvp = projection * view * model;
			glfwGetCursorPos(window, &xpos, &ypos);

		}

		void Window::update(GLfloat* vertices, size_t size, uint renderMode) {
			updateCamera();

			glClear(GL_COLOR_BUFFER_BIT);
			
			glBufferData(GL_ARRAY_BUFFER, size * 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
			
			glUseProgram(programID);
			glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);


			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
>>>>>>> Camera

			for (size_t i = 0; i < nrOfChunks; i++)
				chunks[i].draw(mvp, renderMode);
			
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

			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);

<<<<<<< HEAD
			// Todo: get from Camera-Class
			projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
			view = lookAt(CAMERA_POSITION, vec3(0, 0, 0), vec3(0, 1, 0));
			// Todo: refactor
=======
			glfwSetCursorPos(window, width / 2, height / 2);

			projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
			view = lookAt(cameraPosition, vec3(0,1,0), vec3(0,1,0));
>>>>>>> Camera
			model = mat4(1.0f, .0f, .0f, .0f, .0f, 1.0f, .0f, .0f, .0f, .0f, 1.0f, .0f, -.5f, -.5f, .0f, 1.0f);

			mvp = projection * view * model;

			
			/*
			texBuffer = Texture::load("Textures/MarbleGreen001.dds");

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texBuffer);*/

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