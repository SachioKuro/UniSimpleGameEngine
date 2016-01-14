#pragma once

#include "Block.hpp"
#include "../Graphics/Shader.hpp"
#include "../Graphics/Renderer.hpp"
#include "../Graphics/Texture.hpp"
#include "../Graphics/Camera.hpp"
#include "../Graphics/BlockContext.hpp"
#include "../Utils/Output.hpp"

#define CHUNK_SIZE_X 20
#define CHUNK_SIZE_Y 15
#define CHUNK_SIZE_Z 20
#define BLOCKSIZE 1

namespace Core {
	namespace Terrain {
		using namespace Graphics;
		using namespace std;
		/* A chunk in our world */
		class Chunk {
		private:
			static GLuint64 chunkIDs;
			GLuint64 chunkID;
			Block**** blocks;
			Chunk *lchunk, *tchunk, *fchunk;
			Renderer* renderer;
			Texture* texture;
			vector<vector<double>> heightmap;
			GLboolean active = GL_FALSE;
			RenderMode mode = RenderMode::SOLID;
			GLuint vertexCount = 36;
			vec4 blendColor;
			mat4 model = mat4(1), mvp, pv;
			BlockContext* context;
			vec3 center;
			GLfloat boundingRadius;
		public:
			Chunk(ivec3 position, vector<vector<double>> heightmap, Chunk* lchunk, Chunk* tchunk, Chunk* fchunk, BlockContext* context, vec4 blendColor = vec4(0));
			~Chunk();

			void setRenderMode(RenderMode mode);
			RenderMode getRenderMode() const { return mode; }
			/* Switch between Rendermodes */
			void toggleRenderMode();

			GLboolean isActive() const { return active; }
			void isActive(GLboolean active) { this->active = active; }

			GLuint load(GLuint id);
			void unload(GLuint id);

			/* Draws the chunk */
			void draw(mat4 projection, mat4 view, RenderMode renderMode, Camera* camera);
		};
	}
}