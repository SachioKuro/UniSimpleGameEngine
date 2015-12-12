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
	Input input;
	Context con(&window, &input);

	Controller controller;
	controller.setRootContext(&con);

	// TestChamber:
	Core::Terrain::Chunk* chunk = new Core::Terrain::Chunk;
	chunk->buildMesh();

	size_t size = 36 * CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z;

	while (!controller.getRootContext()->getWindow()->closed())
		controller.getRootContext()->getWindow()->update(chunk->getMeshData(), size, (GLuint)chunk->getRenderMode());

	delete chunk;

	return 0;
}

