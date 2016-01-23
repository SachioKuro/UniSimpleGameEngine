#pragma once

#include "../Utils/GL.hpp"
#include "Texture.hpp"

namespace Core {
	namespace Graphics {
		using namespace glm;

		struct Vertex {
			vec3 position;
			vec2 uv;
			vec3 normal;
		};

		class PrimitiveContext {
		public:
			virtual vec3* getMesh() const { return nullptr; };
			virtual vec2* getUVs(TextureID tid) { return nullptr; };
			virtual vec3* getNormals() const { return nullptr; };
			virtual Texture* getTexture() { return nullptr; }
			virtual vec4* getCenter() { return nullptr; }
		};
	}
}