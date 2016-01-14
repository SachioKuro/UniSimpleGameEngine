#pragma once

#include "../Utils/GL.hpp"
#include "Chunk.hpp"
#include "../Utils/PerlinNoise.hpp"
#include "../Graphics/BlockContext.hpp"
#include <vector>

#define WORLDSIZE 8

namespace Core {
	namespace Terrain {
		using namespace glm;
		using namespace std;
		using namespace Core::Utils;
		class WorldTree {
		private:
			vector<vector<Chunk*>> chunks;
			Texture* texture;
			PerlinNoise* noise;
			BlockContext blockContext;
		public:
			WorldTree();
			~WorldTree();
			vector<vector<Chunk*>> getChunks() { return chunks; }
		};
	}
}