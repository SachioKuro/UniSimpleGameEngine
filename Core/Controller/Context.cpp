#include "Context.hpp"

namespace Core {

	Context* _context;
	Context::Context(Window * _window, Input * _input, Context* _parent, vector<Context*> _childs)
	{
		parent = _parent;
		childs = _childs;
		window = _window;
		input = _input;
		_context = this;
		init();
	}

	Context::~Context() {}

	void Context::handleInput(const GLint * const _keys, const GLint * const _buttons)
	{
		if (_buttons[GLFW_MOUSE_BUTTON_LEFT] == 1)
		{
			DEBUG("Linke Maustaste");
		}
		else if(_buttons[GLFW_MOUSE_BUTTON_RIGHT] == 1)
		{
			DEBUG("Rechte Maustaste");
		}

		if (_keys[GLFW_KEY_ESCAPE] == 1)
		{
			glfwSetWindowShouldClose(window->getGLFWwindow(), GL_TRUE);
		}
	}

	void Context::handleInput(const GLint * const _keys, const GLint * const _buttons, HandleInputFunc _func)
	{
		_func(_keys, _buttons);
	}

	void handleWrapper(const GLint * const _keys, const GLint * const _buttons)
	{
		_context->handleInput(_keys, _buttons);
	}

	void Context::init() 
	{
		window->setHandleInputFunc(handleWrapper);
		window->setKeyCallback(input->getKeyCallbackFunc());
		window->setButtonCallback(input->getButtonCallbackFunc());
	}
}