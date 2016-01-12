#include "Window.hpp"

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
			delete camera;
#if KDEBUG
			delete coordSystem;
#endif
			glfwTerminate();
		}

		void Window::update(vector<vector<Terrain::Chunk*>>* chunks, Terrain::Skybox* skybox, size_t nrOfChunks, Terrain::RenderMode renderMode) {
			view = camera->updateCamera();
			vec3 cameraPosition = camera->getCameraPosition();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Draw Skybox
			skybox->getSkyboxBlock()->draw(cameraPosition, view, projection);

			// Draw Chunks
			//for (GLint i = 0; i < nrOfChunks; i++) {
			//	chunks[i]->draw(projection, view, renderMode);
			//}

			for (vector<Terrain::Chunk*> chunkx : *chunks) {
				for (Terrain::Chunk* chunk : chunkx) {
					chunk->draw(projection, view, renderMode);
				}
			}

#if KDEBUG
			coordSystem->draw(projection, view);
#endif

			// Error-Checking
			GLenum error = glGetError();
			if (error != GL_NO_ERROR && !(errorFlags & 0x0001)) {
				std::cout << error << std::endl;
				errorFlags |= 0x0001;
			}

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
			// Initializes GLFW
			if (!glfwInit()) {
				ERROR("Failed to initialize GLFW\n");
				return false;
			}

			// Error-Handling
			glfwSetErrorCallback(error_callback);

			// GLFW-Settings
			glfwWindowHint(GLFW_SAMPLES, 2);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			// Creates GLFW-Window
			window = glfwCreateWindow(width, height, title, NULL, NULL);

			// Checks if GLFW-Window was successfully created
			if (!window) {
				glfwTerminate();
				ERROR("Failed to create window\n");
				return false;
			}

			// sets context
			glfwMakeContextCurrent(window);
			glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			// Initializes glew
			glewExperimental = GL_TRUE;
			if (glewInit() != GLEW_OK) {
				ERROR("Failed to initialize GLEW\n");
				return false;
			}

			INFO(glfwGetVersionString());
			INFO(glGetString(GL_VERSION));

			glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
			glfwSetWindowUserPointer(window, this);
			glfwSetWindowSizeCallback(window, windowResize_callback);
			glFrontFace(GL_CCW);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);

#if KDEBUG
			glfwSwapInterval(0.0);
#endif // DEBUG

			// Initializes shader
			Shader::init();

			// Enables Depth-Testing
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);

			// Sets projectionmatrix
			projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 1000.0f);

#if KDEBUG
			coordSystem = new CoordSystem(vec3(0), GL_TRUE);
#endif
			camera = new Camera(window);

			return true;
		}

		void error_callback(int error, const char* description) {
			ERROR(description);
		}

		void windowResize_callback(GLFWwindow* window, int width, int height) {
			// Gets pointer to the GLFW-Window
			Window* _window = (Window*)glfwGetWindowUserPointer(window);
			_window->setWidth(width);
			_window->setHeight(height);

			DEBUG(_window->getWidth());
			DEBUG(_window->getHeight());
		}
	}
}