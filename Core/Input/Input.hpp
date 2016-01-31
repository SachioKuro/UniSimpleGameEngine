#pragma once

#include "../Utils/GL.hpp"
#include "../Graphics/Window.hpp"

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

namespace Core {
	namespace Utils {
		// Key-Function
		typedef void(*Keyfunc)(GLFWwindow*, GLint, GLint, GLint, GLint);
		// Button-Function
		typedef void(*Buttonfunc)(GLFWwindow*, GLint, GLint, GLint);
		/* handles the user-input */
		class Input {
		public:
			// Keymap
			GLint Keys[MAX_KEYS];
			// Buttonmap
			GLint Buttons[MAX_BUTTONS];
			// Mouseposition
			glm::vec2 Position;
		public:
			Input();
			GLboolean isKeyPressed(GLuint key);
			GLboolean isButtonPressed(GLuint button);
			void key_callback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods);
			void button_callback(GLFWwindow* window, GLint button, GLint action, GLint mods);
			Buttonfunc getButtonCallbackFunc();
			Keyfunc getKeyCallbackFunc();
		};
	}
}