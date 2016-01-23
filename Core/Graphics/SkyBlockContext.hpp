#pragma once

#include "PrimitiveContext.hpp"

namespace Core {
	namespace Graphics {
		class SkyBlockContext : public PrimitiveContext {
		private:
			vec3 *mesh, *normals;
			vec2 *uvs;
			Texture texture;
		public:
			SkyBlockContext();
			~SkyBlockContext();
			virtual vec3* getMesh() const { return mesh; }
			virtual vec3* getNormals() const { return normals; }
			virtual vec2* getUVs(TextureID tid) { return uvs; }
			virtual Texture* getTexture() { return &texture; }
			virtual vec4* getCenter() { return nullptr; }
		};
	}
}