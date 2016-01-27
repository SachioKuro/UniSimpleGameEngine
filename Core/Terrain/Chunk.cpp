#include "Chunk.hpp"

namespace Core {
	namespace Terrain {
		GLuint64 Chunk::chunkIDs = 0;
		Chunk::Chunk(Renderer* renderer, ivec3 position, vector<vector<double>> heightmap, vector<vector<double>> blockmap, Chunk* lchunk, Chunk* tchunk, Chunk* fchunk, BlockContext* context, vec4 blendColor)
			: renderer(renderer), lchunk(lchunk), tchunk(tchunk), fchunk(fchunk), context(context), blendColor(blendColor), heightmap(heightmap), blockmap(blockmap), active(GL_FALSE), chunkID(chunkIDs++), position(position) {
			model[3].x = position.x; model[3].y = position.y; model[3].z = position.z;										// Position of Chunk
			center = vec3(position.x + CHUNK_SIZE_X / 2, position.y - CHUNK_SIZE_Y / 2, position.z - CHUNK_SIZE_Z / 2);		// Center of Chunk
			boundingRadius = sqrtf(powf(CHUNK_SIZE_X / 2, 2) + powf(CHUNK_SIZE_Y / 2, 2) + powf(CHUNK_SIZE_Z / 2, 2));		// Radius of BoundingSphere
		}

		Chunk::~Chunk() {
			if (active) {
				for (size_t z = 0; z < CHUNK_SIZE_Z; z++) {
					for (size_t y = 0; y < CHUNK_SIZE_Y; y++) {
						for (size_t x = 0; x < CHUNK_SIZE_X; x++) 
							delete[] blocks[z][y][x];
						delete[] blocks[z][y];
					}
					delete[] blocks[z];
				}
				delete[] blocks;
			}
		}

