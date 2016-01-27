#include "WorldTree.hpp"

namespace Core {
	namespace Terrain {
		WorldTree::WorldTree(Camera* camera) : camera(camera) {
			// Set renderer
			renderer = new Renderer(CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z, 36, RenderMode::SOLID);
			renderer->useShader(Shader::Block);
			chunkSizeHalfX = CHUNK_SIZE_X / 2.0, chunkSizeHalfZ = CHUNK_SIZE_Z / 2.0;
			noise = new PerlinNoise(1337 + 11, NOISE_WIDTH, NOISE_HEIGHT, CHUNK_SIZE_X, CHUNK_SIZE_Z, 40, 30000);
			bnoise = new PerlinNoise(1337 - 11, NOISE_WIDTH, NOISE_HEIGHT, CHUNK_SIZE_X, CHUNK_SIZE_Z, 8, 50000);
			vec3 cpos = camera->getCameraPosition();
			noisePos.x -= (WORLD_HALFSIZE * CHUNK_SIZE_X);
			noisePos.y -= (WORLD_HALFSIZE * CHUNK_SIZE_Z);
			chunks = new Chunk**[WORLDSIZE];
			for (int x = 0; x < WORLDSIZE; x++) {
				Chunk** chunkz = new Chunk*[WORLDSIZE];
				for (int z = 0; z < WORLDSIZE; z++) {
					chunkz[z] = new Chunk(renderer,
						ivec3(x * CHUNK_SIZE_X - CHUNK_SIZE_X * WORLDSIZE / 2.0, 0, -z * CHUNK_SIZE_Z + CHUNK_SIZE_Z * WORLDSIZE / 2.0),
						*(noise->createNoise(noisePos.x, noisePos.y)), *(bnoise->createNoise(noisePos.x, noisePos.y)),
						x == 0 ? nullptr : chunks[x - 1][z], nullptr, z == 0 ? nullptr : chunkz[z - 1], &blockContext);
					chunkz[z]->load(0);
					noisePos.y += CHUNK_SIZE_Z;
				}
				noisePos.y -= (WORLDSIZE * CHUNK_SIZE_Z);
				noisePos.x += CHUNK_SIZE_X;
				chunks[x] = chunkz;
			}
			noisePos.x -= (WORLDSIZE * CHUNK_SIZE_X);
		}

		WorldTree::~WorldTree() {
			for (int x = 0; x < WORLDSIZE; x++) {
				for (int y = 0; y < WORLDSIZE; y++) {
					delete chunks[x][y];
				}
				delete[] chunks[x];
			}
			delete[] chunks;
			delete noise;
			delete bnoise;
			delete renderer;
		}

