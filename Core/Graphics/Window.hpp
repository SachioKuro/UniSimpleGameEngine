#pragma once

#include "../Utils/GL.hpp"
#include "../Utils/Debug.hpp"
#include "../Terrain/Skybox.hpp"
#include "../Terrain/WorldTree.hpp"
#include "WaterFBO.hpp"
#include "Camera.hpp"

namespace Core {
	namespace Graphics {
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
			GLint width, height;
			const GLchar* title;
			glm::vec4 clearColor;
			// Transformation-Information
			glm::mat4 view = glm::mat4(1.0f), projection;
			GLdouble lastTime;
			GLuint frames = 0;
			WaterFBO* waterFBO;
		public:
			Window(const GLchar* title, GLint width, GLint height, glm::vec4 clearColor = glm::vec4(.5f, .5f, .9f, .0f));
			~Window();
			GLFWwindow* getGLFWwindow() { return window; }
			GLint getWidth() const { return width; }
			void setWidth(GLint width) { this->width = width; }
			GLint getHeight() const { return height; }
			void setHeight(GLint height) { this->height = height; }
			void setClearColor(glm::vec4 clearColor) { this->clearColor; }
			void setHandleInputFunc(HandleInput _handleInputFunc) { handleInputFunc = _handleInputFunc; }
			HandleInput getHandleInputFunc() { return handleInputFunc; }
			/* Updates the window */
			void update(Terrain::WorldTree* wt, Terrain::Skybox* skybox, Camera*& camera);
			/* Is the window ready for close */
			GLboolean closed() const;
			void setButtonCallback(GLFWmousebuttonfun func);
			void setKeyCallback(GLFWkeyfun func);
		private:
			/* Initialize the window */
			GLboolean init();
			
		};
	}
}