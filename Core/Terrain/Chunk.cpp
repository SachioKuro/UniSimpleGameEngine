#include "Chunk.hpp"

namespace Core {
	namespace Terrain {
		GLuint64 Chunk::chunkIDs = 0;
		Chunk::Chunk(ivec3 position, vector<vector<double>> heightmap, Texture* texture, Chunk* lchunk, Chunk* tchunk, Chunk* fchunk, vec4 blendColor)
			: lchunk(lchunk), tchunk(tchunk), fchunk(fchunk), blendColor(blendColor), texture(texture), heightmap(heightmap) {
			chunkID = chunkIDs++;
			setRenderMode(RenderMode::SOLID);

			model[3].x = position.x;
			model[3].y = position.y;
			model[3].z = position.z;

			active = GL_TRUE;

			if (active) {
				active = GL_FALSE;
				load(0);
			}

		}

		Chunk::~Chunk() {
			if (active) {
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
				delete renderer;
				DEBUG_F("Deleted Chunk [%llu]\n", chunkID);
			}
		}

		void Chunk::setRenderMode(RenderMode mode) {
			// Setup rendermode
			this->mode = mode;
			switch (mode) {
			case RenderMode::SOLID:
				glEnable(GL_DEPTH_TEST);
				glDisable(GL_BLEND);
				vertexCount = 36;
				break;
			case RenderMode::WIRED:
				glEnable(GL_BLEND);
				glDisable(GL_DEPTH_TEST);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				vertexCount = 23;
				break;
			default:
				break;
			}
		}

		void Chunk::toggleRenderMode() {
			switch (mode) {
			case RenderMode::SOLID:	setRenderMode(RenderMode::WIRED); break;
			case RenderMode::WIRED:	setRenderMode(RenderMode::SOLID); break;
			default:				break;
			}
		}

