#include "Core/Graphics/window.hpp"
#include "Core/Input/Input.hpp"
#include "Core/Controller/Context.hpp"
#include "Core/Controller/Controller.hpp"

int main(void) {
	using namespace Core::Graphics;
	using namespace Core::Utils;
	using namespace Core;

	Window window("Engine", 1024, 800);
	Input input;
	Context con(&window, &input);

	Controller controller;
	controller.setRootContext(&con);

	while (!controller.getRootContext()->getWindow()->closed())
		controller.getRootContext()->getWindow()->update();

	return 0;
}

