#include "Block.hpp"

namespace Core {
	namespace Terrain {
		GLuint timer = 0;
		Block::Block(ivec3 position, BlockType type, vec2 textureOffset, vec2 textureSize, RenderMode mode, GLboolean enabled)
			: type(type), enabled(enabled), Drawable(mode, textureOffset, textureSize, 36)
		{
			//if(enabled) buildBlock(position);
		}

		Block::~Block() {
		}

		void Block::buildBlock(ivec3 position) {
			switch (mode) {
			case RenderMode::SOLID:
				buildBlockSolid(position);
				break;
			case RenderMode::WIRED:
				buildBlockWired(position);
				break;
			}
		}

		void Block::buildBlockSolid(ivec3 position) {
			ivec3* mesh = new ivec3[36];
			vec2* uvs = new vec2[6];
			ivec3* normals = new ivec3[6];

			/* Face Front */
			*(mesh++) = ivec3(position.x, position.y, position.z - 1);
			*(mesh++) = ivec3(position.x + 1, position.y - 1, position.z - 1);
			*(mesh++) = ivec3(position.x, position.y - 1, position.z - 1);
			*(mesh++) = ivec3(position.x, position.y, position.z - 1);
			*(mesh++) = ivec3(position.x + 1, position.y, position.z - 1);
			*(mesh++) = ivec3(position.x + 1, position.y - 1, position.z - 1);
			/* Face Right */
			*(mesh++) = ivec3(position.x + 1, position.y, position.z - 1);
			*(mesh++) = ivec3(position.x + 1, position.y - 1, position.z);
			*(mesh++) = ivec3(position.x + 1, position.y - 1, position.z - 1);
			*(mesh++) = ivec3(position.x + 1, position.y, position.z - 1);
			*(mesh++) = ivec3(position.x + 1, position.y, position.z);
			*(mesh++) = ivec3(position.x + 1, position.y - 1, position.z);
			/* Face Back */
			*(mesh++) = ivec3(position.x + 1, position.y, position.z);
			*(mesh++) = ivec3(position.x, position.y - 1, position.z);
			*(mesh++) = ivec3(position.x + 1, position.y - 1, position.z);
			*(mesh++) = ivec3(position.x + 1, position.y, position.z);
			*(mesh++) = ivec3(position.x, position.y, position.z);
			*(mesh++) = ivec3(position.x, position.y - 1, position.z);
			/* Face Left */
			*(mesh++) = ivec3(position.x, position.y, position.z);
			*(mesh++) = ivec3(position.x, position.y - 1, position.z - 1);
			*(mesh++) = ivec3(position.x, position.y - 1, position.z);
			*(mesh++) = ivec3(position.x, position.y, position.z);
			*(mesh++) = ivec3(position.x, position.y, position.z - 1);
			*(mesh++) = ivec3(position.x, position.y - 1, position.z - 1);
			/* Face Lower */
			*(mesh++) = ivec3(position.x, position.y, position.z);
			*(mesh++) = ivec3(position.x + 1, position.y, position.z - 1);
			*(mesh++) = ivec3(position.x, position.y, position.z - 1);
			*(mesh++) = ivec3(position.x, position.y, position.z);
			*(mesh++) = ivec3(position.x + 1, position.y, position.z);
			*(mesh++) = ivec3(position.x + 1, position.y, position.z - 1);
			/* Face Upper */
			*(mesh++) = ivec3(position.x + 1, position.y - 1, position.z);
			*(mesh++) = ivec3(position.x, position.y - 1, position.z - 1);
			*(mesh++) = ivec3(position.x + 1, position.y - 1, position.z - 1);
			*(mesh++) = ivec3(position.x + 1, position.y - 1, position.z);
			*(mesh++) = ivec3(position.x, position.y - 1, position.z);
			*(mesh++) = ivec3(position.x, position.y - 1, position.z - 1);

			*(uvs++) = textureOffset;
			*(uvs++) = textureOffset + textureSize;
			*(uvs++) = vec2(textureOffset.s, textureOffset.t + textureSize.t);
			*(uvs++) = textureOffset;
			*(uvs++) = vec2(textureOffset.s + textureSize.s, textureOffset.t);
			*(uvs++) = textureOffset + textureSize;

			*(normals++) = ivec3(0, 0, 1);
			*(normals++) = ivec3(1, 0, 0);
			*(normals++) = ivec3(0, 0, -1);
			*(normals++) = ivec3(-1, 0, 0);
			*(normals++) = ivec3(0, -1, 0);
			*(normals++) = ivec3(0, 1, 0);

			// Resets pointer
			mesh -= 36; uvs -= 6; normals -= 6;

			// Set vertices
			for (GLsizei i = 0, j = 0, n = 0; i < 36; i++, n++) {
				setPosition(mesh[i], i);
				setNormal(normals[j], i);
				setUV(uvs[i % 6], i);
				setblendColor(vec4(0, 0, 0, 0), i);
				if (n >= 5) {
					j++;
					n = -1;
				}
			}

			delete[] mesh;
			delete[] uvs;
			delete[] normals;
			nrOfVertices = 36;
		}

