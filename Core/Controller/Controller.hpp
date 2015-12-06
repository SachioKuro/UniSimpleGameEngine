#pragma once

#include <vector>
#include "Context.hpp"

namespace Core {
	class Controller {
	private:
		Context* mainContext;
	public:
		Context* getRootContext() { return mainContext; }
		void setRootContext(Context* _context) { mainContext = _context; }
	};
}