#pragma once

#include "PrimitiveContext.hpp"
#include <map>
#include <unordered_map>

namespace Core {
	namespace Graphics {
		class BlockContext : public PrimitiveContext {
		private:
			vec3 *mesh, *normals;
			map<TextureID, vec2*> uvs;
			vec4 center;
			Texture texture;
		public:
			BlockContext();
			~BlockContext();
			virtual vec3* getMesh() const { return mesh; }
			virtual vec3* getNormals() const { return normals; }
			virtual vec2* getUVs(TextureID tid) { return uvs[tid]; }
			virtual Texture* getTexture() { return &texture; }
			virtual vec4* getCenter() { return &center; }
		};
	}
}