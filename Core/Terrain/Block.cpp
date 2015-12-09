#include "Block.hpp"

namespace Core {
	namespace Terrain {
		Block::Block(vec3 position, BlockType type, GLboolean enabled) 
			: position(position), type(type), enabled(enabled) {
		}

		Block::Block() : Block::Block(vec3(0.0f), (BlockType)0, GL_TRUE) {}

		void Block::enable() {
			this->enabled = GL_TRUE;
		}

		void Block::disable() {
			this->enabled = GL_FALSE;
		}

		void Block::transformTo(BlockType type) {
			this->type = type;
		}
	}
}