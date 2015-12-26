#pragma once

#include "Block.hpp"
#include "../Graphics/Shader.hpp"
#include "../Graphics/Renderer.hpp"
#include "../Graphics/Texture.hpp"
#include "../Utils/Output.hpp"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 8
#define CHUNK_SIZE_Z 8
#define BLOCKSIZE 1

namespace Core {
	namespace Terrain {
		using namespace Graphics;
		/* A chunk in our world */
		class Chunk {
		private:
			GLuint64 chunkID;
			Block**** blocks;
			Renderer* renderer;
			RenderMode mode = RenderMode::SOLID;
			Texture texture;
			GLuint vertexCount = 36;
		public:
			Chunk();
			~Chunk();

			void setRenderMode(RenderMode mode);
			RenderMode getRenderMode() const { return mode; }
			/* Switch between Rendermodes */
			void toggleRenderMode();

			/* Draws the chunk */
			void draw(mat4 mvp, RenderMode renderMode);
		};
	}
}