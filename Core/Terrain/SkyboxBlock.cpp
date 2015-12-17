#include "SkyboxBlock.hpp"

namespace Core {
	namespace Terrain {
		SkyboxBlock::SkyboxBlock() {
			shader = Shader::Sky;
			//Shader::init();

			meshData = new GLfloat[108];
			texData = new GLfloat[72];
			GLfloat *tmpMesh = meshData, *tmpTex = texData;

			#pragma region Box-Data
			/* Face Front */
			// Triangle LU-F
			// LLF
			*(meshData++) = -1;
			*(meshData++) = -1;
			*(meshData++) = 1;
			*(texData++) = 1;
			*(texData++) = 0;
			// LUF
			*(meshData++) = -1;
			*(meshData++) = 1;
			*(meshData++) = 1;
			*(texData++) = 1;
			*(texData++) = 1;
			// RUF
			*(meshData++) = 1;
			*(meshData++) = 1;
			*(meshData++) = 1;
			*(texData++) = 0;
			*(texData++) = 1;
			// Triangle RL-F
			// LLF
			*(meshData++) = -1;
			*(meshData++) = -1;
			*(meshData++) = 1;
			*(texData++) = 1;
			*(texData++) = 0;
			// RUF
			*(meshData++) = 1;
			*(meshData++) = 1;
			*(meshData++) = 1;
			*(texData++) = 0;
			*(texData++) = 1;
			// RLF
			*(meshData++) = 1;
			*(meshData++) = -1;
			*(meshData++) = 1;
			*(texData++) = 0;
			*(texData++) = 0;
			/* Face Right */
			// Triangle LL-R
			// RLF
			*(meshData++) = 1;
			*(meshData++) = -1;
			*(meshData++) = 1;
			*(texData++) = 1;
			*(texData++) = 0;
			// RUF
			*(meshData++) = 1;
			*(meshData++) = 1;
			*(meshData++) = 1;
			*(texData++) = 1;
			*(texData++) = 1;
			// RLB
			*(meshData++) = 1;
			*(meshData++) = -1;
			*(meshData++) = -1;
			*(texData++) = 0;
			*(texData++) = 0;
			// Triangle RU-R
			// RLB
			*(meshData++) = 1;
			*(meshData++) = -1;
			*(meshData++) = -1;
			*(texData++) = 0;
			*(texData++) = 0;
			// RUF
			*(meshData++) = 1;
			*(meshData++) = 1;
			*(meshData++) = 1;
			*(texData++) = 1;
			*(texData++) = 1;
			// RUB
			*(meshData++) = 1;
			*(meshData++) = 1;
			*(meshData++) = -1;
			*(texData++) = 0;
			*(texData++) = 1;
			/* Face Back */
			// Triangle LU-B
			// LUB
			*(meshData++) = -1;
			*(meshData++) = 1;
			*(meshData++) = -1;
			*(texData++) = 0;
			*(texData++) = 1;
			// RLB
			*(meshData++) = 1;
			*(meshData++) = -1;
			*(meshData++) = -1;
			*(texData++) = 1;
			*(texData++) = 0;
			// RUB
			*(meshData++) = 1;
			*(meshData++) = 1;
			*(meshData++) = -1;
			*(texData++) = 1;
			*(texData++) = 1;
			// Triangle RL-B
			// LUB
			*(meshData++) = -1;
			*(meshData++) = 1;
			*(meshData++) = -1;
			*(texData++) = 0;
			*(texData++) = 1;
			// LLB
			*(meshData++) = -1;
			*(meshData++) = -1;
			*(meshData++) = -1;
			*(texData++) = 0;
			*(texData++) = 0;
			// RLB
			*(meshData++) = 1;
			*(meshData++) = -1;
			*(meshData++) = -1;
			*(texData++) = 1;
			*(texData++) = 0;
			/* Face Left */
			// Triangle LL-L
			// LLB
			*(meshData++) = -1;
			*(meshData++) = -1;
			*(meshData++) = -1;
			*(texData++) = 1;
			*(texData++) = 0;
			// LUB
			*(meshData++) = -1;
			*(meshData++) = 1;
			*(meshData++) = -1;
			*(texData++) = 1;
			*(texData++) = 1;
			// LLF
			*(meshData++) = -1;
			*(meshData++) = -1;
			*(meshData++) = 1;
			*(texData++) = 0;
			*(texData++) = 0;
			// Triangle RU-L
			// LLF
			*(meshData++) = -1;
			*(meshData++) = -1;
			*(meshData++) = 1;
			*(texData++) = 0;
			*(texData++) = 0;
			// LUB
			*(meshData++) = -1;
			*(meshData++) = 1;
			*(meshData++) = -1;
			*(texData++) = 1;
			*(texData++) = 1;
			// LUF
			*(meshData++) = -1;
			*(meshData++) = 1;
			*(meshData++) = 1;
			*(texData++) = 0;
			*(texData++) = 1;
			/* Face Lower */
			// Triangle LL-L
			// LLF
			*(meshData++) = -1;
			*(meshData++) = -1;
			*(meshData++) = 1;
			*(texData++) = 0;
			*(texData++) = 0;
			// RLB
			*(meshData++) = 1;
			*(meshData++) = -1;
			*(meshData++) = -1;
			*(texData++) = 1;
			*(texData++) = 1;
			// LLB
			*(meshData++) = -1;
			*(meshData++) = -1;
			*(meshData++) = -1;
			*(texData++) = 0;
			*(texData++) = 1;
			// Triangle RU-L
			// LLF
			*(meshData++) = -1;
			*(meshData++) = -1;
			*(meshData++) = 1;
			*(texData++) = 0;
			*(texData++) = 0;
			// RLF
			*(meshData++) = 1;
			*(meshData++) = -1;
			*(meshData++) = 1;
			*(texData++) = 1;
			*(texData++) = 0;
			// RLB
			*(meshData++) = 1;
			*(meshData++) = -1;
			*(meshData++) = -1;
			*(texData++) = 1;
			*(texData++) = 1;
			/* Face Upper */
			// Triangle LL-U
			// LUF
			*(meshData++) = -1;
			*(meshData++) = 1;
			*(meshData++) = 1;
			*(texData++) = 0;
			*(texData++) = 1;
			// LUB
			*(meshData++) = -1;
			*(meshData++) = 1;
			*(meshData++) = -1;
			*(texData++) = 0;
			*(texData++) = 0;
			// RUF
			*(meshData++) = 1;
			*(meshData++) = 1;
			*(meshData++) = 1;
			*(texData++) = 1;
			*(texData++) = 1;
			// Triangle RU-U
			// RUF
			*(meshData++) = 1;
			*(meshData++) = 1;
			*(meshData++) = 1;
			*(texData++) = 1;
			*(texData++) = 1;
			// LUB
			*(meshData++) = -1;
			*(meshData++) = 1;
			*(meshData++) = -1;
			*(texData++) = 0;
			*(texData++) = 0;
			// RUB
			*(meshData++) = 1;
			*(meshData++) = 1;
			*(meshData++) = -1;
			*(texData++) = 1;
			*(texData++) = 0;
			#pragma endregion

			glGenVertexArrays(1, &vertexArrayID);
			glBindVertexArray(vertexArrayID);
			glGenBuffers(1, &vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(GLfloat), tmpMesh, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
			
			glGenBuffers(1, &texBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, texBuffer);
			glBufferData(GL_ARRAY_BUFFER, 72 * sizeof(GLfloat), tmpTex, GL_STATIC_DRAW);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
			
			vector<const char*> textures;
			textures.push_back("Textures/MarbleGreen001.dds");
			textures.push_back("Textures/MarbleGreen001.dds");
			textures.push_back("Textures/SoilMud002.dds");
			textures.push_back("Textures/SoilMud002.dds");
			textures.push_back("Textures/SoilMud002.dds");
			textures.push_back("Textures/MarbleGreen001.dds");
			
			texture.loadCubeMap(textures);
			
			texture.setFiltering(GL_LINEAR, GL_LINEAR);
			texture.setCubeBoxParam();
			
		}

		SkyboxBlock::~SkyboxBlock() {}

		void SkyboxBlock::draw(GLubyte renderType, mat4 mvp, GLint index) const {
			shader->activate();
			shader->setUniformMatrix4("MVP", mvp);
			glDepthMask(GL_FALSE);
			glBindVertexArray(vertexArrayID);
			
			glBindTexture(GL_TEXTURE_CUBE_MAP, texture.getID());
			glDrawArrays(renderType, 0, 36);
			
			glBindVertexArray(0);
			glDepthMask(GL_TRUE);
			shader->deactivate();
		}
	}
}