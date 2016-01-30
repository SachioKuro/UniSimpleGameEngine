#pragma once

#include "PrimitiveContext.hpp"

namespace Core {
	namespace Graphics {
		class SkyBlockContext : public PrimitiveContext {
		private:
			glm::vec3 *mesh, *normals;
			glm::vec2 *uvs;
			Texture texture;
		public:
			SkyBlockContext();
			~SkyBlockContext();
			virtual glm::vec3* getMesh() const { return mesh; }
			virtual glm::vec3* getNormals() const { return normals; }
			virtual glm::vec2* getUVs(TextureID tid) { return uvs; }
			virtual Texture* getTexture() { return &texture; }
			virtual glm::vec4* getCenter() { return nullptr; }
		};
	}
}