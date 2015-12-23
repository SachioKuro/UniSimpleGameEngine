#pragma once

#include "../Utils/GL.hpp"
#include "SkyboxBlock.hpp"

namespace Core {
	namespace Terrain {
		using namespace glm;

		/* Global Light */
		struct GlobalLight {
			vec3 color = vec3(1.0f, 1.0f, 1.0f);
			vec3 position;
			GLfloat intensity;
		};

		/* Manages one Skybox */
		class Skybox {
		private:
			// Physical part of the skybox 
			SkyboxBlock* skyboxBlock;
		public:
			Skybox(SkyType type);
			~Skybox();
			SkyboxBlock* getSkyboxBlock() const { return skyboxBlock; }
		};
	}
}