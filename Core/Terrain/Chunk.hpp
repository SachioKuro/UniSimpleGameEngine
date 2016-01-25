#pragma once

#include "Block.hpp"
#include "../Graphics/Shader.hpp"
#include "../Graphics/Renderer.hpp"
#include "../Graphics/Texture.hpp"
#include "../Graphics/Camera.hpp"
#include "../Graphics/BlockContext.hpp"
#include "../Utils/Output.hpp"

#define CHUNK_SIZE_X 10
#define CHUNK_SIZE_Y 35
#define CHUNK_SIZE_Z 10
#define BSIZE 1

namespace Core {
	namespace Terrain {
		using namespace Graphics;
		using namespace std;

		enum class TerrainType { LAND, WATER };

		/* A chunk in our world */
		class Chunk {
		private:
			static GLuint64 chunkIDs;
			GLuint64 chunkID;
			Block**** blocks;
			vector<Block*> tmpBlocksContainer;
			Chunk *lchunk, *tchunk, *fchunk;
			Renderer* renderer;
			Texture* texture;
			vector<vector<double>> heightmap, blockmap;
			GLboolean active = GL_FALSE;
			RenderMode mode = RenderMode::SOLID;
			GLuint vertexCount = 36;
			vec4 blendColor;
			mat4 model = mat4(1), mvp, pv;
			BlockContext* context;
			vec3 center;
			vec2 planePosition;
			GLfloat boundingRadius;
		public:
			Chunk(ivec3 position, vector<vector<double>> heightmap, vector<vector<double>> blockmap, Chunk* lchunk, Chunk* tchunk, Chunk* fchunk, BlockContext* context, vec4 blendColor = vec4(0));
			~Chunk();

			RenderMode getRenderMode() const { return mode; }

			GLboolean isActive() const { return active; }
			void isActive(GLboolean active) { this->active = active; }

			GLuint load(GLuint id);
			void unload(GLuint id);

			void setBlendColor(vec4 color) { blendColor = color; }
			vec3& getCenter() { return center; }

			Block**** getBlocks() { return blocks; }

			void setFrontChunk(Chunk* fchunk) { this->fchunk = fchunk; }
			void setLeftChunk(Chunk* lchunk) { this->lchunk = lchunk; }

			vector<Block*>& getTmpBlocks() { return tmpBlocksContainer; }

			/* Draws the chunk */
			void draw(mat4 projection, mat4 view, RenderMode renderMode, Camera* camera);

			int getHighestBlock(int x, int z);
		};
	}
}