		void Block::buildBlockWired(ivec3 position) {
			ivec3* mesh = new ivec3[23];

			// Sets the end of line with Alpha = 0
			*(mesh++) = ivec3(position.x, position.y - 1, position.z);
			/* Face Front */
			*(mesh++) = ivec3(position.x, position.y - 1, position.z);
			*(mesh++) = ivec3(position.x, position.y, position.z);
			*(mesh++) = ivec3(position.x + 1, position.y, position.z);
			*(mesh++) = ivec3(position.x, position.y - 1, position.z);
			*(mesh++) = ivec3(position.x + 1, position.y - 1, position.z);
			*(mesh++) = ivec3(position.x + 1, position.y, position.z);
			/* Face Right */
			*(mesh++) = ivec3(position.x + 1, position.y, position.z - 1);
			*(mesh++) = ivec3(position.x + 1, position.y - 1, position.z);
			*(mesh++) = ivec3(position.x + 1, position.y - 1, position.z - 1);
			*(mesh++) = ivec3(position.x + 1, position.y, position.z - 1);
			/* Face Back */
			*(mesh++) = ivec3(position.x, position.y, position.z - 1);
			*(mesh++) = ivec3(position.x + 1, position.y - 1, position.z - 1);
			*(mesh++) = ivec3(position.x, position.y - 1, position.z - 1);
			*(mesh++) = ivec3(position.x, position.y, position.z - 1);
			/* Face Left */
			*(mesh++) = ivec3(position.x, position.y, position.z);
			*(mesh++) = ivec3(position.x, position.y - 1, position.z - 1);
			*(mesh++) = ivec3(position.x, position.y - 1, position.z);
			*(mesh++) = ivec3(position.x, position.y, position.z);
			/* Face Upper */
			*(mesh++) = ivec3(position.x + 1, position.y, position.z - 1);
			/*....*/
			*(mesh++) = ivec3(position.x + 1, position.y - 1, position.z - 1);
			/* Face Lower */
			*(mesh++) = ivec3(position.x, position.y - 1, position.z);
			// Sets the start of line with Alpha = 0
			*(mesh++) = ivec3(position.x, position.y - 1, position.z);

			// Resets Pointer
			mesh -= 23;

			// Set vertices
			for (GLsizei i = 0, j = 0, n = 0; i < 23; i++, n++) {
				setPosition(mesh[i], i);
				setNormal(ivec3(0), i);
				setUV(vec2(0), i);
				if (i == 0 || i == 22)
					setblendColor(vec4(0, 0, 0, 0), i);
				else
					setblendColor(vec4(0.8, 0.2, 0.0, 1), i);
			}

			delete[] mesh;
			nrOfVertices = 23;
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

		void Block::submit(Renderer* renderer) const {
			if (isEnabled()) renderer->submit((Drawable*)this);
		}
	}
}