#include "Core\Terrain\Chunk.hpp"
#include "Core/Input/Input.hpp"
#include "Core/Controller/Context.hpp"
#include "Core/Controller/Controller.hpp"
#include "Core/Graphics/Window.hpp"

#include "Core\Terrain\WorldTree.hpp"
#include <iomanip>

#include "Core/Utils/PerlinNoise.hpp"

#include <vector>
int main(void) {
	using namespace Core::Graphics;
	using namespace Core::Utils;
	using namespace Core::Terrain;
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


	Texture texture;
	// Define texturemap
	texture.load2D("Textures/texturemap64.png");
	texture.setCubeBoxParam();
	texture.defineTextureInfo(vec2(8, 8), vec2(64, 64));

	Core::Terrain::Skybox* skybox = new Core::Terrain::Skybox(Core::Terrain::SkyType::SUNNY01);
	Core::Terrain::WorldTree wt(&texture);

	while (!controller.getRootContext()->getWindow()->closed()) {
		controller
			.getRootContext()
			->getWindow()
			->update(&(wt.getChunks()), skybox, 36, chunks[0]->getRenderMode());
		
	}

	delete skybox;

	return 0;
}

