#pragma once

#include "../Utils/GL.hpp"
#include "SkyboxBlock.hpp"

namespace Core {
	namespace Terrain {
		/* Global Light */
		struct GlobalLight {
			glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
			glm::vec3 position;
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