#pragma once

#include "../Utils/GL.hpp"
#include "Texture.hpp"

namespace Core {
	namespace Graphics {
		using namespace glm;

		struct Vertex {
			vec3 position;
			vec2 uv;
		};

		class PrimitiveContext {
		public:
			virtual ivec3* getMesh() const { return nullptr; };
			virtual vec2* getUVs(TextureID tid) { return nullptr; };
			virtual ivec3* getNormals() const { return nullptr; };
			virtual Texture* getTexture() { return nullptr; }
			virtual vec4* getCenter() { return nullptr; }
		};
	}
}