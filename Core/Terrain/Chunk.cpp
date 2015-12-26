#include "Chunk.hpp"

namespace Core {
	namespace Terrain {
		Chunk::Chunk() {
			setRenderMode(RenderMode::SOLID);

			// Define texturemap
			texture.load2D("Textures/texturemap64.png");
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

						if (x == 0 || y == 0 || z == 0) {
							isEnabled = GL_TRUE;
						} else if (x == CHUNK_SIZE_X - 1 || y == CHUNK_SIZE_Y - 1 || z == CHUNK_SIZE_Z - 1) {
							isEnabled = GL_TRUE;
						} else if (blocks[x][y][z - 1]->isEnabled() && blocks[x][y + 1][z]->isEnabled() && blocks[x - 1][y][z]->isEnabled()) {
							isEnabled = GL_FALSE;
							isCovered = GL_TRUE;
						} else if (blocks[x][y][z - 1]->isCovered() && blocks[x][y + 1][z]->isCovered() && blocks[x - 1][y][z]->isCovered()) {
							isEnabled = GL_FALSE;
							isCovered = GL_TRUE;
						} else if (blocks[x][y][z - 1]->isEnabled() && blocks[x][y + 1][z]->isCovered() && blocks[x - 1][y][z]->isCovered()) {
							isEnabled = GL_FALSE;
							isCovered = GL_TRUE;
						} else if (blocks[x][y][z - 1]->isCovered() && blocks[x][y + 1][z]->isEnabled() && blocks[x - 1][y][z]->isCovered()) {
							isEnabled = GL_FALSE;
							isCovered = GL_TRUE;
						} else if (blocks[x][y][z - 1]->isCovered() && blocks[x][y + 1][z]->isCovered() && blocks[x - 1][y][z]->isEnabled()) {
							isEnabled = GL_FALSE;
							isCovered = GL_TRUE;
						} else if (blocks[x][y][z - 1]->isEnabled() && blocks[x][y + 1][z]->isEnabled() && blocks[x - 1][y][z]->isCovered()) {
							isEnabled = GL_FALSE;
							isCovered = GL_TRUE;
						} else if (blocks[x][y][z - 1]->isEnabled() && blocks[x][y + 1][z]->isCovered() && blocks[x - 1][y][z]->isEnabled()) {
							isEnabled = GL_FALSE;
							isCovered = GL_TRUE;
						} else if (blocks[x][y][z - 1]->isCovered() && blocks[x][y + 1][z]->isEnabled() && blocks[x - 1][y][z]->isEnabled()) {
							isEnabled = GL_FALSE;
							isCovered = GL_TRUE;
						} else {
							isEnabled = GL_TRUE;
						}

						blocks[x][y][z] =
							new Block(
								vec3(BLOCKSIZE * x, BLOCKSIZE * y, BLOCKSIZE * z),
								btype, texture.getTextureOffset(tex), texture.getTexturePercentage(), mode, isEnabled);

						if ((x + y + z) & 1)
							blocks[x][y][z]->disable();

						if (!isEnabled && !isCovered && !(x == 0 || y == CHUNK_SIZE_Y - 1 || z == 0)) {
							if (blocks[x][y][z - 1]->isCovered()) blocks[x][y][z - 1]->enable();
							if (blocks[x][y + 1][z]->isCovered()) blocks[x][y + 1][z]->enable();
							if (blocks[x - 1][y][z]->isCovered()) blocks[x - 1][y][z]->enable();
							blocks[x][y][z - 1]->isCovered(GL_FALSE);
							blocks[x][y + 1][z]->isCovered(GL_FALSE);
							blocks[x - 1][y][z]->isCovered(GL_FALSE);
						}

						if (isEnabled && !isCovered) blocks[x][y][z]->buildBlock(vec3(x, y, z));

						blocks[x][y][z]->isCovered(isCovered);

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

		void Chunk::draw(mat4 mvp, RenderMode renderMode) {
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