#pragma once
#define DEBUG 1
#define ERROR_OUTPUT_ENABLED 1
#define DEBUG_OUTPUT_ENABLED 1

#include <string>

#include "../Utils/GL.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "../Terrain/Chunk.hpp"
#include "../Terrain/Skybox.hpp"
#include "../Utils/Output.hpp"

namespace Core {
	namespace Graphics {
		using namespace glm;
		// Input-Handler
		typedef void(*HandleInput)(const GLint* const, const GLint* const);
		/* A Window */
		class Window {
		private:
			// GLFW-Window
			GLFWwindow* window;
			// Inpud-Funktion
			HandleInput handleInputFunc;
			// Window-Information
			int width, height;
			const char* title;
			glm::vec4 clearColor;
			// Transformation-Information
			glm::mat4 view = mat4(1.0f), projection, model = mat4(1.0f), mvp;
			double xpos, ypos;
			vec3 cameraPosition = vec3(0, 0, 0);
			GLbyte errorFlags = 0x0000;
		public:
			Window(const char* title, int width, int height, glm::vec4 clearColor = glm::vec4(.5f, .5f, .9f, .0f));
			~Window();
			GLFWwindow* getGLFWwindow() { return window; }
			int getWidth() const { return width; }
			void setWidth(int width) { this->width = width; }
			int getHeight() const { return height; }
			void setHeight(int height) { this->height = height; }
			void setClearColor(glm::vec4 clearColor) { this->clearColor; }
			void setHandleInputFunc(HandleInput _handleInputFunc) { handleInputFunc = _handleInputFunc; }
			HandleInput getHandleInputFunc() { return handleInputFunc; }
			/* Updates the window */
			void update(Terrain::Chunk* chunks, Terrain::Skybox* skybox, size_t nrOfChunks, Terrain::RenderMode renderMode);
			void updateCamera();
			/* Is the window ready for close */
			bool closed() const;
			void setButtonCallback(GLFWmousebuttonfun func);
			void setKeyCallback(GLFWkeyfun func);
		private:
			/* Initialize the window */
			bool init();
		};
	}
}