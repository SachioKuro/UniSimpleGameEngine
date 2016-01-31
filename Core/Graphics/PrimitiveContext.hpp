#pragma once

#include "../Utils/GL.hpp"
#include "Texture.hpp"

namespace Core {
	namespace Graphics {
		/* Matches the structure of Information,
		   which will be send to the GPU through the MapBuffer */
		struct Vertex {
			glm::vec3 position;
			glm::vec2 uv;
			glm::vec3 normal;
		};

		/* Collection of Information, which will be shared */
		class PrimitiveContext {
		public:
			virtual glm::vec3* getMesh() const { return nullptr; };
			virtual glm::vec2* getUVs(TextureID tid) { return nullptr; };
			virtual glm::vec3* getNormals() const { return nullptr; };
			virtual Texture* getTexture() { return nullptr; }
			virtual glm::vec4* getCenter() { return nullptr; }
		};
	}
}