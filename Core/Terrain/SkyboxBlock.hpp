#pragma once

#include <vector>

#include "../Graphics/Shader.hpp"
#include "../Graphics/Drawable.hpp"
#include "../Graphics/Renderer.hpp"
#include "../Graphics/SkyBlockContext.hpp"
#include "../Utils/output.hpp"

namespace Core {
	namespace Terrain {
		using namespace Graphics;
		using namespace std;

		/* Type of the Sky (Night, Stormy, Sunny, ...) */
		enum class SkyType {
			NONE,
			SUNNY01,
			NIGHT01
		};

		/* Physical-Part */
		class SkyboxBlock : public Drawable {
		private:
			SkyType stype = SkyType::SUNNY01;
			mat4 model = mat4(1);
			Renderer* renderer;
		public:
			SkyboxBlock(SkyType stype, RenderMode mode);
			~SkyboxBlock();
			SkyBlockContext* getContext() const { return nullptr; }
			/* Draws our Sky */
			void draw(vec3& position, mat4& view, mat4& projection);
		};
	}
}