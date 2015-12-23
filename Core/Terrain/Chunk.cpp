#include "Chunk.hpp"

namespace Core {
	namespace Terrain {
		Chunk::Chunk() {
			setRenderMode(RenderMode::SOLID);

			// Define texturemap
			texture.load2D("Textures/texturemap.png");
			texture.setCubeBoxParam();
			texture.defineTextureInfo(vec2(8, 8), vec2(256, 256));

			// Creates blocks
			TextureID tex; 
			vec2 texOffSet;
			blocks = new Block***[CHUNK_SIZE_X];
			for (size_t x = 0; x < CHUNK_SIZE_X; x++) {
				blocks[x] = new Block**[CHUNK_SIZE_Y];
				for (size_t y = 0; y < CHUNK_SIZE_Y; y++) {
					blocks[x][y] = new Block*[CHUNK_SIZE_Z];
					for (size_t z = 0; z < CHUNK_SIZE_Z; z++) {
						BlockType btype = (x + y + z) & 1 ? BlockType::GRASS : BlockType::STONE;

						switch (btype) {
							case BlockType::GRASS:	tex = TextureID::GRASS01; break;
							case BlockType::STONE:	tex = TextureID::STONE01; break;
							default:				tex = TextureID::NONE;
						}

						blocks[x][y][z] =
							new Block(
								vec3(BLOCKSIZE * x, BLOCKSIZE * y, BLOCKSIZE * z),
								btype, texture.getTextureOffset(tex), texture.getTexturePercentage(), mode, 
								(x+y+z) & 2 ? GL_TRUE : GL_FALSE);
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
			for (size_t x = 0; x < CHUNK_SIZE_X; x++)
				for (size_t y = 0; y < CHUNK_SIZE_Y; y++)
					for (size_t z = 0; z < CHUNK_SIZE_Z; z++)
						if (blocks[x][y][z]->isEnabled()) blocks[x][y][z]->submit(renderer);

			// Ready for render
			renderer->end();
			// Starts rendering
			renderer->draw();
			renderer->deactivateShader();
		}
	}
}