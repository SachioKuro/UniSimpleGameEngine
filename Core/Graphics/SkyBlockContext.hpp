#pragma once

#include "PrimitiveContext.hpp"

namespace Core {
	namespace Graphics {
		class SkyBlockContext : public PrimitiveContext {
		private:
			ivec3 *mesh, *normals;
			vec2 *uvs;
			Texture texture;
		public:
			SkyBlockContext();
			~SkyBlockContext();
			virtual ivec3* getMesh() const { return mesh; }
			virtual ivec3* getNormals() const { return normals; }
			virtual vec2* getUVs() const { return uvs; }
			virtual Texture* getTexture() { return &texture; }
		};
	}
}