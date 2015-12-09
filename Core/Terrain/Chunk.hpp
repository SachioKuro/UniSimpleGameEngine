#pragma once

#include "Block.hpp"

#define CHUNK_SIZE_X 8
#define CHUNK_SIZE_Y 8
#define CHUNK_SIZE_Z 8
#define BLOCKSIZE 1

namespace Core {
	namespace Terrain {
		enum class RenderMode { SOLID, WIRED };
		class Chunk {
		private:
			RenderMode renderMode;
			GLuint64 chunkID;
			Block*** blocks;
			GLfloat* meshData = 0;
		public:
			Chunk();
			~Chunk();
			void buildMesh();
			GLfloat* getMeshData() const { return meshData; }
			RenderMode getRenderMode() const { return  renderMode; }
			// TODO: load existing Chunk
			// GLboolean loadChunk(GLuint64 chunkID);
		private:
			void buildBlockMesh(vec3& position, GLfloat*& meshPointer);
			void buildBlockMeshWired(vec3& position, GLfloat*& meshPointer);
		};
	}
}