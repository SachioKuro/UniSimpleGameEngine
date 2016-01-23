#include "Block.hpp"

// Todo: Fix memory

namespace Core {
	namespace Terrain {
		Block::Block(ivec3 position, BlockType type, TextureID textureOffset, RenderMode mode, GLboolean enabled)
			: type(type), enabled(enabled), Drawable(mode, position, textureOffset, texturePercentage, 36) {}

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

		void Block::submit(Renderer* renderer, BlockContext* context, vec2& range) const {
			if (isEnabled() && !isCovered()) renderer->submit((Drawable*)this, context, range);
		}
	}
}