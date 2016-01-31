#pragma once

#include "../Graphics/Shader.hpp"
#include "../Graphics/Drawable.hpp"
#include "../Graphics/Renderer.hpp"
#include "../Graphics/SkyBlockContext.hpp"
#include "../Utils/output.hpp"
#include "Chunk.hpp"
#include "../Graphics/Camera.hpp"

namespace Core {
	namespace Terrain {
		/* Type of the Sky (Night, Stormy, Sunny, ...) */
		enum class SkyType {
			NONE,
			SUNNY01,
			NIGHT01
		};

		/* Physical-Part */
		class SkyboxBlock : public Graphics::Drawable {
		private:
			SkyType stype = SkyType::SUNNY01;
			glm::mat4 model = glm::mat4(1);
			Graphics::Renderer* renderer;
			Graphics::SkyBlockContext context;
		public:
			SkyboxBlock(SkyType stype);
			~SkyboxBlock();
			Graphics::SkyBlockContext* getContext() const { return nullptr; }
			/* Draws our Sky */
			void draw(glm::vec3& position, glm::mat4& view, glm::mat4& projection, Graphics::Camera* camera);
		};
	}
}