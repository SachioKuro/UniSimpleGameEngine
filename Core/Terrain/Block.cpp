#include "Block.hpp"

namespace Core {
	namespace Terrain {
		uint timer = 0;
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
			// Test: Disco-Mode
			//shader->setUniformVector3("BlendColor", glm::vec3((index + timer)  % 72 > 60 ? 0.5 : 0.1, (index + timer++) % 108 > 90 ? 0.5 : 0.1, 0.1f));
			// Alternative: glDrawElements mit einem Pointer
			glDrawArrays(renderType, index, 36);
			shader->deactivate();
			timer = timer > 2000 ? 0 : timer;
		}
	}
}