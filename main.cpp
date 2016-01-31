#include "Core/Terrain/Chunk.hpp"
#include "Core/Input/Input.hpp"
#include "Core/Controller/Context.hpp"
#include "Core/Controller/Controller.hpp"
#include "Core/Graphics/Window.hpp"
#include "Core/Graphics/Camera.hpp"
#include "Core/Terrain/WorldTree.hpp"
#include "Core/Utils/Debug.hpp"

#if DEBUG_LEVEL == 3
	#include "Core/Utils/PerlinNoise.hpp"
#endif

int main(void) {
	using namespace Core::Graphics;
	using namespace Core::Utils;
	using namespace Core::Terrain;
	using namespace Core;
	
#if DEBUG_LEVEL == 3
	PerlinNoise pn(1337 + 9, NOISE_WIDTH, NOISE_HEIGHT, 200, 200, 28, 25000);
	pn.createNoise(500000, 500000);
	pn.debugNoise(0);
	PerlinNoise pn2(1337 - 9, NOISE_WIDTH, NOISE_HEIGHT, 20, 20, 50, 800000);
	pn2.createNoise(500000, 500000);
	pn2.debugNoise(1);
#endif

	Window window("Engine", 1200, 800);
	Input input;
	Context con(&window, &input);

	Controller controller;
	controller.setRootContext(&con);

	Camera* camera = new Camera(window.getGLFWwindow());
	Skybox* skybox = new Skybox(SkyType::SUNNY01);
	WorldTree wt(camera);

	while (!controller.getRootContext()->getWindow()->closed()) {
		controller
			.getRootContext()
			->getWindow()
			->update(&wt, skybox, camera);
	}

	delete camera;
	delete skybox;

	return 0;
}

