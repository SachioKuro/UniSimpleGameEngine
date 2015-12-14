#include "Chunk.hpp"
#include "../Utils/Output.hpp"

namespace Core {
	namespace Terrain {
		Chunk::Chunk() {
			renderMode = RenderMode::SOLID;
			Shader::init();
			blocks = new Block**[CHUNK_SIZE_X];
			for (size_t x = 0; x < CHUNK_SIZE_X; x++) {
				blocks[x] = new Block*[CHUNK_SIZE_Y];
				for (size_t y = 0; y < CHUNK_SIZE_Y; y++) {
					blocks[x][y] = new Block[CHUNK_SIZE_Z];
					for (size_t z = 0; z < CHUNK_SIZE_Z; z++) {
						blocks[x][y][z] = Block(vec3(BLOCKSIZE * x, BLOCKSIZE * y, BLOCKSIZE * z), (BlockType)0, ((x + y + z) & 1) ? GL_TRUE : GL_FALSE);
					}
				}
			}
			verticesCount = 0;
			glGenVertexArrays(1, &vertexArrayID);
			glBindVertexArray(vertexArrayID);
			glGenBuffers(1, &vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glBufferData(
				GL_ARRAY_BUFFER,
				108 * CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z * sizeof(GLfloat),
				nullptr,
				GL_DYNAMIC_DRAW);
		}

		Chunk::~Chunk() {
			for (size_t x = 0; x < CHUNK_SIZE_X; x++)
			{
				for (size_t y = 0; y < CHUNK_SIZE_Y; y++)
				{
					delete[] blocks[x][y];
				}
				delete[] blocks[x];
			}


			glDeleteBuffers(1, &vertexBuffer);
			glDeleteVertexArrays(1, &vertexArrayID);
			DEBUG_F("Deleted Chunk [%llu]\n", chunkID);
		}

		void Chunk::buildBlockMesh(vec3& position, GLfloat*& meshPointer, GLfloat*& texPointer) {
			/* Face Front */
			// Triangle LU-F
			// LLF
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			*(texPointer++) = 0.0f;
			*(texPointer++) = 1.0f;
			// RUF
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			*(texPointer++) = 1.0f;
			*(texPointer++) = 0.0f;
			// LUF
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			*(texPointer++) = 0.0f;
			*(texPointer++) = 0.0f;
			// Triangle RL-F
			// LLF
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			*(texPointer++) = 0.0f;
			*(texPointer++) = 1.0f;
			// RLF
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			*(texPointer++) = 1.0f;
			*(texPointer++) = 1.0f;
			// RUF
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			*(texPointer++) = 1.0f;
			*(texPointer++) = 0.0f;
			/* Face Right */
			// Triangle LL-R
			// RLF
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			*(texPointer++) = 0.0f;
			*(texPointer++) = 1.0f;
			// RLB
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			*(texPointer++) = 1.0f;
			*(texPointer++) = 1.0f;
			// RUF
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			*(texPointer++) = 0.0f;
			*(texPointer++) = 0.0f;
			// Triangle RU-R
			// RLB
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			*(texPointer++) = 1.0f;
			*(texPointer++) = 1.0f;
			// RUB
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			*(texPointer++) = 1.0f;
			*(texPointer++) = 0.0f;
			// RUF
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			*(texPointer++) = 0.0f;
			*(texPointer++) = 0.0f;
			/* Face Back */
			// Triangle LU-B
			// LUB
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			*(texPointer++) = 1.0f;
			*(texPointer++) = 0.0f;
			// RUB
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			*(texPointer++) = 0.0f;
			*(texPointer++) = 0.0f;
			// RLB
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			*(texPointer++) = 0.0f;
			*(texPointer++) = 1.0f;
			// Triangle RL-B
			// LUB
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			*(texPointer++) = 1.0f;
			*(texPointer++) = 0.0f;
			// RLB
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			*(texPointer++) = 0.0f;
			*(texPointer++) = 1.0f;
			// LLB
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			*(texPointer++) = 1.0f;
			*(texPointer++) = 1.0f;
			/* Face Left */
			// Triangle LL-L
			// LLB
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			*(texPointer++) = 0.0f;
			*(texPointer++) = 1.0f;
			// LLF
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			*(texPointer++) = 1.0f;
			*(texPointer++) = 1.0f;
			// LUB
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			*(texPointer++) = 0.0f;
			*(texPointer++) = 0.0f;
			// Triangle RU-L
			// LLF
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			*(texPointer++) = 1.0f;
			*(texPointer++) = 1.0f;
			// LUF
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			*(texPointer++) = 1.0f;
			*(texPointer++) = 0.0f;
			// LUB
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			*(texPointer++) = 0.0f;
			*(texPointer++) = 0.0f;
			/* Face Lower */
			// Triangle LL-L
			// LLF
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			*(texPointer++) = 0.0f;
			*(texPointer++) = 0.0f;
			// LLB
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			*(texPointer++) = 0.0f;
			*(texPointer++) = 1.0f;
			// RLB
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			*(texPointer++) = 1.0f;
			*(texPointer++) = 1.0f;
			// Triangle RU-L
			// LLF
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			*(texPointer++) = 0.0f;
			*(texPointer++) = 0.0f;
			// RLF
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			*(texPointer++) = 1.0f;
			*(texPointer++) = 0.0f;
			// RLB
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			*(texPointer++) = 1.0f;
			*(texPointer++) = 1.0f;
			/* Face Upper */
			// Triangle LL-U
			// LUF
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			*(texPointer++) = 0.0f;
			*(texPointer++) = 1.0f;
			// RUF
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			*(texPointer++) = 1.0f;
			*(texPointer++) = 1.0f;
			// LUB
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			*(texPointer++) = 0.0f;
			*(texPointer++) = 0.0f;
			// Triangle RU-U
			// RUF
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			*(texPointer++) = 1.0f;
			*(texPointer++) = 1.0f;
			// RUB
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			*(texPointer++) = 1.0f;
			*(texPointer++) = 0.0f;
			// LUB
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			*(texPointer++) = 0.0f;
			*(texPointer++) = 0.0f;

			verticesCount += 108;
		}

		void Chunk::buildBlockMeshWired(vec3& position, GLfloat*& meshPointer) {
			/* Face Front */
			// Left
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			// Upper
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			// V-LL-RU
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			// Lower
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			// Right
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			/* Face Right */
			// Upper
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			// V-RU-LL
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			// Lower
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			// Right
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			/* Face Back */
			// Upper
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			// V-RU-LL
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			// Lower
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			// Right
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			/* Face Left */
			// Upper
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			// V-RU-LL
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			// Lower
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			/* Face Lower */
			// V-LU-RL
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			/* Face Upper */
			// V-LU-RL
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
		}

		void Chunk::buildMesh() {
			if (!meshData) {
				meshData = new GLfloat[36 * 3 * CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z];
			}
			if (!texData) {
				texData = new GLfloat[36 * 2 * CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z];
			}
			GLfloat* texPointer = texData;
			GLfloat* meshPointer = meshData;

			if (renderMode == RenderMode::SOLID) {
				for (size_t x = 0; x < CHUNK_SIZE_X; x++)
					for (size_t y = 0; y < CHUNK_SIZE_Y; y++)
						for (size_t z = 0; z < CHUNK_SIZE_Z; z++)
							if (blocks[x][y][z].isEnabled())
								buildBlockMesh(blocks[x][y][z].getPosition(), meshPointer, texPointer);
			}
			else if (renderMode == RenderMode::WIRED) {
				for (size_t x = 0; x < CHUNK_SIZE_X; x++)
					for (size_t y = 0; y < CHUNK_SIZE_Y; y++)
						for (size_t z = 0; z < CHUNK_SIZE_Z; z++)
							if (blocks[x][y][z].isEnabled())
								buildBlockMeshWired(blocks[x][y][z].getPosition(), meshPointer);
			}
		}

		void Chunk::draw(mat4 mvp, RenderMode renderMode) const {
			glBufferSubData(
				GL_ARRAY_BUFFER,
				0,
				108 * CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z * sizeof(GLfloat),
				meshData);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
			
			GLint index = 0;
			if (renderMode == RenderMode::SOLID) {
				for (size_t x = 0; x < CHUNK_SIZE_X; x++)
					for (size_t y = 0; y < CHUNK_SIZE_Y; y++)
						for (size_t z = 0; z < CHUNK_SIZE_Z; z++)
							if (blocks[x][y][z].isEnabled()) {
								index += 36;
								blocks[x][y][z].draw(GL_TRIANGLES, mvp, index);
							}
			}
			else if (renderMode == RenderMode::WIRED) {
				for (size_t x = 0; x < CHUNK_SIZE_X; x++)
					for (size_t y = 0; y < CHUNK_SIZE_Y; y++)
						for (size_t z = 0; z < CHUNK_SIZE_Z; z++)
							if (blocks[x][y][z].isEnabled()) {
								index += 36;
								blocks[x][y][z].draw(GL_LINE, mvp, index);
							}
			}
		}
	}
}