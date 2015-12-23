#include "Core\Terrain\Chunk.hpp"
#include "Core/Input/Input.hpp"
#include "Core/Controller/Context.hpp"
#include "Core/Controller/Controller.hpp"
#include "Core/Graphics/Window.hpp"
int main(void) {
	using namespace Core::Graphics;
	using namespace Core::Utils;
	using namespace Core;

	Window window("Engine", 1024, 800);
	GLenum error = glGetError();
	Input input;
	Context con(&window, &input);


	Controller controller;
	controller.setRootContext(&con);

	// TestChamber:
	Core::Terrain::Chunk* chunk = new Core::Terrain::Chunk;
	Core::Terrain::Skybox* skybox = new Core::Terrain::Skybox(Core::Terrain::SkyType::SUNNY01);

	while (!controller.getRootContext()->getWindow()->closed())
		controller
			.getRootContext()
			->getWindow()
			->update(chunk, skybox, 1, chunk->getRenderMode());

	delete chunk;
	delete skybox;

	return 0;
}