		GLuint Chunk::load(GLuint) {
			if (!active) {			// Load only if not already loaded
				active = GL_TRUE;
				TextureID tex;		
				GLboolean isEnabled = GL_FALSE, isCovered = GL_FALSE;
				GLuint ex = CHUNK_SIZE_X - 1, ey = CHUNK_SIZE_Y - 1, ez = CHUNK_SIZE_Z - 1;		// Border-Indieces
				blocks = new Block***[CHUNK_SIZE_Z];
				for (size_t z = 0; z < CHUNK_SIZE_Z; z++) {
					blocks[z] = new Block**[CHUNK_SIZE_Y];
					for (size_t y = 0; y < CHUNK_SIZE_Y; y++) {
						blocks[z][y] = new Block*[CHUNK_SIZE_X];
						for (size_t x = 0; x < CHUNK_SIZE_X; x++) {
							/* "Calculate" Blocktype */
							BlockType btype;
							if (heightmap[x][z] + blockmap[x][z] <= 8)		 { btype = BlockType::KIES;		    tex = TextureID::KIES01;  }
							else if (heightmap[x][z] + blockmap[x][z] <= 12) { btype = BlockType::SAND;		    tex = TextureID::SAND01;  }
							else if (heightmap[x][z] + blockmap[x][z] <= 18) { btype = BlockType::GRASS_GREEN;  tex = TextureID::GRASS01; }
							else if (heightmap[x][z] + blockmap[x][z] <= 22) { btype = BlockType::GRASS_SEMI;   tex = TextureID::GRASS02; }
						    else if (heightmap[x][z] + blockmap[x][z] <= 24) { btype = BlockType::STONE_BRIGHT; tex = TextureID::STONE03; }
							else if (heightmap[x][z] + blockmap[x][z] <= 26) { btype = BlockType::STONE_DARK;	tex = TextureID::STONE02; }
							else if (heightmap[x][z] + blockmap[x][z] <= 28) { btype = BlockType::STONE_ROUGH;	tex = TextureID::STONE01; }
							else											 { btype = BlockType::SNOW;		    tex = TextureID::SNOW01;  }

							/* Enables Blocks according the heightmap */
							if (y >= CHUNK_SIZE_Y - heightmap[x][z]) { isEnabled = GL_TRUE; isCovered = GL_FALSE; }

							/* Temporary check if Block is covered */
							if ((x != 0 || lchunk != nullptr) && (y != 0 || tchunk != nullptr) && (z != 0 || fchunk != nullptr))
							if (y >= CHUNK_SIZE_Y - heightmap[x][z])
								if (x == 0 ? GL_TRUE : blocks[z][y][x - 1]->check()) 
								if (y == 0 ? GL_TRUE : blocks[z][y - 1][x]->check()) 
								if (z == 0 ? GL_TRUE : blocks[z - 1][y][x]->check()) 
									isCovered = GL_TRUE;

							if (y >= CHUNK_SIZE_Y - WATERLEVEL && !isEnabled) {
								isEnabled = GL_TRUE;
								btype = BlockType::WATER; 
								tex = TextureID::WATER01;
							}

							blocks[z][y][x] = new Block(ivec3(BSIZE * x, BSIZE * -y, BSIZE * -z), btype, tex, mode, isEnabled);
							blocks[z][y][x]->isCovered(isCovered);
							
							/* If Block is not there uncover covered neighbor */
							if (!isEnabled && !isCovered && !(x == 0 || y == 0 || z == 0)) {
								if (blocks[z][y][x - 1]->isCovered()) { blocks[z][y][x - 1]->enable(); blocks[z][y][x - 1]->isCovered(GL_FALSE); }
								if (blocks[z][y - 1][x]->isCovered()) { blocks[z][y - 1][x]->enable(); blocks[z][y - 1][x]->isCovered(GL_FALSE); }
								if (blocks[z - 1][y][x]->isCovered()) { blocks[z - 1][y][x]->enable(); blocks[z - 1][y][x]->isCovered(GL_FALSE); }
							}
							
							/* Check Block from left side */
							if (((tchunk != nullptr && tchunk->active) || y != 0) && ((fchunk != nullptr && fchunk->active) || z != 1)) 
								if (x == 0 && z > 0 && y != ey) {
									if (y == 0 ? tchunk->blocks[z - 1][ey][0]->check() : blocks[z - 1][y - 1][0]->check())
									if (blocks[z - 1][y + 1][0]->check()) 
									if (blocks[z][y][0]->check())
									if (z == 1 ? fchunk->blocks[ez][y][0]->check() : blocks[z - 2][y][0]->check())
									if (lchunk != nullptr && lchunk->active ? lchunk->blocks[z - 1][y][ex]->check() : GL_TRUE) 
									if (blocks[z - 1][y][1]->check()) {
										blocks[z - 1][y][0]->isCovered(GL_TRUE);

										/* Check Block from right side fo left Chunk */
										if (lchunk != nullptr && lchunk->active) {
											if (y == 0 ? (lchunk->tchunk->active ? lchunk->tchunk->blocks[z - 1][ey][ex]->check() : GL_FALSE) : 
											   (lchunk->blocks[z - 1][y - 1][ex]->check()))
											if (lchunk->blocks[z - 1][y + 1][ex]->check())
											if (lchunk->blocks[z][y][ex]->check())
											if (z == 1 ? (lchunk->fchunk->active ? lchunk->fchunk->blocks[ez][y][ex]->check() : GL_FALSE) : 
											   (lchunk->blocks[z - 2][y][ex]->check()))
											if (lchunk->blocks[z - 1][y][ex - 1]->check())
												lchunk->blocks[z - 1][y][ex]->isCovered(GL_TRUE);

#if 0
											/* Check Block from top-right corner of left Chunk */
											if (y == 0 && tchunk->lchunk != nullptr && tchunk->lchunk->active)
												if (tchunk->lchunk->blocks[z - 1][ey - 1][ex]->check())
												if (lchunk->blocks[z - 1][0][ex]->check())
												if (z == 1 ? (tchunk->lchunk->fchunk->active ? tchunk->lchunk->fchunk->blocks[ez][ey][ex]->check() : GL_FALSE) : 
												   (tchunk->lchunk->blocks[z - 2][ey][ex]->check()))
												if (tchunk->lchunk->blocks[z][ey][ex]->check())
												if (tchunk->lchunk->blocks[z - 1][ey][ex - 1]->check())
												if (tchunk->blocks[z - 1][ey][0]->check())
													tchunk->lchunk->blocks[z - 1][ey][ex]->isCovered(GL_TRUE);
#endif

											/* Check Block from front-right corner of left Chunk */
											if (z == 1 && lchunk->fchunk != nullptr && lchunk->fchunk->active)
												if (y == 0 ? (lchunk->fchunk->tchunk->active ? lchunk->fchunk->tchunk->blocks[ez][ey][ex]->check() : GL_FALSE) : 
												   (lchunk->fchunk->blocks[ez][y - 1][ex]->check()))
												if (lchunk->fchunk->blocks[ez][y + 1][ex]->check())
												if (lchunk->fchunk->blocks[ez][y][ex - 1]->check())
												if (fchunk->blocks[ez][y][0]->check())
												if (lchunk->blocks[0][y][ex]->check())
												if (lchunk->fchunk->blocks[ez - 1][y][ex]->check())
													lchunk->fchunk->blocks[ez][y][ex]->isCovered(GL_TRUE);
										}
									}
								}

#if 0
							/* Check Block from top side */
							if (tchunk != nullptr && tchunk->active && ((lchunk != nullptr && lchunk->active) || x != 0) && ((fchunk != nullptr && fchunk->active) || z != 1)) {
								if (y == 0 && z > 0 && x != ex) {
									if (tchunk->blocks[z - 1][ey][x]->check())
									if (blocks[z - 1][1][x]->check())
									if (x == 0 ? lchunk->blocks[z - 1][0][ex]->check() : blocks[z - 1][0][x - 1]->check())
									if (blocks[z - 1][0][x + 1]->check())
									if (blocks[z][0][x]->check())
									if (z == 1 ? fchunk->blocks[ez][0][x]->check() : blocks[z - 2][0][x]->check()) {
										blocks[z - 1][0][x]->isCovered(GL_TRUE);
										
										if (tchunk->blocks[z - 1][ey - 1][x]->check())
										if (x == 0 ? (tchunk->lchunk->active ? tchunk->lchunk->blocks[z - 1][ey][ex]->check() : GL_FALSE) : tchunk->blocks[z - 1][ey][x - 1]->check())
										if (tchunk->blocks[z - 1][ey][x + 1]->check()) 
										if (tchunk->blocks[z][ey][x]->check())
										if (z == 1 ? (tchunk->fchunk->active ? tchunk->fchunk->blocks[ez][ey][x]->check() : GL_FALSE) : tchunk->blocks[z - 2][ey][x]->check())
											tchunk->blocks[z - 1][ey][x]->isCovered(GL_TRUE);
										
										if (z == 1) 
											if (fchunk->tchunk != nullptr && fchunk->tchunk->active) 
												if (fchunk->tchunk->blocks[ez][ey - 1][x]->check())
												if (fchunk->blocks[ez][0][x]->check())
												if (x == 0 ? (fchunk->tchunk->lchunk->active ? fchunk->tchunk->lchunk->blocks[ez][ey][ex]->check() : GL_FALSE) : fchunk->tchunk->blocks[ez][ey][x - 1]->check())
												if (fchunk->tchunk->blocks[ez][ey][x + 1]->check())
												if (tchunk->blocks[0][ey][x])
												if (fchunk->tchunk->blocks[ez - 1][ey][x]->check())
													fchunk->tchunk->blocks[ez][ey][x]->isCovered(GL_TRUE);
									}
								}
							}
#endif

							/* Check Block from front side */
							if (((lchunk != nullptr && lchunk->active) || x != 0) && ((tchunk != nullptr && tchunk->active) || y != 0)) {
								if (z == 1 && y != ey && x != ex) {
									if (y == 0 ? tchunk->blocks[0][ey][x]->check() : blocks[0][y - 1][x]->check())
									if (blocks[0][y + 1][x]->check())
									if (blocks[0][y][x + 1]->check())
									if (x == 0 ? lchunk->blocks[0][y][ex]->check() : blocks[0][y][x - 1]->check())
									if (fchunk != nullptr && fchunk->active ? fchunk->blocks[ez][y][x]->check() : GL_TRUE)
									if (blocks[1][y][x]->check()) {
										blocks[0][y][x]->isCovered(GL_TRUE);
										
										/* Check Block from backside of front Chunk */
										if (fchunk != nullptr && fchunk->active)
											if (y == 0 ? (fchunk->tchunk->active ? fchunk->tchunk->blocks[ez][ey][x]->check() : GL_FALSE) : fchunk->blocks[ez][y - 1][x]->check())
											if (x == 0 ? (fchunk->lchunk->active ? fchunk->lchunk->blocks[ez][y][ex]->check() : GL_FALSE) : fchunk->blocks[ez][y][x - 1]->check())
											if (fchunk->blocks[ez][y + 1][x]->check())
											if (fchunk->blocks[ez][y][x + 1]->check())
											if (fchunk->blocks[ez - 1][y][x]->check())
												fchunk->blocks[ez][y][x]->isCovered(GL_TRUE);
										
									}
								}
							}
							
#if 0
							if (x == 0 && y == 0 && z == 0 && fchunk != nullptr && lchunk != nullptr && tchunk != nullptr && fchunk->active && lchunk->active && fchunk->active) 
								if (lchunk->tchunk->fchunk->active ? lchunk->tchunk->fchunk->blocks[ez][ey - 1][ex]->check() : GL_FALSE)
								if (lchunk->fchunk->active ? lchunk->fchunk->blocks[ez][0][ex]->check() : GL_FALSE)
								if (lchunk->tchunk->fchunk->active ? lchunk->tchunk->fchunk->blocks[ez][ey][ex - 1]->check() : GL_FALSE)
								if (fchunk->tchunk->active ? fchunk->tchunk->blocks[ez][ey][0]->check() : GL_FALSE)
								if (lchunk->tchunk->active ? lchunk->tchunk->fchunk->blocks[ez - 1][ey][ex]->check() : GL_FALSE)
								if (tchunk->lchunk->active ? tchunk->lchunk->blocks[0][ey][ex]->check() : GL_FALSE)
									lchunk->tchunk->fchunk->blocks[ez][ey][ex]->isCovered(GL_TRUE);
#endif

							/* Fill height-gaps betwwen Chunks*/
							if (x == 0 && lchunk != nullptr && lchunk->active)
								if (y >= CHUNK_SIZE_Y - lchunk->heightmap[ex][z] && y <= CHUNK_SIZE_Y - heightmap[x][z]) {
									lchunk->blocks[z][y][ex]->isCovered(GL_FALSE);
									lchunk->blocks[z][y][ex]->enable();
								}

							if (z == 0 && fchunk != nullptr && fchunk->active)
								if (y >= CHUNK_SIZE_Y - fchunk->heightmap[x][ez] && y <= CHUNK_SIZE_Y - heightmap[x][z]) {
									fchunk->blocks[ez][y][x]->isCovered(GL_FALSE);
									fchunk->blocks[ez][y][x]->enable();
								}
								
							isEnabled = GL_FALSE; isCovered = GL_FALSE;
						}
					}
				}

			}
			return 0;
		}

