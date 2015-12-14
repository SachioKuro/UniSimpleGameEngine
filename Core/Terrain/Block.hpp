#pragma once

#include "../Graphics/Shader.hpp"
#include "../Utils/GL.hpp"

namespace Core {
	namespace Terrain {
		using namespace glm;
		using namespace Graphics;
		/*
			Types of Blocks like sand, stone ...
		*/
		enum class BlockType
		{
			None,
			Water,
			Stone,
			Grass,
			Sand
		};

		/*
			Presentation of an Block in our world
		*/
		class Block {
		private:
			// Position in our world
			vec3 position;
			BlockType type;
			// Should the block be rendered
			GLboolean enabled;
		public:
			Shader* shader;
			Block();
			Block(vec3 position, BlockType type, GLboolean enabled);
			~Block();
			void enable();
			void disable();
			void transformTo(BlockType type);
			vec3 getPosition() const { return position; }
			inline GLboolean isEnabled() const { return enabled; };
			inline BlockType getBlockType() const { return type; };
			void draw(mat4 mvp) const;
		};
	}
}