#include "Chunk.hpp"

namespace Core {
	namespace Terrain {
		GLuint64 Chunk::chunkIDs = 0;
		Chunk::Chunk(ivec3 position, Chunk* lchunk, Chunk* tchunk, Chunk* fchunk, vec4 blendColor)
			: lchunk(lchunk), tchunk(tchunk), fchunk(fchunk), blendColor(blendColor) {
			chunkID = chunkIDs++;
			setRenderMode(RenderMode::WIRED);

			model[3].x = position.x;
			model[3].y = position.y;
			model[3].z = position.z;

			// Define texturemap
			texture.load2D("Textures/texturemap64.png");
			texture.setCubeBoxParam();
			texture.defineTextureInfo(vec2(8, 8), vec2(64, 64));

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

						if (x == 0 || y == 0 || z == 0 || x == ex || y == ey || z == ez) {
							isEnabled = GL_TRUE;
						} else if ((blocks[z][y][x - 1]->isEnabled() && blocks[z][y - 1][x]->isEnabled() && blocks[z - 1][y][x]->isEnabled()) ||
							(blocks[z][y][x - 1]->isCovered() && blocks[z][y - 1][x]->isCovered() && blocks[z - 1][y][x]->isCovered()) ||
							(blocks[z][y][x - 1]->isEnabled() && blocks[z][y - 1][x]->isCovered() && blocks[z - 1][y][x]->isCovered()) ||
							(blocks[z][y][x - 1]->isCovered() && blocks[z][y - 1][x]->isEnabled() && blocks[z - 1][y][x]->isCovered()) ||
							(blocks[z][y][x - 1]->isCovered() && blocks[z][y - 1][x]->isCovered() && blocks[z - 1][y][x]->isEnabled()) ||
							(blocks[z][y][x - 1]->isEnabled() && blocks[z][y - 1][x]->isEnabled() && blocks[z - 1][y][x]->isCovered()) ||
							(blocks[z][y][x - 1]->isEnabled() && blocks[z][y - 1][x]->isCovered() && blocks[z - 1][y][x]->isEnabled()) ||
							(blocks[z][y][x - 1]->isCovered() && blocks[z][y - 1][x]->isEnabled() && blocks[z - 1][y][x]->isEnabled())) {
							isEnabled = GL_FALSE;
							isCovered = GL_TRUE;
						} else {
							isEnabled = GL_TRUE;
						}

						blocks[z][y][x] =
							new Block(
								ivec3(BLOCKSIZE * x, BLOCKSIZE * -y, BLOCKSIZE * -z),
								btype, texture.getTextureOffset(tex), texture.getTexturePercentage(), mode, isEnabled);

						if (!isEnabled && !isCovered && !(x == 0 || y == 0 || z == 0)) {
							if (blocks[z][y][x - 1]->isCovered()) blocks[z][y][x - 1]->enable();
							if (blocks[z][y - 1][x]->isCovered()) blocks[z][y - 1][x]->enable();
							if (blocks[z - 1][y][x]->isCovered()) blocks[z - 1][y][x]->enable();
							blocks[z][y][x - 1]->isCovered(GL_FALSE);
							blocks[z][y - 1][x]->isCovered(GL_FALSE);
							blocks[z - 1][y][x]->isCovered(GL_FALSE);
						}

						blocks[z][y][x]->isCovered(isCovered);

						if (lchunk != nullptr && (tchunk != nullptr || y != 0) && (fchunk != nullptr || z != 1)) {
							if (x == 0 && z > 0 && y != ey) {
								if (y == 0 ? tchunk->blocks[z - 1][ey][0]->check() : blocks[z - 1][y - 1][0]->check() &&// Top
									blocks[z - 1][y + 1][0]->check() && blocks[z][y][0]->check() && // Down / Back
									z == 1 ? fchunk->blocks[ez][y][0]->check() : blocks[z - 2][y][0]->check() && // Front
									lchunk->blocks[z - 1][y][ex]->check() && blocks[z - 1][y][1]->check()) {// Left / Right
									blocks[z - 1][y][0]->isCovered(GL_TRUE);
									if (y == 0 ? lchunk->tchunk->blocks[z - 1][ey][ex]->check() : lchunk->blocks[z - 1][y - 1][ex]->check() && // Top
										lchunk->blocks[z - 1][y + 1][ex]->check() && lchunk->blocks[z][y][ex]->check() && // Down / Back
										z == 1 ? lchunk->fchunk->blocks[ez][y][ex]->check() : lchunk->blocks[z - 2][y][ex]->check() && // Front
										lchunk->blocks[z - 1][y][ex - 1]->check()) {// Left
										lchunk->blocks[z - 1][y][ex]->isCovered(GL_TRUE);
									}
									if (y == 0) {
										if (tchunk->lchunk != nullptr) {
											if (tchunk->lchunk->blocks[z - 1][ey - 1][ex]->check() && lchunk->blocks[z - 1][0][ex]->check() && // Top / Down
												z == 1 ? tchunk->lchunk->fchunk->blocks[ez][ey][ex]->check() : tchunk->lchunk->blocks[z - 2][ey][ex]->check() && // Front
												tchunk->lchunk->blocks[z][ey][ex]->check() && tchunk->lchunk->blocks[z - 1][ey][ex - 1]->check() && // Back / Left
												tchunk->blocks[z - 1][ey][0]->check()) { // Right
												tchunk->lchunk->blocks[z - 1][ey][ex]->isCovered(GL_TRUE);
											}
										}
									}
									if (z == 1) {
										if (lchunk->fchunk != nullptr) {
											if (y == 0 ? lchunk->fchunk->tchunk->blocks[ez][ey][ex]->check() : lchunk->fchunk->blocks[ez][y - 1][ex]->check() && // Top
												lchunk->fchunk->blocks[ez][y + 1][ex]->check() && lchunk->fchunk->blocks[ez][y][ex - 1]->check() && // Down / Left
												fchunk->blocks[ez][y][0]->check() && lchunk->blocks[0][y][ex]->check() && // Right / Back
												lchunk->fchunk->blocks[ez - 1][y][ex]->check()) { // Front
												lchunk->fchunk->blocks[ez][y][ex]->isCovered(GL_TRUE);
											}
										}
									}
								}
							}
						}

						if (tchunk != nullptr && (lchunk != nullptr || x != 0) && (fchunk != nullptr || z != 1)) {
							if (y == 0 && z > 0 && x != ex) {
								if (tchunk->blocks[z - 1][ey][x]->check() && blocks[z - 1][1][x]->check() && // Top / Down
									x == 0 ? lchunk->blocks[z - 1][0][ex]->check() : blocks[z - 1][0][x - 1]->check() && // Left
									blocks[z - 1][0][x + 1]->check() && blocks[z][0][x]->check() && // Right / Back
									z == 1 ? fchunk->blocks[ez][0][x]->check() : blocks[z - 2][0][x]->check()) { // Front
									blocks[z - 1][0][x]->isCovered(GL_TRUE);
									if (tchunk->blocks[z - 1][ey - 1][x]->check() && // Top
										x == 0 ? tchunk->lchunk->blocks[z - 1][ey][ex]->check() : tchunk->blocks[z - 1][ey][x - 1]->check() && // Left
										tchunk->blocks[z - 1][ey][x + 1]->check() && tchunk->blocks[z][ey][x]->check() && // Right / Back
										z == 1 ? tchunk->fchunk->blocks[ez][ey][x]->check() : tchunk->blocks[z - 2][ey][x]->check()) { // Front
										tchunk->blocks[z - 1][ey][x]->isCovered(GL_TRUE);
									}
									if (z == 1) {
										if (fchunk->tchunk != nullptr) {
											if (fchunk->tchunk->blocks[ez][ey - 1][x]->check() && fchunk->blocks[ez][0][x]->check() && // Top / Down
												x == 0 ? fchunk->tchunk->lchunk->blocks[ez][ey][ex]->check() : fchunk->tchunk->blocks[ez][ey][x - 1]->check() && // Left
												fchunk->tchunk->blocks[ez][ey][x + 1]->check() && tchunk->blocks[0][ey][x] && // Right / Back
												fchunk->tchunk->blocks[ez - 1][ey][x]->check()) { // Front
												fchunk->tchunk->blocks[ez][ey][x]->isCovered(GL_TRUE);
											}
										}
									}
								}
							}
						}

						if (fchunk != nullptr && (lchunk != nullptr || x != 0) && (tchunk != nullptr || y != 0)) {
							if (z == 1 && y != ey && x != ex) {
								if (y == 0 ? tchunk->blocks[0][ey][x]->check() : blocks[0][y - 1][x]->check() && // Top
									blocks[0][y + 1][x]->check() && blocks[0][y][x + 1]->check() && // Down / Right
									x == 0 ? lchunk->blocks[0][y][ex]->check() : blocks[0][y][x - 1]->check() && // Left
									fchunk->blocks[ez][y][x]->check() && blocks[1][y][x]->check()) { // Front / Back
									blocks[0][y][x]->isCovered(GL_TRUE);
									if (y == 0 ? fchunk->tchunk->blocks[ez][ey][x]->check() : fchunk->blocks[ez][y - 1][x]->check() && // Top
										x == 0 ? fchunk->lchunk->blocks[ez][y][ex]->check() : fchunk->blocks[ez][y][x - 1]->check() && // Left
										fchunk->blocks[ez][y + 1][x]->check() && fchunk->blocks[ez][y][x + 1]->check() && // Down / Right
										fchunk->blocks[ez - 1][y][x]->check()) { // Front
										fchunk->blocks[ez][y][x]->isCovered(GL_TRUE);
									}
								}
							}
						}

						if (x == 0 && y == 0 && z == 0 && fchunk != nullptr && lchunk != nullptr && tchunk != nullptr) {
							if (lchunk->tchunk->fchunk->blocks[ez][ey - 1][ex]->check() && lchunk->fchunk->blocks[ez][0][ex]->check() && // Top / Down
								lchunk->tchunk->fchunk->blocks[ez][ey][ex - 1]->check() && fchunk->tchunk->blocks[ez][ey][0]->check() && // Left / Right
								lchunk->tchunk->fchunk->blocks[ez - 1][ey][ex]->check() && tchunk->lchunk->blocks[0][ey][ex]->check()){ // Front / Back 
								lchunk->tchunk->fchunk->blocks[ez][ey][ex]->isCovered(GL_TRUE);
							}
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

		Chunk::~Chunk() {
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