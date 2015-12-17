#pragma once

#include "Block.hpp"
#include "../Graphics/Texture.hpp"
#include <vector>

namespace Core {
	namespace Terrain {
		class SkyboxBlock : public Block {
		private:
			GLfloat *texData = 0, *meshData = 0;
			GLuint vertexArrayID, vertexBuffer, texBuffer;
			Shader* shader;
			Texture texture;
		public:
			SkyboxBlock();
			~SkyboxBlock();
			virtual void draw(GLubyte renderType, mat4 mvp, GLint index) const;
		};
	}
}