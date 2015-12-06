#include "Input.hpp"
#include "../Graphics/window.hpp"

namespace Core {
	namespace Utils {

		Input* _input;
		Input::Input() {
			_input = this;
		}

		void Input::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
		{
			Graphics::Window* _window = (Graphics::Window*)glfwGetWindowUserPointer(window);
			Keys[key] = action != GLFW_RELEASE;

			_window->getHandleInputFunc()(Keys, Buttons);
		}

		void key_callback_Wrapper(GLFWwindow * window, int key, int scancode, int action, int mods)
		{
			_input->key_callback(window, key, scancode, action, mods);
		}

		Keyfunc Input::getKeyCallbackFunc()
		{
			return key_callback_Wrapper;
		}

		void Input::button_callback(GLFWwindow * window, int button, int action, int mods)
		{
			Graphics::Window* _window = (Graphics::Window*)glfwGetWindowUserPointer(window);
			Buttons[button] = action != GLFW_RELEASE;

			_window->getHandleInputFunc()(Keys, Buttons);
		}

		void button_callback_Wrapper(GLFWwindow * window, int button, int action, int mods)
		{
			_input->button_callback(window, button, action, mods);
		}

		Buttonfunc Input::getButtonCallbackFunc()
		{
			return button_callback_Wrapper;
		}

		GLboolean Input::isKeyPressed(GLuint key)
		{
			return Keys[key];
		}

		GLboolean Utils::Input::isButtonPressed(GLuint button)
		{
			return Buttons[button];
		}
	}
}