#include "Block.hpp"

namespace Core {
	namespace Terrain {
		GLuint timer = 0;
		Block::Block(vec3 position, BlockType type, vec2 textureOffset, vec2 textureSize, RenderMode mode, GLboolean enabled)
			: type(type), enabled(enabled), Drawable(mode, textureOffset, textureSize)
		{
			buildBlock(position);
		}

		Block::~Block() {
		}

		void Block::buildBlock(vec3 position) {
			switch (mode) {
			case RenderMode::SOLID:
				buildBlockSolid(position);
				break;
			case RenderMode::WIRED:
				buildBlockWired(position);
				break;
			}
		}

		void Block::buildBlockSolid(vec3 position) {
			vec3* mesh = new vec3[36];
			vec2* uvs = new vec2[6];
			vec3* normals = new vec3[6];

			/* Face Front */
			*(mesh++) = vec3(position.x, position.y, position.z);
			*(mesh++) = vec3(position.x + 1, position.y + 1, position.z);
			*(mesh++) = vec3(position.x, position.y + 1, position.z);
			*(mesh++) = vec3(position.x, position.y, position.z);
			*(mesh++) = vec3(position.x + 1, position.y, position.z);
			*(mesh++) = vec3(position.x + 1, position.y + 1, position.z);
			/* Face Right */
			*(mesh++) = vec3(position.x + 1, position.y, position.z);
			*(mesh++) = vec3(position.x + 1, position.y + 1, position.z - 1);
			*(mesh++) = vec3(position.x + 1, position.y + 1, position.z);
			*(mesh++) = vec3(position.x + 1, position.y, position.z);
			*(mesh++) = vec3(position.x + 1, position.y, position.z - 1);
			*(mesh++) = vec3(position.x + 1, position.y + 1, position.z - 1);
			/* Face Back */
			*(mesh++) = vec3(position.x + 1, position.y, position.z - 1);
			*(mesh++) = vec3(position.x, position.y + 1, position.z - 1);
			*(mesh++) = vec3(position.x + 1, position.y + 1, position.z - 1);
			*(mesh++) = vec3(position.x + 1, position.y, position.z - 1);
			*(mesh++) = vec3(position.x, position.y, position.z - 1);
			*(mesh++) = vec3(position.x, position.y + 1, position.z - 1);
			/* Face Left */
			*(mesh++) = vec3(position.x, position.y, position.z - 1);
			*(mesh++) = vec3(position.x, position.y + 1, position.z);
			*(mesh++) = vec3(position.x, position.y + 1, position.z - 1);
			*(mesh++) = vec3(position.x, position.y, position.z - 1);
			*(mesh++) = vec3(position.x, position.y, position.z);
			*(mesh++) = vec3(position.x, position.y + 1, position.z);
			/* Face Lower */
			*(mesh++) = vec3(position.x, position.y, position.z - 1);
			*(mesh++) = vec3(position.x + 1, position.y, position.z);
			*(mesh++) = vec3(position.x, position.y, position.z);
			*(mesh++) = vec3(position.x, position.y, position.z - 1);
			*(mesh++) = vec3(position.x + 1, position.y, position.z - 1);
			*(mesh++) = vec3(position.x + 1, position.y, position.z);
			/* Face Upper */
			*(mesh++) = vec3(position.x + 1, position.y + 1, position.z - 1);
			*(mesh++) = vec3(position.x, position.y + 1, position.z);
			*(mesh++) = vec3(position.x + 1, position.y + 1, position.z);
			*(mesh++) = vec3(position.x + 1, position.y + 1, position.z - 1);
			*(mesh++) = vec3(position.x, position.y + 1, position.z - 1);
			*(mesh++) = vec3(position.x, position.y + 1, position.z);

			*(uvs++) = textureOffset;
			*(uvs++) = textureOffset + textureSize;
			*(uvs++) = vec2(textureOffset.s, textureOffset.t + textureSize.t);
			*(uvs++) = textureOffset;
			*(uvs++) = vec2(textureOffset.s + textureSize.s, textureOffset.t);
			*(uvs++) = textureOffset + textureSize;

			*(normals++) = vec3(0, 0, 1);
			*(normals++) = vec3(1, 0, 0);
			*(normals++) = vec3(0, 0, -1);
			*(normals++) = vec3(-1, 0, 0);
			*(normals++) = vec3(0, -1, 0);
			*(normals++) = vec3(0, 1, 0);

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

		void Block::buildBlockWired(vec3 position) {
			vec3* mesh = new vec3[23];

			// Sets the end of line with Alpha = 0
			*(mesh++) = vec3(position.x, position.y, position.z);
			/* Face Front */
			*(mesh++) = vec3(position.x, position.y, position.z);
			*(mesh++) = vec3(position.x, position.y + 1, position.z);
			*(mesh++) = vec3(position.x + 1, position.y + 1, position.z);
			*(mesh++) = vec3(position.x, position.y, position.z);
			*(mesh++) = vec3(position.x + 1, position.y, position.z);
			*(mesh++) = vec3(position.x + 1, position.y + 1, position.z);
			/* Face Right */
			*(mesh++) = vec3(position.x + 1, position.y + 1, position.z - 1);
			*(mesh++) = vec3(position.x + 1, position.y, position.z);
			*(mesh++) = vec3(position.x + 1, position.y, position.z - 1);
			*(mesh++) = vec3(position.x + 1, position.y + 1, position.z - 1);
			/* Face Back */
			*(mesh++) = vec3(position.x, position.y + 1, position.z - 1);
			*(mesh++) = vec3(position.x + 1, position.y, position.z - 1);
			*(mesh++) = vec3(position.x, position.y, position.z - 1);
			*(mesh++) = vec3(position.x, position.y + 1, position.z - 1);
			/* Face Left */
			*(mesh++) = vec3(position.x, position.y + 1, position.z);
			*(mesh++) = vec3(position.x, position.y, position.z - 1);
			*(mesh++) = vec3(position.x, position.y, position.z);
			*(mesh++) = vec3(position.x, position.y + 1, position.z);
			/* Face Upper */
			*(mesh++) = vec3(position.x + 1, position.y + 1, position.z - 1);
			/*....*/
			*(mesh++) = vec3(position.x + 1, position.y, position.z - 1);
			/* Face Lower */
			*(mesh++) = vec3(position.x, position.y, position.z);
			// Sets the start of line with Alpha = 0
			*(mesh++) = vec3(position.x, position.y, position.z);

			// Resets Pointer
			mesh -= 23;

			// Set vertices
			for (GLsizei i = 0, j = 0, n = 0; i < 23; i++, n++) {
				setPosition(mesh[i], i);
				setNormal(vec3(0), i);
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
			renderer->submit((Drawable*)this);
		}
	}
}