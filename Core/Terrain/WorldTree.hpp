#pragma once

#include "../Utils/GL.hpp"
#include "Chunk.hpp"
#include "../Utils/PerlinNoise.hpp"
#include "../Graphics/BlockContext.hpp"
#include "../Graphics/Camera.hpp"

#define WORLDSIZE			20
#define WORLD_HALFSIZE		10
#define NOISE_WIDTH			1000000
#define NOISE_HEIGHT		1000000
#define NOISE_WIDTH_MID		500000
#define NOISE_HEIGHT_MID 	500000

namespace Core {
	namespace Terrain {
		using namespace glm;
		using namespace std;
		using namespace Core::Utils;
		class WorldTree {
		private:
			Chunk*** chunks;
			Chunk* currentChunk = nullptr;
			Texture* texture;
			PerlinNoise *noise, *bnoise;
			uvec2 noisePos = uvec2(NOISE_WIDTH_MID, NOISE_HEIGHT_MID);
			Camera* camera;
			BlockContext blockContext;
			GLfloat chunkSizeHalfX, chunkSizeHalfZ;
			Renderer* renderer;
		public:
			WorldTree(Camera* camera);
			~WorldTree();
			Chunk***& getChunks() { return chunks; }
			void checkAndLoad();
			Chunk* getCurrentChunk() { return currentChunk; }
		};
	}
}