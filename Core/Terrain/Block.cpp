#include "Block.hpp"

// Todo: Fix memory

namespace Core {
	namespace Terrain {
		Block::Block(glm::ivec3 position, BlockType type, Graphics::TextureID textureOffset, GLboolean enabled)
			: type(type), enabled(enabled), Drawable(position, textureOffset, texturePercentage, 36) {}

		Block::~Block() {}
		
		void Block::enable() {
			this->enabled = GL_TRUE;
		}

		void Block::disable() {
			this->enabled = GL_FALSE;
		}

		void Block::transformTo(BlockType type) {
			this->type = type;
		}

		void Block::submit(Graphics::Renderer* renderer, Graphics::BlockContext* context, glm::vec2& range) const {
			if (isEnabled() && !isCovered()) renderer->submit((Drawable*)this, context, range);
		}
	}
}