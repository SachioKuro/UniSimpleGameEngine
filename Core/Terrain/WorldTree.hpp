#pragma once

#include "../Utils/GL.hpp"
#include "Chunk.hpp"
#include "../Utils/PerlinNoise.hpp"
#include "../Graphics/BlockContext.hpp"
#include "../Graphics/Camera.hpp"

#define WORLDSIZE			6
#define WORLD_HALFSIZE		3
#define NOISE_WIDTH			1000000
#define NOISE_HEIGHT		1000000
#define NOISE_WIDTH_MID		500000
#define NOISE_HEIGHT_MID 	500000

namespace Core {
	namespace Terrain {
		class WorldTree {
		private:
			Chunk*** chunks;
			Chunk* currentChunk = nullptr;
			Utils::PerlinNoise *noise, *bnoise;
			glm::uvec2 noisePos = glm::uvec2(NOISE_WIDTH_MID, NOISE_HEIGHT_MID);
			Graphics::Camera* camera;
			Graphics::BlockContext blockContext;
			GLfloat chunkSizeHalfX, chunkSizeHalfZ;
			Graphics::Renderer* renderer;
		public:
			WorldTree(Graphics::Camera* camera);
			~WorldTree();
			Chunk***& getChunks() { return chunks; }
			void checkAndLoad();
			Chunk* getCurrentChunk() { return currentChunk; }
			Graphics::BlockContext* getContext() { return &blockContext; }
			Graphics::Renderer* getRenderer() { return renderer; }
		};
	}
}