#pragma once

#include "../Utils/GL.hpp"
#include "../Graphics/Window.hpp"

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

namespace Core {
	namespace Utils {
		using namespace glm;
		using namespace Graphics;
		// Key-Function
		typedef void(*Keyfunc)(GLFWwindow*, int, int, int, int);
		// Button-Function
		typedef void(*Buttonfunc)(GLFWwindow*, int, int, int);
		/* handles the user-input */
		class Input {
		public:
			// Keymap
			GLint Keys[MAX_KEYS];
			// Buttonmap
			GLint Buttons[MAX_BUTTONS];
			// Mouseposition
			vec2 Position;
		public:
			Input();
			GLboolean isKeyPressed(GLuint key);
			GLboolean isButtonPressed(GLuint button);
			void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			void button_callback(GLFWwindow* window, int button, int action, int mods);
			Buttonfunc getButtonCallbackFunc();
			Keyfunc getKeyCallbackFunc();
		};
	}
}