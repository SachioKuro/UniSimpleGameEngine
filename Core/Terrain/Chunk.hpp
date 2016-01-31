#pragma once

#include "Block.hpp"
#include "../Graphics/Shader.hpp"
#include "../Graphics/Renderer.hpp"
#include "../Graphics/Camera.hpp"
#include "../Graphics/BlockContext.hpp"
#include "../Utils/Output.hpp"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 28
#define CHUNK_SIZE_Z 16
#define BSIZE 1
#define WATERLEVEL 9

namespace Core {
	namespace Terrain {
		/* Type of a collection of Blocks */
		enum class TerrainType { LAND, WATER };
		/* A chunk in our world */
		class Chunk {
		private:
			static GLuint64 chunkIDs;
			GLuint64 chunkID;
			Block**** blocks;
			Chunk *lchunk, *tchunk, *fchunk;
			Graphics::Renderer* renderer;
			std::vector<std::vector<GLint>> heightmap, blockmap;
			GLboolean active = GL_FALSE;
			glm::mat4 model = glm::mat4(1);
			Graphics::BlockContext* context;
			glm::vec3 center, position;
			GLfloat boundingRadius;
			std::vector<Block*> waterBlocks;
		public:
			Chunk(Graphics::Renderer* renderer, glm::ivec3 position, std::vector<std::vector<GLint>> heightmap,
				std::vector<std::vector<GLint>> blockmap, Chunk* lchunk, Chunk* tchunk, Chunk* fchunk, 
				Graphics::BlockContext* context, glm::vec4 blendColor = glm::vec4(0));
			~Chunk();

			GLboolean isActive() const { return active; }
			void isActive(GLboolean active) { this->active = active; }

			GLuint load(GLuint id);
			void unload(GLuint id);

			glm::vec3& getCenter() { return center; }
			glm::vec3& getPosition() { return position; }
			Block**** getBlocks() { return blocks; }

			/* Set neighbor */
			void setFrontChunk(Chunk* fchunk) { this->fchunk = fchunk; }
			void setLeftChunk(Chunk* lchunk) { this->lchunk = lchunk; }

			/* Draws the chunk */
			void draw(glm::mat4 projection, glm::mat4 view, glm::vec4 clippingPlane, GLint highOffset, GLint lowerOffset, 
				Graphics::Camera* camera, TerrainType type);
		};
	}
}
