#pragma once

#include "PrimitiveContext.hpp"
#include <map>

namespace Core {
	namespace Graphics {
		/* Information which all Block shares */
		class BlockContext : public PrimitiveContext {
		private:
			glm::vec3 *mesh, *normals;
			//std::map<TextureID, glm::vec2*> uvs;
			glm::vec2 **uvs;
			glm::vec4 center;
			Texture texture;
		public:
			BlockContext();
			~BlockContext();
			virtual glm::vec3* getMesh() const { return mesh; }
			virtual glm::vec3* getNormals() const { return normals; }
			virtual glm::vec2* getUVs(TextureID tid) { return uvs[(((GLubyte)tid & 0xF0) >> 4) * 8 + ((GLubyte)tid & 0x0F)]; }
			virtual Texture* getTexture() { return &texture; }
			virtual glm::vec4* getCenter() { return &center; }
		};
	}
}