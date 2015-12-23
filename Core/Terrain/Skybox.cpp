#include "Skybox.hpp"

namespace Core {
	namespace Terrain {
		Skybox::Skybox(SkyType type) {
			skyboxBlock = new SkyboxBlock(type, RenderMode::SOLID);
		}

		Skybox::~Skybox() {
			delete skyboxBlock;
		}
	}
}