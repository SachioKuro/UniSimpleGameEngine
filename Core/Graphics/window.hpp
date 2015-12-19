#pragma once

#include <string>

#include "../Terrain/Chunk.hpp"
#include "../Terrain/Skybox.hpp"
#include "../Utils/GL.hpp"

namespace Core {
	namespace Graphics {
		using namespace glm;
		typedef void(*HandleInput)(const GLint* const, const GLint* const);
		class Window {
		private:
			HandleInput handleInputFunc;
			GLFWwindow* window;
			Shader* shader = nullptr;
			int width, height;
			const char* title;
			glm::vec4 clearColor;
			GLuint matrixID;
			glm::mat4 view = mat4(1.0f), projection, model, mvp;
			double xpos, ypos;
			GLuint texBuffer;
			GLbyte errorFlags = 0x0000;
		public:
			Window(const char* title, int width, int height, glm::vec4 clearColor = glm::vec4(.5f, .5f, .9f, .0f));
			~Window();
			inline int getWidth() const { return width; }
			inline int getHeight() const { return height; }
			inline void setWidth(int width) { this->width = width; }
			inline void setHeight(int height) { this->height = height; }
			inline void setClearColor(glm::vec4 clearColor) { this->clearColor; }
			inline void setHandleInputFunc(HandleInput _handleInputFunc) { handleInputFunc = _handleInputFunc; }
			inline HandleInput getHandleInputFunc() { return handleInputFunc; }
			void update(Terrain::Chunk* chunks, Terrain::Skybox* skybox, size_t nrOfChunks, Terrain::RenderMode renderMode);
			GLFWwindow* getGLFWwindow() { return window; }
			void updateCamera();
			bool closed() const;
			void setButtonCallback(GLFWmousebuttonfun func);
			void setKeyCallback(GLFWkeyfun func);
			vec3 cameraPosition = vec3(0, 0, 0);
		private:
			bool init();
		};
	}
}