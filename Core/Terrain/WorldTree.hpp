#pragma once
#pragma warning (disable:4005)

#include "../Utils/GL.hpp"
#include "Chunk.hpp"
#include "../Utils/PerlinNoise.hpp"
#include "../Graphics/BlockContext.hpp"
#include "../Graphics/Camera.hpp"

#define WORLDSIZE			11
#define WORLD_HALFSIZE		6
#define NOISE_WIDTH			1000000
#define NOISE_HEIGHT		1000000
#define NOISE_WIDTH_MID		500000
#define NOISE_HEIGHT_MID 	500000

namespace Core {
	namespace Terrain {
		/* Handles Worldloading */
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
			/* Loads the Chunks if needed */
			void checkAndLoad();
			Chunk* getCurrentChunk() { return currentChunk; }
			Graphics::BlockContext* getContext() { return &blockContext; }
			Graphics::Renderer* getRenderer() { return renderer; }
		};
	}
}