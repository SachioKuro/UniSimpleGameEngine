#include "WorldTree.hpp"

namespace Core {
	namespace Terrain {
		WorldTree::WorldTree() {
			noise = new PerlinNoise(1337+4, 100000, 100000, CHUNK_SIZE_X, CHUNK_SIZE_Z, CHUNK_SIZE_Y, 6000);
			for (int x = 0; x < WORLDSIZE; x++) {
				vector<Chunk*> chunkz;
				chunkz.clear();
				for (int z = 0; z < WORLDSIZE; z++) {
					chunkz.push_back(
						new Chunk(ivec3(x * CHUNK_SIZE_X, 0, -z * CHUNK_SIZE_Z), *(noise->createNoise(x * CHUNK_SIZE_X, z * CHUNK_SIZE_Z)),
							x == 0 ? nullptr : chunks[x - 1][z],
							nullptr,
							z == 0 ? nullptr : chunkz[z - 1],
							&blockContext)
						);
				}
				chunks.push_back(chunkz);
			}
		}

		WorldTree::~WorldTree() {
			for (int x = 0; x < WORLDSIZE; x++)
				for (int y = 0; y < WORLDSIZE; y++)
					delete chunks[x][y];
			delete noise;
		}
	}
}