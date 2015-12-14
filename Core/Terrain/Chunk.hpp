#pragma once

#include "Block.hpp"
#include "../Graphics/Shader.hpp"

#define CHUNK_SIZE_X 8
#define CHUNK_SIZE_Y 8
#define CHUNK_SIZE_Z 8
#define BLOCKSIZE 1

namespace Core {
	namespace Terrain {
		using namespace Graphics;
		enum class RenderMode { SOLID, WIRED };
		class Chunk {
		private:
			RenderMode renderMode;
			GLuint64 chunkID;
			Block*** blocks;
			GLfloat* meshData = 0;
			GLuint verticesCount;
			GLfloat* texData = 0;
			Shader* shader;
			GLuint vertexArrayID;
			GLuint vertexBuffer;
		public:
			Chunk();
			~Chunk();
			void buildMesh();
			GLfloat* getTexData() const { return texData; }
			GLfloat* getMeshData() const { return meshData; }
			RenderMode getRenderMode() const { return  renderMode; }
			void setRenderMode(RenderMode _renderMode) { renderMode = _renderMode; }
			void draw(mat4 mvp, RenderMode renderMode) const;
			void switchRenderMode() { 
				renderMode = renderMode == RenderMode::SOLID ? RenderMode::WIRED : RenderMode::SOLID; 
			}
			// TODO: load existing Chunk
			// GLboolean loadChunk(GLuint64 chunkID);
		private:
			void buildBlockMesh(vec3& position, GLfloat*& meshPointer, GLfloat*& texPointer);
			void buildBlockMeshWired(vec3& position, GLfloat*& meshPointer);
		};
	}
}