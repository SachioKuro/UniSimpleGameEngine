#include "SkyboxBlock.hpp"

namespace Core {
	namespace Terrain {
		SkyboxBlock::SkyboxBlock() {
			// Of Course Sky
			shader = Shader::Sky;

			// Initialize Memory for our vertices / uvvs
			meshData = new GLfloat[108];
			texData = new GLfloat[72];
			// Store the start of our vert./uv-Memory
			GLfloat *tmpMesh = meshData, *tmpTex = texData;

			#pragma region Box-Data
			/* Face Front */
			// Triangle LU-F
			// LLF
			*(meshData++) = -0.5;
			*(meshData++) = -0.5;
			*(meshData++) = 0.5;
			*(texData++) = 1;
			*(texData++) = 0;
			// LUF
			*(meshData++) = -0.5;
			*(meshData++) = 0.5;
			*(meshData++) = 0.5;
			*(texData++) = 1;
			*(texData++) = 1;
			// RUF
			*(meshData++) = 0.5;
			*(meshData++) = 0.5;
			*(meshData++) = 0.5;
			*(texData++) = 0;
			*(texData++) = 1;
			// Triangle RL-F
			// LLF
			*(meshData++) = -0.5;
			*(meshData++) = -0.5;
			*(meshData++) = 0.5;
			*(texData++) = 1;
			*(texData++) = 0;
			// RUF
			*(meshData++) = 0.5;
			*(meshData++) = 0.5;
			*(meshData++) = 0.5;
			*(texData++) = 0;
			*(texData++) = 1;
			// RLF
			*(meshData++) = 0.5;
			*(meshData++) = -0.5;
			*(meshData++) = 0.5;
			*(texData++) = 0;
			*(texData++) = 0;
			/* Face Right */
			// Triangle LL-R
			// RLF
			*(meshData++) = 0.5;
			*(meshData++) = -0.5;
			*(meshData++) = 0.5;
			*(texData++) = 1;
			*(texData++) = 0;
			// RUF
			*(meshData++) = 0.5;
			*(meshData++) = 0.5;
			*(meshData++) = 0.5;
			*(texData++) = 1;
			*(texData++) = 1;
			// RLB
			*(meshData++) = 0.5;
			*(meshData++) = -0.5;
			*(meshData++) = -0.5;
			*(texData++) = 0;
			*(texData++) = 0;
			// Triangle RU-R
			// RLB
			*(meshData++) = 0.5;
			*(meshData++) = -0.5;
			*(meshData++) = -0.5;
			*(texData++) = 0;
			*(texData++) = 0;
			// RUF
			*(meshData++) = 0.5;
			*(meshData++) = 0.5;
			*(meshData++) = 0.5;
			*(texData++) = 1;
			*(texData++) = 1;
			// RUB
			*(meshData++) = 0.5;
			*(meshData++) = 0.5;
			*(meshData++) = -0.5;
			*(texData++) = 0;
			*(texData++) = 1;
			/* Face Back */
			// Triangle LU-B
			// LUB
			*(meshData++) = -0.5;
			*(meshData++) = 0.5;
			*(meshData++) = -0.5;
			*(texData++) = 0;
			*(texData++) = 1;
			// RLB
			*(meshData++) = 0.5;
			*(meshData++) = -0.5;
			*(meshData++) = -0.5;
			*(texData++) = 1;
			*(texData++) = 0;
			// RUB
			*(meshData++) = 0.5;
			*(meshData++) = 0.5;
			*(meshData++) = -0.5;
			*(texData++) = 1;
			*(texData++) = 1;
			// Triangle RL-B
			// LUB
			*(meshData++) = -0.5;
			*(meshData++) = 0.5;
			*(meshData++) = -0.5;
			*(texData++) = 0;
			*(texData++) = 1;
			// LLB
			*(meshData++) = -0.5;
			*(meshData++) = -0.5;
			*(meshData++) = -0.5;
			*(texData++) = 0;
			*(texData++) = 0;
			// RLB
			*(meshData++) = 0.5;
			*(meshData++) = -0.5;
			*(meshData++) = -0.5;
			*(texData++) = 1;
			*(texData++) = 0;
			/* Face Left */
			// Triangle LL-L
			// LLB
			*(meshData++) = -0.5;
			*(meshData++) = -0.5;
			*(meshData++) = -0.5;
			*(texData++) = 1;
			*(texData++) = 0;
			// LUB
			*(meshData++) = -0.5;
			*(meshData++) = 0.5;
			*(meshData++) = -0.5;
			*(texData++) = 1;
			*(texData++) = 1;
			// LLF
			*(meshData++) = -0.5;
			*(meshData++) = -0.5;
			*(meshData++) = 0.5;
			*(texData++) = 0;
			*(texData++) = 0;
			// Triangle RU-L
			// LLF
			*(meshData++) = -0.5;
			*(meshData++) = -0.5;
			*(meshData++) = 0.5;
			*(texData++) = 0;
			*(texData++) = 0;
			// LUB
			*(meshData++) = -0.5;
			*(meshData++) = 0.5;
			*(meshData++) = -0.5;
			*(texData++) = 1;
			*(texData++) = 1;
			// LUF
			*(meshData++) = -0.5;
			*(meshData++) = 0.5;
			*(meshData++) = 0.5;
			*(texData++) = 0;
			*(texData++) = 1;
			/* Face Lower */
			// Triangle LL-L
			// LLF
			*(meshData++) = -0.5;
			*(meshData++) = -0.5;
			*(meshData++) = 0.5;
			*(texData++) = 0;
			*(texData++) = 0;
			// RLB
			*(meshData++) = 0.5;
			*(meshData++) = -0.5;
			*(meshData++) = -0.5;
			*(texData++) = 1;
			*(texData++) = 1;
			// LLB
			*(meshData++) = -0.5;
			*(meshData++) = -0.5;
			*(meshData++) = -0.5;
			*(texData++) = 0;
			*(texData++) = 1;
			// Triangle RU-L
			// LLF
			*(meshData++) = -0.5;
			*(meshData++) = -0.5;
			*(meshData++) = 0.5;
			*(texData++) = 0;
			*(texData++) = 0;
			// RLF
			*(meshData++) = 0.5;
			*(meshData++) = -0.5;
			*(meshData++) = 0.5;
			*(texData++) = 1;
			*(texData++) = 0;
			// RLB
			*(meshData++) = 0.5;
			*(meshData++) = -0.5;
			*(meshData++) = -0.5;
			*(texData++) = 1;
			*(texData++) = 1;
			/* Face Upper */
			// Triangle LL-U
			// LUF
			*(meshData++) = -0.5;
			*(meshData++) = 0.5;
			*(meshData++) = 0.5;
			*(texData++) = 0;
			*(texData++) = 1;
			// LUB
			*(meshData++) = -0.5;
			*(meshData++) = 0.5;
			*(meshData++) = -0.5;
			*(texData++) = 0;
			*(texData++) = 0;
			// RUF
			*(meshData++) = 0.5;
			*(meshData++) = 0.5;
			*(meshData++) = 0.5;
			*(texData++) = 1;
			*(texData++) = 1;
			// Triangle RU-U
			// RUF
			*(meshData++) = 0.5;
			*(meshData++) = 0.5;
			*(meshData++) = 0.5;
			*(texData++) = 1;
			*(texData++) = 1;
			// LUB
			*(meshData++) = -0.5;
			*(meshData++) = 0.5;
			*(meshData++) = -0.5;
			*(texData++) = 0;
			*(texData++) = 0;
			// RUB
			*(meshData++) = 0.5;
			*(meshData++) = 0.5;
			*(meshData++) = -0.5;
			*(texData++) = 1;
			*(texData++) = 0;
			#pragma endregion

			// VAO
			glGenVertexArrays(1, &vertexArrayID);
			glBindVertexArray(vertexArrayID);
			// VBO for our vertices
			glGenBuffers(1, &vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			// Push to graphicscard
			glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(GLfloat), tmpMesh, GL_STATIC_DRAW);
			// Define how the vertices are structured
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
			
			// VBO for our textures
			glGenBuffers(1, &texBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, texBuffer);
			// Push to graphicscard
			glBufferData(GL_ARRAY_BUFFER, 72 * sizeof(GLfloat), tmpTex, GL_STATIC_DRAW);
			// Define how the uvs are structured
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
			
			// Clean
			meshData = texData = nullptr;
			delete[] tmpMesh;
			delete[] tmpTex;

			// Activate Vertices-VBO
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

			// Front
			texture[0].load2D("Textures/FullMoon/Front.png");
			// Right
			texture[1].load2D("Textures/FullMoon/Right.png");
			// Back
			texture[2].load2D("Textures/FullMoon/Back.png");
			// Left
			texture[3].load2D("Textures/FullMoon/Left.png");
			// Bottom
			texture[4].load2D("Textures/FullMoon/Down.png");
			// Top
			texture[5].load2D("Textures/FullMoon/Up.png");
			
			// Set Parameters
			for (Texture tex : texture) {
				tex.setCubeBoxParam();
			}

			model = mat4(1.0f);
		}

		SkyboxBlock::~SkyboxBlock() {}

		void SkyboxBlock::updateModelMatrix(vec3& position) {
			model[3].x = position.x;
			model[3].y = position.y;
			model[3].z = position.z;
		}

		void SkyboxBlock::buildMVP(mat4& view, mat4& projection) {
			//mvp = projection * view * model;
			mvp = model;
		}

		void SkyboxBlock::draw(mat4& _mvp) const {
			// Activates the Shader
			shader->activate();
			// Send MVP
			shader->setUniformMatrix4("MVP", _mvp);

			// Don't check the Distance (Skybox is always in the Background)
			glDepthMask(GL_FALSE);
			glBindVertexArray(vertexArrayID);

			// Draws face by face, with their Texture
			GLuint index = 0;
			for (Texture tex : texture) {
				tex.bind(0);
				glDrawArrays(GL_TRIANGLES, 6 * index++, 6);
			}
			glBindVertexArray(0);

			// After that check again for the Distance
			glDepthMask(GL_TRUE);
			//Deactivate the Shader
			shader->deactivate();
		}
	}
}