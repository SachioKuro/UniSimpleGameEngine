#include "Chunk.hpp"

namespace Core {
	namespace Terrain {
		Chunk::Chunk(vec3 position, Chunk* lchunk, Chunk* tchunk, Chunk* bchunk) 
			: position(position), lchunk(lchunk), tchunk(tchunk), bchunk(bchunk) {
			setRenderMode(RenderMode::SOLID);

			model[3].x = position.x;
			model[3].y = position.y;
			model[3].z = position.z;

			// Define texturemap
			texture.load2D("Textures/texturemap.png");
			texture.setCubeBoxParam();
			texture.defineTextureInfo(vec2(8, 8), vec2(64, 64));

			// Creates blocks
			TextureID tex;
			vec2 texOffSet;
			GLboolean isEnabled = GL_FALSE, isCovered = GL_FALSE;
			blocks = new Block***[CHUNK_SIZE_X];
			for (size_t x = 0; x < CHUNK_SIZE_X; x++) {
				blocks[x] = new Block**[CHUNK_SIZE_Y];
				for (GLint y = CHUNK_SIZE_Y - 1; y >= 0; y--) {
					blocks[x][y] = new Block*[CHUNK_SIZE_Z];
					for (size_t z = 0; z < CHUNK_SIZE_Z; z++) {
						BlockType btype = (x + y + z) & 1 ? BlockType::GRASS : BlockType::STONE;

						switch (btype) {
						case BlockType::GRASS:	tex = TextureID::GRASS01; break;
						case BlockType::STONE:	tex = TextureID::STONE01; break;
						default:				tex = TextureID::NONE;
						}

						if (x == 0 || y == 0 || z == 0 || x == CHUNK_SIZE_X - 1 || y == CHUNK_SIZE_Y - 1 || z == CHUNK_SIZE_Z - 1) {
							isEnabled = GL_TRUE;
						} else if ((blocks[x][y][z - 1]->isEnabled() && blocks[x][y + 1][z]->isEnabled() && blocks[x - 1][y][z]->isEnabled()) ||
							       (blocks[x][y][z - 1]->isCovered() && blocks[x][y + 1][z]->isCovered() && blocks[x - 1][y][z]->isCovered()) ||
							       (blocks[x][y][z - 1]->isEnabled() && blocks[x][y + 1][z]->isCovered() && blocks[x - 1][y][z]->isCovered()) ||
							       (blocks[x][y][z - 1]->isCovered() && blocks[x][y + 1][z]->isEnabled() && blocks[x - 1][y][z]->isCovered()) ||
							       (blocks[x][y][z - 1]->isCovered() && blocks[x][y + 1][z]->isCovered() && blocks[x - 1][y][z]->isEnabled()) ||
							       (blocks[x][y][z - 1]->isEnabled() && blocks[x][y + 1][z]->isEnabled() && blocks[x - 1][y][z]->isCovered()) ||
							       (blocks[x][y][z - 1]->isEnabled() && blocks[x][y + 1][z]->isCovered() && blocks[x - 1][y][z]->isEnabled()) ||
							       (blocks[x][y][z - 1]->isCovered() && blocks[x][y + 1][z]->isEnabled() && blocks[x - 1][y][z]->isEnabled())) {
							isEnabled = GL_FALSE;
							isCovered = GL_TRUE;
						} else {
							isEnabled = GL_TRUE;
						}

						blocks[x][y][z] =
							new Block(
								vec3(BLOCKSIZE * x, BLOCKSIZE * y, BLOCKSIZE * z),
								btype, texture.getTextureOffset(tex), texture.getTexturePercentage(), mode, isEnabled);
#if 0
						if ((x + y + z) & 1)
							blocks[x][y][z]->disable();
#endif
#if 1
						if (!isEnabled && !isCovered && !(x == 0 || y == CHUNK_SIZE_Y - 1 || z == 0)) {
							if (blocks[x][y][z - 1]->isCovered()) blocks[x][y][z - 1]->enable();
							if (blocks[x][y + 1][z]->isCovered()) blocks[x][y + 1][z]->enable();
							if (blocks[x - 1][y][z]->isCovered()) blocks[x - 1][y][z]->enable();
							blocks[x][y][z - 1]->isCovered(GL_FALSE);
							blocks[x][y + 1][z]->isCovered(GL_FALSE);
							blocks[x - 1][y][z]->isCovered(GL_FALSE);
						}

						blocks[x][y][z]->isCovered(isCovered);

						if (lchunk != nullptr && (tchunk != nullptr || y != CHUNK_SIZE_Y - 1) && (bchunk != nullptr || z != CHUNK_SIZE_Z - 1)) {
							if (x == 1 && z != 0 && y != 0) {
								if ((blocks[x - 1][y][z]    ->isEnabled() || blocks[x - 1][y][z]    ->isCovered()) &&
									(blocks[x][y][z]        ->isEnabled() || blocks[x][y][z]        ->isCovered()) &&
									(blocks[x - 1][y - 1][z]->isEnabled() || blocks[x - 1][y - 1][z]->isCovered()) &&
									(y == CHUNK_SIZE_Y - 1) ?
									(tchunk->blocks[0][0][z]->isEnabled() || tchunk->blocks[0][0][z]->isCovered()) :
									(blocks[x - 1][y + 1][z]->isEnabled() || blocks[x - 1][y + 1][z]->isCovered()) && 
									(blocks[x - 1][y][z - 1]->isEnabled() || blocks[x - 1][y][z - 1]->isCovered()) &&
									(z == CHUNK_SIZE_Z - 1) ?
									(bchunk->blocks[0][y][0]->isEnabled() || bchunk->blocks[0][y][0]->isCovered()) :
									(blocks[x - 1][y][z + 1]->isEnabled() || blocks[x - 1][y][z + 1]->isCovered())) {
									if (lchunk->blocks[CHUNK_SIZE_X - 1][y][z]->isEnabled() || lchunk->blocks[CHUNK_SIZE_X - 1][y][z]->isCovered()) {
										blocks[x - 1][y][z]->disable();
										blocks[x - 1][y][z]->isCovered(GL_TRUE);
										if (lchunk->blocks[CHUNK_SIZE_X - 1][y][z]    ->isEnabled() &&
											lchunk->blocks[CHUNK_SIZE_X - 2][y][z]    ->isEnabled() || lchunk->blocks[CHUNK_SIZE_X - 2][y][z]    ->isCovered() &&
											lchunk->blocks[CHUNK_SIZE_X - 1][y - 1][z]->isEnabled() || lchunk->blocks[CHUNK_SIZE_X - 1][y - 1][z]->isCovered() && 
											lchunk->blocks[CHUNK_SIZE_X - 1][y + 1][z]->isEnabled() || lchunk->blocks[CHUNK_SIZE_X - 1][y + 1][z]->isCovered() && 
											lchunk->blocks[CHUNK_SIZE_X - 1][y][z - 1]->isEnabled() || lchunk->blocks[CHUNK_SIZE_X - 1][y][z - 1]->isCovered() && 
											lchunk->blocks[CHUNK_SIZE_X - 1][y][z + 1]->isEnabled() || lchunk->blocks[CHUNK_SIZE_X - 1][y][z + 1]->isCovered()) {
											lchunk->blocks[CHUNK_SIZE_X - 1][y][z]->disable();
										}
										if (y == CHUNK_SIZE_Y - 1) {
											if (tchunk        ->blocks[0][0][z]               ->isEnabled() || tchunk        ->blocks[0][0][z]               ->isCovered() &&
												tchunk->lchunk->blocks[CHUNK_SIZE_X - 1][0][z]->isEnabled() || tchunk->lchunk->blocks[CHUNK_SIZE_X - 1][0][z]->isCovered() &&
												tchunk        ->blocks[1][0][z]               ->isEnabled() || tchunk        ->blocks[1][0][z]               ->isCovered() &&
												tchunk		  ->blocks[0][0][z - 1]           ->isEnabled() || tchunk        ->blocks[0][0][z - 1]           ->isCovered() &&
												tchunk        ->blocks[0][0][z + 1]           ->isEnabled() || tchunk        ->blocks[0][0][z + 1]           ->isCovered() &&
												tchunk        ->blocks[0][1][z]               ->isEnabled() || tchunk        ->blocks[0][1][z]               ->isCovered()) {
												tchunk->blocks[0][0][z]->disable();
											}
										}
										if (z == CHUNK_SIZE_Z - 1) {
											if (bchunk        ->blocks[0][y][0]               ->isEnabled() || bchunk        ->blocks[0][y][0]               ->isCovered() &&
												bchunk->lchunk->blocks[CHUNK_SIZE_X - 1][y][0]->isEnabled() || bchunk->lchunk->blocks[CHUNK_SIZE_X - 1][y][0]->isCovered() &&
												bchunk        ->blocks[0][y - 1][0]           ->isEnabled() || bchunk        ->blocks[0][y - 1][0]           ->isCovered() &&
												bchunk        ->blocks[0][y + 1][0]           ->isEnabled() || bchunk        ->blocks[0][y + 1][0]           ->isCovered() &&
												bchunk        ->blocks[1][y][0]               ->isEnabled() || bchunk        ->blocks[1][y][0]               ->isCovered() &&
												bchunk        ->blocks[0][y][1]               ->isEnabled() || bchunk        ->blocks[0][y][1]               ->isCovered()) {
												bchunk->blocks[0][y][0]->disable();
											}
										}
									}
								}
							}
						}

						if (tchunk != nullptr && (lchunk != nullptr || x != 1)) {
							if (y == CHUNK_SIZE_Y - 2 && x > 0 && z > 0 && z < CHUNK_SIZE_Z - 1) {
								if ((blocks[x - 1][y + 1][z]    ->isEnabled() || blocks[x - 1][y + 1][z]    ->isCovered()) && // Mid
								    (blocks[x - 1][y][z]        ->isEnabled() || blocks[x - 1][y][z]        ->isCovered()) && // Down

									(x == 1) ?
									(lchunk->blocks[CHUNK_SIZE_X - 1][CHUNK_SIZE_Y - 1][z]->isEnabled() || lchunk->blocks[CHUNK_SIZE_X - 1][CHUNK_SIZE_Y - 1][z]->isCovered()) : // Left
									(blocks[x - 2][y + 1][z]    ->isEnabled() || blocks[x - 2][y + 1][z]    ->isCovered()) && // Left
									
									
									(blocks[x][y + 1][z]        ->isEnabled() || blocks[x][y + 1][z]        ->isCovered()) && // Right
									(blocks[x - 1][y + 1][z - 1]->isEnabled() || blocks[x - 1][y + 1][z - 1]->isCovered()) && // Front
									(blocks[x - 1][y + 1][z + 1]->isEnabled() || blocks[x - 1][y + 1][z + 1]->isCovered())) { // Back
									if (tchunk->blocks[x - 1][0][z]->isEnabled() || tchunk->blocks[x - 1][0][z]->isCovered()) {
										blocks[x - 1][y + 1][z]->disable();
										blocks[x - 1][y + 1][z]->isCovered(GL_TRUE);
										if (tchunk->blocks[x - 1][0][z]    ->isEnabled() && // To Check
											tchunk->blocks[x - 2][0][z]    ->isEnabled() || tchunk->blocks[x - 2][0][z]    ->isCovered() && // Left
											tchunk->blocks[x][0][z]        ->isEnabled() || tchunk->blocks[x][0][z]        ->isCovered() && // Right
											tchunk->blocks[x - 1][0][z - 1]->isEnabled() || tchunk->blocks[x - 1][0][z - 1]->isCovered() && // Front
											tchunk->blocks[x - 1][0][z + 1]->isEnabled() || tchunk->blocks[x - 1][0][z + 1]->isCovered() && // Back
											tchunk->blocks[x - 1][1][z]    ->isEnabled() || tchunk->blocks[x - 1][1][z]    ->isCovered()) { // Top
											tchunk->blocks[x - 1][0][z]->disable();
										}
										if (x == 1) {
											if ((lchunk->blocks[CHUNK_SIZE_X - 1][CHUNK_SIZE_Y - 1][z]->isEnabled() || lchunk->blocks[CHUNK_SIZE_X - 1][CHUNK_SIZE_Y - 1][z]->isCovered()) && // To Check
												(lchunk->tchunk->blocks[CHUNK_SIZE_X - 1][0][z]->isEnabled() || lchunk->tchunk->blocks[CHUNK_SIZE_X - 1][0][z]->isCovered()) && // Top
												(lchunk->blocks[CHUNK_SIZE_X - 2][CHUNK_SIZE_Y - 1][z]->isEnabled() || lchunk->blocks[CHUNK_SIZE_X - 2][CHUNK_SIZE_Y - 1][z]->isCovered()) && // Left
												(lchunk->blocks[CHUNK_SIZE_X - 1][CHUNK_SIZE_Y - 2][z]->isEnabled() || lchunk->blocks[CHUNK_SIZE_X - 1][CHUNK_SIZE_Y - 2][z]->isCovered()) && // Down
												(lchunk->blocks[CHUNK_SIZE_X - 1][CHUNK_SIZE_Y - 1][z - 1]->isEnabled() || lchunk->blocks[CHUNK_SIZE_X - 1][CHUNK_SIZE_Y - 1][z - 1]->isCovered()) && // Front
												(lchunk->blocks[CHUNK_SIZE_X - 1][CHUNK_SIZE_Y - 1][z + 1]->isEnabled() || lchunk->blocks[CHUNK_SIZE_X - 1][CHUNK_SIZE_Y - 1][z + 1]->isCovered())) { // Back
												lchunk->blocks[CHUNK_SIZE_X - 1][CHUNK_SIZE_Y - 1][z]->disable();
											}
										}
									}
								}
							}
						}

						if (bchunk != nullptr) {
							if (x > 1 && z == 0 && y < CHUNK_SIZE_Y - 1 && y > 0) {
								if ((blocks[x - 1][y][z]    ->isEnabled() || blocks[x - 1][y][z]    ->isCovered()) && // Mid
									(blocks[x - 1][y - 1][z]->isEnabled() || blocks[x - 1][y - 1][z]->isCovered()) && // Down
									(blocks[x - 1][y + 1][z]->isEnabled() || blocks[x - 1][y + 1][z]->isCovered()) && // Top
									(blocks[x - 2][y][z]    ->isEnabled() || blocks[x - 2][y][z]    ->isCovered()) && // Left
									(blocks[x][y][z]        ->isEnabled() || blocks[x][y][z]        ->isCovered()) && // Right
									(blocks[x - 1][y][z + 1]->isEnabled() || blocks[x - 1][y][z + 1]->isCovered())) { // Front
									if (bchunk->blocks[x - 1][y][0]->isEnabled() || bchunk->blocks[x - 1][y][0]->isCovered()) {
										blocks[x - 1][y][z]->disable();
										blocks[x - 1][y][z]->isCovered(GL_TRUE);
										if (bchunk->blocks[x - 1][y][CHUNK_SIZE_Z - 1]    ->isEnabled() && // To Check
											bchunk->blocks[x - 2][y][CHUNK_SIZE_Z - 1]    ->isEnabled() || bchunk->blocks[x - 2][y][CHUNK_SIZE_Z - 1]    ->isCovered() && // Left
											bchunk->blocks[x][y][CHUNK_SIZE_Z - 1]        ->isEnabled() || bchunk->blocks[x][y][CHUNK_SIZE_Z - 1]        ->isCovered() && // Right
											bchunk->blocks[x - 1][y + 1][CHUNK_SIZE_Z - 1]->isEnabled() || bchunk->blocks[x - 1][y + 1][CHUNK_SIZE_Z - 1]->isCovered() && // Top
											bchunk->blocks[x - 1][y - 1][CHUNK_SIZE_Z - 1]->isEnabled() || bchunk->blocks[x - 1][y - 1][CHUNK_SIZE_Z - 1]->isCovered() && // Down
											bchunk->blocks[x - 1][y][CHUNK_SIZE_Z - 2]    ->isEnabled() || bchunk->blocks[x - 1][y][CHUNK_SIZE_Z - 2]    ->isCovered()) { // Back
											bchunk->blocks[x - 1][y][CHUNK_SIZE_Z - 1]->disable();
										}
									}
								}
							}
						}

						if (isEnabled && !isCovered) blocks[x][y][z]->buildBlock(vec3(x, y, z));
#else
						blocks[x][y][z]->buildBlock(vec3(x, y, z));
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

		Chunk::~Chunk() {
			for (size_t x = 0; x < CHUNK_SIZE_X; x++) {
				for (size_t y = 0; y < CHUNK_SIZE_Y; y++) {
					for (size_t z = 0; z < CHUNK_SIZE_Z; z++) {
						delete[] blocks[x][y][z];
					}
					delete[] blocks[x][y];
				}
				delete[] blocks[x];
			}
			delete[] blocks;
			delete renderer;
			DEBUG_F("Deleted Chunk [%llu]\n", chunkID);
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

		void Chunk::draw(mat4 projection, mat4 view, RenderMode renderMode) {
			mvp = projection * view * model;
			// Setup rendering
			renderer->activateShader();
			renderer->start();
			// Set shadervariables
			renderer->getActiveShader()->setUniformMatrix4("MVP", mvp);
			renderer->getActiveShader()->setUniformInteger("renderType", mode == RenderMode::SOLID ? 0 : 1);

			// Submit Blocks
			for (size_t x = 0; x < CHUNK_SIZE_X; x++) {
				for (size_t y = 0; y < CHUNK_SIZE_Y; y++) {
					for (size_t z = 0; z < CHUNK_SIZE_Z; z++) {
						if (blocks[x][y][z]->isEnabled()) {
							if (blocks[x][y][z]->isEnabled()) {
								blocks[x][y][z]->submit(renderer);
							}
						}
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