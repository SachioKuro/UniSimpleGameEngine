#pragma once

#include <vector>

#include "../Graphics/Window.hpp"
#include "../Input/Input.hpp"
#include "../Utils/Output.hpp"

namespace Core {
	// Inputfunktion
	typedef void(*HandleInputFunc)(const GLint* const, const GLint* const);
	class Context {
	private:
		Graphics::Window* window;
		Utils::Input* input;
		Context* parent = 0;
		std::vector<Context*> childs;
	public:
		Context(Graphics::Window* _window, Utils::Input* _input, Context* parent = 0, std::vector<Context*> = {});
		~Context();
		Context* getParent() const { return parent; }
		void setParent(Context* _context) { parent = _context; }
		std::vector<Context*> getChilds() { return childs; }
		void addChild(Context* _context) { childs.push_back(_context); }
		Graphics::Window* getWindow() const { return window; };
		Utils::Input* getInput() const { return input; };
		void handleInput(const GLint* const _keys, const GLint* const _buttons);
		void handleInput(const GLint* const _keys, const GLint* const _buttons, HandleInputFunc _func);
	private:
		void init();
	};
}