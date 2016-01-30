#include "Input.hpp"

namespace Core {
	namespace Utils {
		Input* _input;
		Input::Input() {
			_input = this;
		}

		void Input::key_callback(GLFWwindow * window, GLint key, GLint scancode, GLint action, GLint mods) {
			// Get pointer to window
			Core::Graphics::Window* _window = (Core::Graphics::Window*)glfwGetWindowUserPointer(window);
			// Update keymap
			Keys[key] = action != GLFW_RELEASE;
			// Forward to inputfunction
			_window->getHandleInputFunc()(Keys, Buttons);
		}

		void key_callback_Wrapper(GLFWwindow * window, GLint key, GLint scancode, GLint action, GLint mods) {
			_input->key_callback(window, key, scancode, action, mods);
		}

		Keyfunc Input::getKeyCallbackFunc() {
			return key_callback_Wrapper;
		}

		void Input::button_callback(GLFWwindow * window, GLint button, GLint action, GLint mods) {
			// Get pointer to window
			Core::Graphics::Window* _window = (Core::Graphics::Window*)glfwGetWindowUserPointer(window);
			// Update buttonmap
			Buttons[button] = action != GLFW_RELEASE;
			// Forward to inputfunction
			_window->getHandleInputFunc()(Keys, Buttons);
		}

		void button_callback_Wrapper(GLFWwindow * window, GLint button, GLint action, GLint mods) {
			_input->button_callback(window, button, action, mods);
		}

		Buttonfunc Input::getButtonCallbackFunc() {
			return button_callback_Wrapper;
		}

		GLboolean Input::isKeyPressed(GLuint key) {
			return Keys[key];
		}

		GLboolean Input::isButtonPressed(GLuint button) {
			return Buttons[button];
		}
	}
}