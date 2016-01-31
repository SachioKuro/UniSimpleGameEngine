#include "Window.hpp"

namespace Core {
	namespace Graphics {
		void error_callback(GLint, const GLchar*);
		void windowResize_callback(GLFWwindow*, GLint, GLint);

		Window::Window(const GLchar* title, GLint width, GLint height, glm::vec4 clearColor)
						: title(title), width(width), height(height), clearColor(clearColor) {
			if (!init()) {
				ERROR("Failed to init Window!");
				glfwTerminate();
			}
		}

		Window::~Window() {
			glfwTerminate();
			delete waterFBO;
		}

		void Window::update(Terrain::WorldTree* wt, Terrain::Skybox* skybox, Camera*& camera) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			Terrain::Chunk* currentChunk = wt->getCurrentChunk();
			view = camera->updateCamera(currentChunk);
			vec3 cameraPosition = camera->getCameraPosition();

			GLdouble currentTime = glfwGetTime();
			frames++;
			if (currentTime - lastTime >= 1.0) {
				DEBUG_F("%d Frames/sec\n", frames);
				frames = 0; lastTime += 1.0;
			}

			// Draw Skybox
			skybox->getSkyboxBlock()->draw(cameraPosition, view, projection);
			wt->checkAndLoad();

#if 0
			float distAsWaterMirror = 2 * (cameraPosition.y - (-CHUNK_SIZE_Y + WATERLEVEL));

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, waterFBO->getReflectionTexture());
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, waterFBO->getRefractionTexture());

			glEnable(GL_CLIP_PLANE0);
			waterFBO->bindReflectionFBO();
			camera->getCameraPosition().y -= distAsWaterMirror;
			for (int i = 0; i < WORLDSIZE; i++)
				for (int j = 0; j < WORLDSIZE; j++)
					wt->getChunks()[i][j]->draw(projection, view, vec4(0, -1, 0, -(CHUNK_SIZE_Y - WATERLEVEL)), WATERLEVEL, 0, camera, Terrain::TerrainType::LAND);
			camera->getCameraPosition().y += distAsWaterMirror;
					
			waterFBO->unbindFBO();
			waterFBO->bindRefractionFBO();

			for (int i = 0; i < WORLDSIZE; i++)
				for (int j = 0; j < WORLDSIZE; j++)
					wt->getChunks()[i][j]->draw(projection, view, vec4(0, 1, 0, -(CHUNK_SIZE_Y - WATERLEVEL)), 0, CHUNK_SIZE_Y - WATERLEVEL, camera, Terrain::TerrainType::LAND);

			waterFBO->unbindFBO();
			glDisable(GL_CLIP_PLANE0);
			wt->getContext()->getTexture()->bind(GL_TEXTURE_2D, 0);
#endif
			// Draw Chunks 
			for (int i = 0; i < WORLDSIZE; i++)
				for (int j = 0; j < WORLDSIZE; j++)
					wt->getChunks()[i][j]->draw(projection, view, vec4(0), 0, 0, camera, Terrain::TerrainType::LAND);

			for (int i = 0; i < WORLDSIZE; i++)
				for (int j = 0; j < WORLDSIZE; j++)
					wt->getChunks()[i][j]->draw(projection, view, vec4(0), 0, 0, camera, Terrain::TerrainType::WATER);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}


		GLboolean Window::closed() const {
			return glfwWindowShouldClose(window);
		}

		void Window::setButtonCallback(GLFWmousebuttonfun func) {
			glfwSetMouseButtonCallback(window, func);
		}

		void Window::setKeyCallback(GLFWkeyfun func) {
			glfwSetKeyCallback(window, func);
		}

		GLboolean Window::init() {
			// Initializes GLFW
			if (!glfwInit()) {
				ERROR("Failed to initialize GLFW\n");
				return GL_FALSE;
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
				return GL_FALSE;
			}

			// sets context
			glfwMakeContextCurrent(window);
			glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			// Initializes glew
			glewExperimental = GL_TRUE;
			if (glewInit() != GLEW_OK) {
				ERROR("Failed to initialize GLEW\n");
				return GL_FALSE;
			}

			INFO(glfwGetVersionString());
			INFO(glGetString(GL_VERSION));

			glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
			glfwSetWindowUserPointer(window, this);
			glfwSetWindowSizeCallback(window, windowResize_callback);
			glFrontFace(GL_CCW);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);

			glfwSwapInterval(0);

			// Initializes shader
			Shader::init();

			// Enables Depth-Testing
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			//glShadeModel(GL_FLAT);

			// Sets projectionmatrix
			projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 140.0f);

			lastTime = glfwGetTime();
			waterFBO = new WaterFBO;

			return GL_TRUE;
		}

		void error_callback(int error, const GLchar* description) {
			ERROR(description);
		}

		void windowResize_callback(GLFWwindow* window, GLint width, GLint height) {
			// Gets pointer to the GLFW-Window
			Window* _window = (Window*)glfwGetWindowUserPointer(window);
			_window->setWidth(width);
			_window->setHeight(height);

			DEBUG(_window->getWidth());
			DEBUG(_window->getHeight());
		}
	}
}