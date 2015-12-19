#pragma once

#include "Block.hpp"
#include "../Graphics/Texture.hpp"
#include "../Utils/output.hpp"

namespace Core {
	namespace Terrain {
		/*
		 *	 Skybox-Part
		 */
		class SkyboxBlock {
		private:
			// BufferData
			GLfloat* texData = 0, *meshData = 0;
			GLuint vertexArrayID, vertexBuffer, texBuffer;

			// SkyShader
			Shader* shader;
			// SkyMap
			Texture texture[6];

			// Modelmatrix for our Sky
			mat4 model, mvp;
		public:
			SkyboxBlock();
			~SkyboxBlock();

			mat4 getModelMatrix() const { return model; }

			// Set model to new location of our Sky
			void updateModelMatrix(vec3& position);
			// Update the MVP Matrix of our Sky
			void buildMVP(mat4& view, mat4& projection);
			void setMVP(mat4& _mvp) { mvp = _mvp; }
			// Draw our Sky
			void draw(mat4& _mvp) const;
		};
	}
}