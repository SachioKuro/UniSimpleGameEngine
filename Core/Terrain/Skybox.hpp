#pragma once

#include "../Utils/GL.hpp"
#include "SkyboxBlock.hpp"

namespace Core {
	namespace Terrain {
		using namespace glm;
		using namespace Graphics;

		struct GlobalLight {
			vec3 color = vec3(1.0f, 1.0f, 1.0f);
			vec3 position;
			GLfloat intensity;
		};

		class Skybox {
		private:
			SkyboxBlock skyboxBlock;
		public:
			Skybox();
			~Skybox();
			SkyboxBlock getSkyboxBlock() const { return skyboxBlock; }
		};
	}
}