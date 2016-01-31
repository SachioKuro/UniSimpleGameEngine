#pragma once

#include "../Utils/GL.hpp"
#include <FreeImage.h>
#include <vector>

namespace Core {
	namespace Graphics {
		/*
			Offset in Texture-Grid
			First 4 Bits = Row from below
			Last  4 Bits = Column from left
		*/
		enum class TextureID : GLubyte {
			GRASS01 = 0x00,
			GRASS02 = 0x01,
			GRASS03 = 0x02,
			STONE01 = 0x20,
			STONE02 = 0x21,
			STONE03 = 0x22,
			SAND01  = 0x40,
			KIES01  = 0x44,
			SNOW01  = 0x60,
			WATER01 = 0x46,
			NONE    = 0xFF
		};

		/* Handles textureloading and handling */
		class Texture {
		private:
			// Texture-Information
			GLuint textureID, textureSampler;
			glm::vec2 textureSize = glm::vec2(128, 128);
			// Clamp from 0-1
			glm::vec2 texturePercentage = textureSize / (textureSize * glm::vec2(8, 8));

		public:
			/* Load and setup texture (File have to be RGBA) */
			GLboolean load2D(const char* texturePath, GLboolean withMipMaps = GL_TRUE);
			/* Load and setup texture (Cubemap) */
			GLboolean loadCubeMap(std::vector<const char*> texturePath);
			/* Set the Filtering for 2D-Texture */
			void setFiltering(GLint magnification, GLint minification) const;
			/* Set the CubeBoxParam for 2D-Texture */
			void setCubeBoxParam() const;
			GLuint getID() const { return textureID; }
			GLuint getSampler() const { return textureSampler; }
			/* Bind texture */
			void bind(GLenum type, GLuint unit) const;
			/* Unbind texture */
			void unbind(GLenum type, GLuint unit) const;

			/* Set texture-information */
			void defineTextureInfo(glm::vec2 textureElementCount, glm::vec2 textureElementSize);
			const glm::vec2 getTexturePercentage() const { return texturePercentage; }

			/* Returns the textureoffset in percentage */
			const glm::vec2 getTextureOffset(TextureID textureOffset) const {
				return glm::vec2(((GLubyte)textureOffset & 0x0F) * texturePercentage.x,
					(((GLubyte)textureOffset & 0xF0) >> 4) * texturePercentage.y);
			}
		};
	}
}