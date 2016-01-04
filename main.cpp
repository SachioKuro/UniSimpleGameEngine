#include "Core\Terrain\Chunk.hpp"
#include "Core/Input/Input.hpp"
#include "Core/Controller/Context.hpp"
#include "Core/Controller/Controller.hpp"
#include "Core/Graphics/Window.hpp"
#include <vector>
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
	std::vector<Core::Terrain::Chunk*> chunks;

	GLint countY = CHUNK_SIZE_Y, countX = CHUNK_SIZE_X, countZ = CHUNK_SIZE_Z;

	ivec3 position = ivec3(0, 0, 0);

	for (int i = 0, y = countY, z = 0; i < 36; i++) {
		if (i % 9 == 0) {
			y -= countY;
			z = 0;
		} else if (i % 3 == 0 )
			z -= countZ;

		position.x = (i % 3) * countX;
		position.y = y;
		position.z = z;
		chunks.push_back(
			new Core::Terrain::Chunk(
				position,
				(i % 3 == 0 ? nullptr : chunks[i - 1]),
				(i < 9 ? nullptr : chunks[i - 9]),
				(i % 9 < 3 ? nullptr : chunks[i - 3]),
#if 1
				vec4(0)));
#else 
				vec4((i < 9) ? 1 - (i % 9) * 0.1 : 0, (i >= 9 &&i < 18) ? 1 - (i % 9) * 0.1 : 0, (i >= 18 && i < 27) ? 1 - (i % 9) * 0.1 : 0, 0)));
#endif
	}

	Core::Terrain::Skybox* skybox = new Core::Terrain::Skybox(Core::Terrain::SkyType::SUNNY01);

	while (!controller.getRootContext()->getWindow()->closed())
		controller
		.getRootContext()
		->getWindow()
		->update(chunks, skybox, 36, chunks[0]->getRenderMode());

	for (Core::Terrain::Chunk* chunk : chunks)
		delete chunk;
	delete skybox;

	return 0;
}

