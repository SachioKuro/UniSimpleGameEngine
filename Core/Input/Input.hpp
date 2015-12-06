#pragma once

#include <GLFW\glfw3.h>

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

namespace Core {
	namespace Utils {
		typedef void(*Keyfunc)(GLFWwindow*, int, int, int, int);
		typedef void(*Buttonfunc)(GLFWwindow*, int, int, int);
		class Input {
		public:
			GLint Keys[MAX_KEYS];
			GLint Buttons[MAX_BUTTONS];
			GLfloat X, Y;
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