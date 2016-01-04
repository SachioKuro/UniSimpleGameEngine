#pragma once

#include <vector>

#include "../Graphics/Window.hpp"
#include "../Input/Input.hpp"
#include "../Utils/Output.hpp"

namespace Core {
	using namespace std;
	using namespace Graphics;
	using namespace Core::Utils;

	// Inputfunktion
	typedef void(*HandleInputFunc)(const GLint* const, const GLint* const);
	class Context {
	private:
		Window* window;
		Input* input;
		Context* parent = 0;
		vector<Context*> childs;
	public:
		Context(Window* _window, Input* _input, Context* parent = 0, vector<Context*> = {});
		~Context();
		Context* getParent() const { return parent; }
		void setParent(Context* _context) { parent = _context; }
		vector<Context*> getChilds() { return childs; }
		void addChild(Context* _context) { childs.push_back(_context); }
		Window* getWindow() const { return window; };
		Input* getInput() const { return input; };
		void handleInput(const GLint* const _keys, const GLint* const _buttons);
		void handleInput(const GLint* const _keys, const GLint* const _buttons, HandleInputFunc _func);
	private:
		void init();
	};
}