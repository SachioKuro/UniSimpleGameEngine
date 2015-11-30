#include "Core/Graphics/window.hpp"

int main(void) {
	using namespace Graphics;
	Window window("Engine", 1024, 800);

	while (!window.closed())
		window.update();

	return 0;
}

