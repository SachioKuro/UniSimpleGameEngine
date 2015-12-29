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

	vec3 position = vec3(0, 0, 0);
	for (int i = 0, j = 0, k = 0; i < 27; i++) {
		if (i % 9 == 0) {
			j -= countY;
			k = 0;
		}
		if (i % 3 == 0)
			k += countZ;

		position.x = (i % 3) * countX;
		position.y = j;
		position.z = k;
		chunks.push_back(new Core::Terrain::Chunk(position, (i % 3 == 0 ? nullptr : chunks[i - 1]), (i < 9 ? nullptr : chunks[i - 9]) ,(i % 9 < 3 ? nullptr : chunks[i - 3])));
	}

	Core::Terrain::Skybox* skybox = new Core::Terrain::Skybox(Core::Terrain::SkyType::SUNNY01);

	while (!controller.getRootContext()->getWindow()->closed())
		controller
		.getRootContext()
		->getWindow()
		->update(chunks, skybox, 125, chunks[0]->getRenderMode());

	for (Core::Terrain::Chunk* chunk : chunks)
		delete chunk;
	delete skybox;

	return 0;
}