		GLuint Chunk::load(GLuint) {
			if (!active) {
				active = GL_TRUE;
				// Creates blocks
				TextureID tex;
				vec2 texOffSet;
				GLboolean isEnabled = GL_FALSE, isCovered = GL_FALSE;
				GLuint ex = CHUNK_SIZE_X - 1, ey = CHUNK_SIZE_Y - 1, ez = CHUNK_SIZE_Z - 1;
				blocks = new Block***[CHUNK_SIZE_Z];
				for (size_t z = 0; z < CHUNK_SIZE_Z; z++) {
					blocks[z] = new Block**[CHUNK_SIZE_Y];
					for (size_t y = 0; y < CHUNK_SIZE_Y; y++) {
						blocks[z][y] = new Block*[CHUNK_SIZE_X];
						for (size_t x = 0; x < CHUNK_SIZE_X; x++) {
							BlockType btype = (x + y + z) & 1 ? BlockType::GRASS : BlockType::STONE;

							switch (btype) {
							case BlockType::GRASS:	tex = TextureID::GRASS01; break;
							case BlockType::STONE:	tex = TextureID::STONE01; break;
							default:				tex = TextureID::NONE;
							}

							if (y > CHUNK_SIZE_Y - heightmap[x][z]) {
								isEnabled = GL_TRUE;
								isCovered = GL_FALSE;
							}

							if (!(x == 0 || y == 0 || z == 0) && y > CHUNK_SIZE_Y - heightmap[x][z]) {
								if ((blocks[z][y][x - 1]->isEnabled() && blocks[z][y - 1][x]->isEnabled() && blocks[z - 1][y][x]->isEnabled()) ||
									(blocks[z][y][x - 1]->isCovered() && blocks[z][y - 1][x]->isCovered() && blocks[z - 1][y][x]->isCovered()) ||
									(blocks[z][y][x - 1]->isEnabled() && blocks[z][y - 1][x]->isCovered() && blocks[z - 1][y][x]->isCovered()) ||
									(blocks[z][y][x - 1]->isCovered() && blocks[z][y - 1][x]->isEnabled() && blocks[z - 1][y][x]->isCovered()) ||
									(blocks[z][y][x - 1]->isCovered() && blocks[z][y - 1][x]->isCovered() && blocks[z - 1][y][x]->isEnabled()) ||
									(blocks[z][y][x - 1]->isEnabled() && blocks[z][y - 1][x]->isEnabled() && blocks[z - 1][y][x]->isCovered()) ||
									(blocks[z][y][x - 1]->isEnabled() && blocks[z][y - 1][x]->isCovered() && blocks[z - 1][y][x]->isEnabled()) ||
									(blocks[z][y][x - 1]->isCovered() && blocks[z][y - 1][x]->isEnabled() && blocks[z - 1][y][x]->isEnabled())) {
									//isEnabled = GL_FALSE;
									isCovered = GL_TRUE;
								}
							}

							blocks[z][y][x] =
								new Block(
									ivec3(BLOCKSIZE * x, BLOCKSIZE * -y, BLOCKSIZE * -z),
									btype, texture->getTextureOffset(tex), texture->getTexturePercentage(), mode, isEnabled);
							
							if (!isEnabled && !isCovered && !(x == 0 || y == 0 || z == 0)) {
								if (blocks[z][y][x - 1]->isCovered()) blocks[z][y][x - 1]->enable();
								if (blocks[z][y - 1][x]->isCovered()) blocks[z][y - 1][x]->enable();
								if (blocks[z - 1][y][x]->isCovered()) blocks[z - 1][y][x]->enable();
								blocks[z][y][x - 1]->isCovered(GL_FALSE);
								blocks[z][y - 1][x]->isCovered(GL_FALSE);
								blocks[z - 1][y][x]->isCovered(GL_FALSE);
							}
							
							
							blocks[z][y][x]->isCovered(isCovered);

							if (((tchunk != nullptr && tchunk->active) || y != 0) && ((fchunk != nullptr && fchunk->active) || z != 1)) {
								if (x == 0 && z > 0 && y != ey) {
									if (y == 0 ? tchunk->blocks[z - 1][ey][0]->check() : blocks[z - 1][y - 1][0]->check())
									if (blocks[z - 1][y + 1][0]->check())
									if (blocks[z][y][0]->check())
									if (z == 1 ? fchunk->blocks[ez][y][0]->check() : blocks[z - 2][y][0]->check())
									if (lchunk != nullptr && lchunk->active ? lchunk->blocks[z - 1][y][ex]->check() : GL_TRUE) 
									if (blocks[z - 1][y][1]->check()) {
										blocks[z - 1][y][0]->isCovered(GL_TRUE);

										if (lchunk != nullptr && lchunk->active) {
											if (y == 0 ? (lchunk->tchunk->active ? lchunk->tchunk->blocks[z - 1][ey][ex]->check() : GL_FALSE) : lchunk->blocks[z - 1][y - 1][ex]->check())
											if (lchunk->blocks[z - 1][y + 1][ex]->check())
											if (lchunk->blocks[z][y][ex]->check())
											if (z == 1 ? (lchunk->fchunk->active ? lchunk->fchunk->blocks[ez][y][ex]->check() : GL_FALSE) : lchunk->blocks[z - 2][y][ex]->check())
											if (lchunk->blocks[z - 1][y][ex - 1]->check())
												lchunk->blocks[z - 1][y][ex]->isCovered(GL_TRUE);

											if (y == 0)
												if (tchunk->lchunk != nullptr && tchunk->lchunk->active)
													if (tchunk->lchunk->blocks[z - 1][ey - 1][ex]->check())
													if (lchunk->blocks[z - 1][0][ex]->check())
													if (z == 1 ? (tchunk->lchunk->fchunk->active ? tchunk->lchunk->fchunk->blocks[ez][ey][ex]->check() : GL_FALSE) : tchunk->lchunk->blocks[z - 2][ey][ex]->check())
													if (tchunk->lchunk->blocks[z][ey][ex]->check())
													if (tchunk->lchunk->blocks[z - 1][ey][ex - 1]->check())
													if (tchunk->blocks[z - 1][ey][0]->check())
														tchunk->lchunk->blocks[z - 1][ey][ex]->isCovered(GL_TRUE);

											if (z == 1)
												if (lchunk->fchunk != nullptr && lchunk->fchunk->active)
													if (y == 0 ? (lchunk->fchunk->tchunk->active ? lchunk->fchunk->tchunk->blocks[ez][ey][ex]->check() : GL_FALSE) : lchunk->fchunk->blocks[ez][y - 1][ex]->check())
													if (lchunk->fchunk->blocks[ez][y + 1][ex]->check())
													if (lchunk->fchunk->blocks[ez][y][ex - 1]->check())
													if (fchunk->blocks[ez][y][0]->check())
													if (lchunk->blocks[0][y][ex]->check())
													if (lchunk->fchunk->blocks[ez - 1][y][ex]->check())
														lchunk->fchunk->blocks[ez][y][ex]->isCovered(GL_TRUE);
										}
									}
								}
							}

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

							if (((lchunk != nullptr && lchunk->active) || x != 0) && ((tchunk != nullptr && tchunk->active) || y != 0)) {
								if (z == 1 && y != ey && x != ex) {
									if (y == 0 ? tchunk->blocks[0][ey][x]->check() : blocks[0][y - 1][x]->check())
									if (blocks[0][y + 1][x]->check())
									if (blocks[0][y][x + 1]->check())
									if (x == 0 ? lchunk->blocks[0][y][ex]->check() : blocks[0][y][x - 1]->check())
									if (fchunk != nullptr && fchunk->active ? fchunk->blocks[ez][y][x]->check() : GL_TRUE)
									if (blocks[1][y][x]->check()) {
										blocks[0][y][x]->isCovered(GL_TRUE);
										
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

							if (x == 0 && y == 0 && z == 0 && fchunk != nullptr && lchunk != nullptr && tchunk != nullptr && fchunk->active && lchunk->active && fchunk->active) 
								if (lchunk->tchunk->fchunk->active ? lchunk->tchunk->fchunk->blocks[ez][ey - 1][ex]->check() : GL_FALSE)
								if (lchunk->fchunk->active ? lchunk->fchunk->blocks[ez][0][ex]->check() : GL_FALSE)
								if (lchunk->tchunk->fchunk->active ? lchunk->tchunk->fchunk->blocks[ez][ey][ex - 1]->check() : GL_FALSE)
								if (fchunk->tchunk->active ? fchunk->tchunk->blocks[ez][ey][0]->check() : GL_FALSE)
								if (lchunk->tchunk->active ? lchunk->tchunk->fchunk->blocks[ez - 1][ey][ex]->check() : GL_FALSE)
								if (tchunk->lchunk->active ? tchunk->lchunk->blocks[0][ey][ex]->check() : GL_FALSE)
									lchunk->tchunk->fchunk->blocks[ez][ey][ex]->isCovered(GL_TRUE);

							if (x == 0 && lchunk != nullptr && lchunk->active)
								if (y > CHUNK_SIZE_Y - lchunk->heightmap[ex][z] && y <= CHUNK_SIZE_Y - heightmap[x][z]) {
									lchunk->blocks[z][y][ex]->isCovered(GL_FALSE);
									lchunk->blocks[z][y][ex]->enable();
								}

							if (z == 0 && fchunk != nullptr && fchunk->active)
								if (y > CHUNK_SIZE_Y - fchunk->heightmap[x][ez] && y <= CHUNK_SIZE_Y - heightmap[x][z]) {
									fchunk->blocks[ez][y][x]->isCovered(GL_FALSE);
									fchunk->blocks[ez][y][x]->enable();
								}

#if 0
							if (isEnabled && !isCovered) blocks[z][y][x]->buildBlock(ivec3(x, -1 * y, -1 * z));
#else
							blocks[z][y][x]->buildBlock(ivec3(x, -1 * y, -1 * z));
#endif

							isEnabled = GL_FALSE;
							isCovered = GL_FALSE;
						}
					}
				}

				// Set renderer
				renderer = new Renderer(CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z, vertexCount, mode);
				renderer->useShader(Shader::Block);
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
				delete renderer;
				DEBUG_F("Deleted Chunk [%llu]\n", chunkID);
			}
		}

		void Chunk::draw(mat4 projection, mat4 view, RenderMode renderMode) {
			if (active) {
				mvp = projection * view * model;
				// Setup rendering
				renderer->activateShader();
				renderer->start();
				// Set shadervariables
				renderer->getActiveShader()->setUniformMatrix4("MVP", mvp);
				renderer->getActiveShader()->setUniformInteger("renderType", mode == RenderMode::SOLID ? 0 : 1);
				renderer->getActiveShader()->setUniformVector4("blendColor", blendColor);

				// Submit Blocks
				for (size_t z = 0; z < CHUNK_SIZE_Z; z++) {
					for (size_t y = 0; y < CHUNK_SIZE_Y; y++) {
						for (size_t x = 0; x < CHUNK_SIZE_X; x++) {
							blocks[z][y][x]->submit(renderer);
						}
					}
				}

				// Ready for render
				renderer->end();
				// Starts rendering
				renderer->draw();
				renderer->deactivateShader();
			}
		}
	}
}