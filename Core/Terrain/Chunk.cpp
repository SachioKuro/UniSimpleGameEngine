#include "Chunk.hpp"
#include "../Utils/Output.hpp"

namespace Core {
	namespace Terrain {
		Chunk::Chunk() {
			renderMode = RenderMode::WIRED;
			blocks = new Block**[CHUNK_SIZE_X];
			for (size_t x = 0; x < CHUNK_SIZE_X; x++) {
				blocks[x] = new Block*[CHUNK_SIZE_Y];
				for (size_t y = 0; y < CHUNK_SIZE_Y; y++) {
					blocks[x][y] = new Block[CHUNK_SIZE_Z];
					for (size_t z = 0; z < CHUNK_SIZE_Z; z++) {
						blocks[x][y][z] = Block(vec3(BLOCKSIZE * x, BLOCKSIZE * y, BLOCKSIZE * z), (BlockType)0, GL_TRUE);
					}
				}
			}
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
			delete[] blocks;

			DEBUG_F("Deleted Chunk [%llu]\n", chunkID);
		}

		void Chunk::buildBlockMesh(vec3& position, GLfloat*& meshPointer) {
			/* Face Front */
			// Triangle LU-F
			// LLF
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			// RUF
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			// LUF
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			// Triangle RL-F
			// LLF
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			// RLF
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			// RUF
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			/* Face Right */
			// Triangle LL-R
			// RLF
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			// RLB
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			// RUF
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			// Triangle RU-R
			// RLB
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			// RUB
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			// RUF
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			/* Face Back */
			// Triangle LU-B
			// LUB
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			// RUB
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			// RLB
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			// Triangle RL-B
			// LUB
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			// RLB
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			// LLB
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			/* Face Left */
			// Triangle LL-L
			// LLB
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			// LLF
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			// LUB
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			// Triangle RU-L
			// LLF
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			// LUF
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			// LUB
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			/* Face Lower */
			// Triangle LL-L
			// LLF
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			// LLB
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			// RLB
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			// Triangle RU-L
			// LLF
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			// RLF
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z;
			// RLB
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y;
			*(meshPointer++) = position.z - 1;
			/* Face Upper */
			// Triangle LL-U
			// LUF
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			// RUF
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			// LUB
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			// Triangle RU-U
			// RUF
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z;
			// RUB
			*(meshPointer++) = position.x + 1;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
			// LUB
			*(meshPointer++) = position.x;
			*(meshPointer++) = position.y + 1;
			*(meshPointer++) = position.z - 1;
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
			GLfloat* meshPointer = meshData;

			if (renderMode == RenderMode::SOLID)
				for (size_t x = 0; x < CHUNK_SIZE_X; x++)
					for (size_t y = 0; y < CHUNK_SIZE_Y; y++)
						for (size_t z = 0; z < CHUNK_SIZE_Z; z++)
							buildBlockMesh(blocks[x][y][z].getPosition(), meshPointer);
			else if (renderMode == RenderMode::WIRED)
				for (size_t x = 0; x < CHUNK_SIZE_X; x++)
					for (size_t y = 0; y < CHUNK_SIZE_Y; y++)
						for (size_t z = 0; z < CHUNK_SIZE_Z; z++)
							buildBlockMeshWired(blocks[x][y][z].getPosition(), meshPointer);
		}


	}
}