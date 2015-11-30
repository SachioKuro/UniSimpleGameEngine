#pragma once

#include <string>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


namespace Graphics {
	class Window {
	private:
		GLFWwindow* window;
		int width, height;
		const char* title;
		glm::vec4 clearColor;
	public:
		Window(const char*  title, int width, int height, glm::vec4 clearColor = glm::vec4(.5f, .5f, .9f, .0f));
		~Window();
		inline int getWidth() const { return width; }
		inline int getHeight() const { return height; }
		inline void setWidth(int width) { this->width = width; }
		inline void setHeight(int height) { this->height = height; }
		inline void setClearColor(glm::vec4 clearColor) { this->clearColor; }
		void update() const;
		bool closed() const;
	private:
		bool init();
	};
}