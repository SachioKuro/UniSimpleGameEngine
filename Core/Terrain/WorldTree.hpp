#pragma once

#include "../Utils/GL.hpp"
#include "Chunk.hpp"
#include <vector>

#define WORLDSIZE 5

namespace Core {
	namespace Terrain {
		using namespace glm;
		using namespace std;
		class WorldTree {
		private:
			vector<vector<vector<Chunk*>>> chunks;
			Texture* texture;
		public:
			WorldTree(Texture* texture);
			//~WorldTree();
			vector<vector<vector<Chunk*>>> getChunks() { return chunks; }
		private:
			void buildWorld(Chunk* current, ivec3 position, Chunk* lchunk, Chunk* tchunk, Chunk* fchunk, GLubyte depth);
		};
	}
}