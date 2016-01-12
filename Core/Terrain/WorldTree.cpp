#include "WorldTree.hpp"

namespace Core {
	namespace Terrain {
		WorldTree::WorldTree(Texture* texture) {
			for (int x = 0; x < WORLDSIZE; x++) {
				vector<vector<Chunk*>> chunky;
				for (int y = 0; y < 2; y++) {
					vector<Chunk*> chunkz;
					for (int z = 0; z < WORLDSIZE; z++) {
						chunkz.push_back(
							new Chunk(ivec3(x * CHUNK_SIZE_X, -y * CHUNK_SIZE_Y, -z * CHUNK_SIZE_Z), texture, 
								x == 0 ? nullptr : chunks[x - 1][y][z], 
								y == 0 ? nullptr : chunky[y - 1][z], 
								z == 0 ? nullptr : chunkz[z - 1]));
					}
					chunky.push_back(chunkz);
				}
				chunks.push_back(chunky);
			}
		}

	}
}