		void Chunk::unload(GLuint) {
			if (active) {
				active = GL_FALSE;

				for (size_t z = 0; z < CHUNK_SIZE_Z; z++) {
					for (size_t y = 0; y < CHUNK_SIZE_Y; y++) {
						for (size_t x = 0; x < CHUNK_SIZE_X; x++) {
							delete[] blocks[z][y][x];
						}
						delete[] blocks[z][y];
					}
					delete[] blocks[z];
				}
				delete[] blocks;
				DEBUG_F("Deleted Chunk [%llu]\n", chunkID);
			}
		}

		void Chunk::draw(mat4 projection, mat4 view, vec4 clippingPlane, Camera* camera, TerrainType type) {
			if (active) {
				vec4* planes = camera->getFrustumPlanes(&projection);
				GLboolean toDraw = GL_TRUE;
				for (int i = 0; i < 6; i++)
					toDraw &= 0 > planes[i].x * center.x + planes[i].y * center.y + planes[i].z * center.z + planes[i].w - boundingRadius;
				
				if (toDraw) {
					// Setup rendering
					if (type == TerrainType::LAND) {
						renderer->useShader(Shader::Block);
						renderer->activateShader();
						renderer->start();
						// Set shadervariables
						renderer->getActiveShader()->setUniformMatrix4("MODEL", model);
						renderer->getActiveShader()->setUniformMatrix4("VIEW", view);
						renderer->getActiveShader()->setUniformMatrix4("PROJECTION", projection);
						renderer->getActiveShader()->setUniformVector3("lightPosition", vec3(-1000, 2000, -1000));
						renderer->getActiveShader()->setUniformVector4("clippingPlane", clippingPlane);
						glDisable(GL_BLEND);
						int topLayer = -1;
						// Submit Blocks
						for (size_t z = 0; z < CHUNK_SIZE_Z; z++) {
							for (size_t y = 0; y < CHUNK_SIZE_Y; y++) {
								for (size_t x = 0; x < CHUNK_SIZE_X; x++) {
									if (blocks[z][y][x]->getBlockType() == BlockType::WATER && (topLayer == -1 || topLayer == y)) { topLayer = y; waterBlocks.push_back(blocks[z][y][x]); }
									else if (blocks[z][y][x]->getBlockType() != BlockType::WATER) blocks[z][y][x]->submit(renderer, context);
								}
							}
						}

						// Ready for render
						renderer->end();
						// Starts rendering
						renderer->draw();
						renderer->deactivateShader();
					} else {
						// Setup rendering
						renderer->useShader(Shader::Water);
						renderer->activateShader();
						renderer->start();
						// Set shadervariables
						renderer->getActiveShader()->setUniformMatrix4("MODEL", model);
						renderer->getActiveShader()->setUniformMatrix4("VIEW", view);
						renderer->getActiveShader()->setUniformMatrix4("PROJECTION", projection);
						glEnable(GL_BLEND);
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
						// Submit Blocks
						for (Block* block : waterBlocks)
							block->submit(renderer, context, vec2(24, 30));

						// Ready for render
						renderer->end();
						// Starts rendering
						renderer->draw();
						renderer->deactivateShader();

						waterBlocks.clear();
					}
				}
			}
		}
	}
}