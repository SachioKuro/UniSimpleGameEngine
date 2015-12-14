#include "Block.hpp"

namespace Core {
	namespace Terrain {
		Block::Block(vec3 position, BlockType type, GLboolean enabled) 
			: position(position), type(type), enabled(enabled) 
		{
			shader = Shader::Block;
		}

		Block::Block() : Block::Block(vec3(0.0f), (BlockType)0, GL_TRUE) {}

		Block::~Block() {
		}

		void Block::enable() {
			this->enabled = GL_TRUE;
		}

		void Block::disable() {
			this->enabled = GL_FALSE;
		}

		void Block::transformTo(BlockType type) {
			this->type = type;
		}

		void Block::draw(GLubyte renderType, mat4 mvp, GLint index) const {
			shader->activate();
			shader->setUniformMatrix4("MVP", mvp);
			glDrawArrays(renderType, index, 36);
			shader->deactivate();
		}
	}
}