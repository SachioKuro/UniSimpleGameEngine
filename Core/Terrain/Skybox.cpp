#include "Skybox.hpp"

namespace Core {
	namespace Terrain {
		Skybox::Skybox(SkyType type) {
			skyboxBlock = new SkyboxBlock(type);
		}

		Skybox::~Skybox() {
			delete skyboxBlock;
		}
	}
}