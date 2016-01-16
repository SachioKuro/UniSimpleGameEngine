#include "Core\Terrain\Chunk.hpp"
#include "Core/Input/Input.hpp"
#include "Core/Controller/Context.hpp"
#include "Core/Controller/Controller.hpp"
#include "Core/Graphics/Window.hpp"
#include "Core/Graphics/Camera.hpp"

#include "Core\Terrain\WorldTree.hpp"
#include <iomanip>

#include "Core/Utils/PerlinNoise.hpp"

#include <vector>
int main(void) {
	using namespace Core::Graphics;
	using namespace Core::Utils;
	using namespace Core::Terrain;
	using namespace Core;

	PerlinNoise pn(1337 + 5, NOISE_WIDTH, NOISE_HEIGHT, 200, 200, 40, 30000);
	pn.createNoise(500000, 500000);
	pn.debugNoise(0);

	Window window("Engine", 1024, 800);
	GLenum error = glGetError();
	Input input;
	Context con(&window, &input);


	Controller controller;
	controller.setRootContext(&con);

	GLint countY = CHUNK_SIZE_Y, countX = CHUNK_SIZE_X, countZ = CHUNK_SIZE_Z;

	ivec3 position = ivec3(0, 0, 0);

	Camera* camera = new Camera(window.getGLFWwindow());
	Skybox* skybox = new Skybox(SkyType::SUNNY01);
	WorldTree wt(camera);

	while (!controller.getRootContext()->getWindow()->closed()) {
		controller
			.getRootContext()
			->getWindow()
			->update(&wt, skybox, camera, RenderMode::SOLID);
		
	}

	delete camera;
	delete skybox;

	return 0;
}

