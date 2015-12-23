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
			GLboolean enabled;
		public:
			Block(vec3 position, BlockType type, vec2 textureOffset, vec2 textureSize, RenderMode mode, GLboolean enabled);
			~Block();

			/* Enable the Block */
			void enable();
			/* Disable the Block */
			void disable();
			/* Transform the Block */
			void transformTo(BlockType type);

			inline GLboolean isEnabled() const { return enabled; };
			inline BlockType getBlockType() const { return type; };

			/* Submit Block for rendering */
			void submit(Renderer* renderer) const;
		private:
			/* Build the mesh */
			void buildBlock(vec3 position);
			void buildBlockSolid(vec3 position);
			void buildBlockWired(vec3 position);
		};
	}
}