		void WorldTree::checkAndLoad() {
			vec3 cpos = camera->getCameraPosition();
			for (int i = 0; i < WORLDSIZE; i++) {
				for (int j = 0; j < WORLDSIZE; j++) {
					if (chunks[i][j]->getCenter().x + chunkSizeHalfX > cpos.x &&
						chunks[i][j]->getCenter().x - chunkSizeHalfX < cpos.x &&
						chunks[i][j]->getCenter().z + chunkSizeHalfZ > cpos.z &&
						chunks[i][j]->getCenter().z - chunkSizeHalfZ < cpos.z) {
						if (chunks[i][j] == currentChunk) {
						} else {
							if (currentChunk != nullptr) {
								if (currentChunk->getCenter().x + chunkSizeHalfX < cpos.x) {
									currentChunk = chunks[i][j];
#if 1
									noisePos.x += CHUNK_SIZE_X;
									for (int l = 0; l < WORLDSIZE; l++) {
										delete chunks[0][l];
										for (int k = 0; k < WORLDSIZE - 1; k++) chunks[k][l] = chunks[k + 1][l];
										chunks[WORLDSIZE - 1][l] =
											new Chunk(renderer, ivec3(chunks[WORLDSIZE - 2][l]->getCenter().x + chunkSizeHalfX, 0, chunks[WORLDSIZE - 2][l]->getCenter().z + chunkSizeHalfZ),
												*(noise->createNoise(noisePos.x + (WORLDSIZE - 1) * CHUNK_SIZE_X, noisePos.y)), 
												*(bnoise->createNoise(noisePos.x + (WORLDSIZE - 1) * CHUNK_SIZE_X, noisePos.y)),
												chunks[WORLDSIZE - 2][l], nullptr, l == 0 ? nullptr : chunks[WORLDSIZE - 1][l - 1], &blockContext);
										chunks[0][l]->setLeftChunk(nullptr);
										chunks[WORLDSIZE - 1][l]->load(0);
										noisePos.y += CHUNK_SIZE_Z;
									}
									noisePos.y -= WORLDSIZE * CHUNK_SIZE_Z;
#endif
								} else if (currentChunk->getCenter().x - chunkSizeHalfX > cpos.x) {
									currentChunk = chunks[i][j];
#if 1
									noisePos.x -= CHUNK_SIZE_X;
									for (int l = 0; l < WORLDSIZE; l++) {
										delete chunks[WORLDSIZE - 1][l];
										for (int k = WORLDSIZE - 1; k > 0; k--) chunks[k][l] = chunks[k - 1][l];
										chunks[0][l] =
											new Chunk(renderer, ivec3(chunks[1][l]->getCenter().x - CHUNK_SIZE_X - chunkSizeHalfX, 0, chunks[1][l]->getCenter().z + chunkSizeHalfZ),
												*(noise->createNoise(noisePos.x, noisePos.y)), 
												*(bnoise->createNoise(noisePos.x, noisePos.y)),
												nullptr, nullptr, l == 0 ? nullptr : chunks[0][l - 1], &blockContext);
										chunks[1][l]->setLeftChunk(chunks[0][l]);
										chunks[0][l]->load(0);
										noisePos.y += CHUNK_SIZE_Z;
									}
									noisePos.y -= WORLDSIZE * CHUNK_SIZE_Z;
#endif
								} else if (currentChunk->getCenter().z + chunkSizeHalfZ < cpos.z) {
									currentChunk = chunks[i][j];
#if 1
									noisePos.y -= CHUNK_SIZE_Z;
									for (int k = 0; k < WORLDSIZE; k++) {
										delete chunks[k][WORLDSIZE - 1];
										for (int l = WORLDSIZE - 1; l > 0; l--) chunks[k][l] = chunks[k][l - 1];
										chunks[k][0] =
											new Chunk(renderer, ivec3(chunks[k][1]->getCenter().x - chunkSizeHalfX, 0, chunks[k][1]->getCenter().z + CHUNK_SIZE_Z + chunkSizeHalfZ),
												*(noise->createNoise(noisePos.x, noisePos.y)), 
												*(bnoise->createNoise(noisePos.x, noisePos.y)),
												k == 0 ? nullptr : chunks[k - 1][0], nullptr, nullptr, &blockContext);
										chunks[k][1]->setFrontChunk(chunks[k][0]);
										chunks[k][0]->load(0);
										noisePos.x += CHUNK_SIZE_X;
									}
									noisePos.x -= WORLDSIZE * CHUNK_SIZE_X;
#endif
								} else if (currentChunk->getCenter().z - chunkSizeHalfZ > cpos.z) {
									currentChunk = chunks[i][j];
#if 1
									noisePos.y += CHUNK_SIZE_Z;
									for (int k = 0; k < WORLDSIZE; k++) {
										delete chunks[k][0];
										for (int l = 0; l < WORLDSIZE - 1; l++) chunks[k][l] = chunks[k][l + 1];
										chunks[k][WORLDSIZE - 1] =
											new Chunk(renderer, ivec3(chunks[k][WORLDSIZE - 2]->getCenter().x - chunkSizeHalfX, 0, chunks[k][WORLDSIZE - 2]->getCenter().z - chunkSizeHalfZ),
												*(noise->createNoise(noisePos.x, noisePos.y + (WORLDSIZE - 1) * CHUNK_SIZE_Z)), 
												*(bnoise->createNoise(noisePos.x, noisePos.y + (WORLDSIZE - 1) * CHUNK_SIZE_Z)),
												k == 0 ? nullptr : chunks[k - 1][WORLDSIZE - 1], nullptr, chunks[k][WORLDSIZE - 2], &blockContext);
										chunks[k][0]->setFrontChunk(nullptr);
										chunks[k][WORLDSIZE - 1]->load(0);
										noisePos.x += CHUNK_SIZE_X;
									}
									noisePos.x -= WORLDSIZE * CHUNK_SIZE_X;
#endif
								}
							}
							if (currentChunk == nullptr) currentChunk = chunks[i][j];
						}
						break;
					}
				}
			}
		}
	}
}