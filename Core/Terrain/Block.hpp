#pragma once

#include "../Utils/GL.hpp"
#include "../Graphics/Renderer.hpp"
#include "../Graphics/Drawable.hpp"

namespace Core {
	namespace Terrain {
		using namespace glm;
		using namespace Graphics;
		/*
			Types of Blocks like sand, stone ...
		*/
		enum class BlockType
		{
			NONE,
			WATER,
			STONE,
			GRASS,
			SAND
		};

		/*
			Presentation of an Block in our world
		*/
		class Block : public Drawable {
		protected:
			BlockType type;
			// Should the block be rendered
			GLboolean enabled = GL_TRUE, covered = GL_FALSE;
		public:
			Block(ivec3 position, BlockType type, vec2 textureOffset, vec2 textureSize, RenderMode mode, GLboolean enabled);
			~Block();

			/* Enable the Block */
			void enable();
			/* Disable the Block */
			void disable();
			/* Transform the Block */
			void transformTo(BlockType type);

			GLboolean isEnabled() const { return enabled; };
			GLboolean isCovered() const { return covered; };
			GLboolean check() const { return covered || enabled; };
			void isCovered(GLboolean isCovered) { if (isCovered) disable(); covered = isCovered; }
			BlockType getBlockType() const { return type; };

			/* Submit Block for rendering */
			void submit(Renderer* renderer) const;
			void buildBlock(ivec3 position);
		private:
			/* Build the mesh */
			void buildBlockSolid(ivec3 position);
			void buildBlockWired(vec3 position);
		};
	}
}