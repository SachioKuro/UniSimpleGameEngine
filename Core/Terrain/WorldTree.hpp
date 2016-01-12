#pragma once

#include "../Utils/GL.hpp"
#include "Chunk.hpp"
#include "../Utils/PerlinNoise.hpp"
#include <vector>

#define WORLDSIZE 7

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
		public:
			WorldTree(Texture* texture);
			~WorldTree();
			vector<vector<Chunk*>> getChunks() { return chunks; }
		};
	}
}