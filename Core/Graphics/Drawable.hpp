#pragma once

#include "../Utils/GL.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

namespace Core {
	namespace Graphics {
		using namespace glm;

		/* Type of rendering (Solid/Wired) */
		enum class RenderMode { SOLID, WIRED };

		/* Entity, which will be rendered */
		class Drawable {
		protected:
			GLsizei nrOfVertices;
			RenderMode mode = RenderMode::SOLID;
			GLint x, y, z;
			TextureID textureOffset;
			vec4 color;
			vec2 texturePercentage;
		public:
			Drawable(RenderMode mode, ivec3 position, TextureID textureOffset, vec2 texturePercentage, GLuint vertexAttrSize)
				: mode(mode), nrOfVertices(vertexAttrSize), textureOffset(textureOffset), texturePercentage(texturePercentage) {
				x = position.x; y = position.y; z = position.z;
			}

			virtual ~Drawable() {}

			/* Switch RenderMode */
			void toggleRenderMode() { mode = mode == RenderMode::SOLID ? RenderMode::WIRED : RenderMode::SOLID; }

			void setRenderMode(RenderMode mode) { this->mode = mode; }
			RenderMode getRenderMode() const { return mode; }

			void setPosition(ivec3 position) { x = position.x; y = position.y; z = position.z; }
			vec3 getPosition() const { return vec3(x, y, z); }

			void setTextureOffset(TextureID textureOffset) { this->textureOffset = textureOffset; }
			vec2 getTextureOffset() const { return vec2((GLubyte)textureOffset & 0x0F, ((GLubyte)textureOffset >> 4) & 0x0F); }
			TextureID getTextureID() const { return textureOffset; }
			void setColor(vec4 color) { this->color = color; }
			vec4 getColor() const { return color; }

			GLsizei getSize() { return nrOfVertices; }
		};
	}
}