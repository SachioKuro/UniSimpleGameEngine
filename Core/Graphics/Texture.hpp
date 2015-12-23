#pragma once

#include "../Utils/GL.hpp"
#include <FreeImage.h>
#include <vector>

namespace Core {
	namespace Graphics {
		using namespace glm;
		using namespace std;
		/*
			Offset in Texture-Grid
			First 4 Bits = Row from below
			Last  4 Bits = Column from left
		*/
		enum class TextureID : GLubyte {
			GRASS01			= 0x00,
			STONE01			= 0x04,
			NONE			= 0xFF
		};

		/* Handles textureloading and handling */
		class Texture {
		private:
			// Texture-Information
			GLuint textureID, textureSampler;
			vec2 textureSize = vec2(256, 256);
			// Clamp from 0-1
			vec2 texturePercentage = textureSize / (textureSize * vec2(8, 8));

		public:
			/* Load and setup texture (File have to be RGBA) */
			GLboolean load2D(const char* texturePath, GLboolean withMipMaps = GL_TRUE);
			/* Load and setup texture (Cubemap) */
			GLboolean loadCubeMap(vector<const char*> texturePath);
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
			void defineTextureInfo(vec2 textureElementCount, vec2 textureElementSize);
			const vec2 getTexturePercentage() const { return texturePercentage; }

			const vec2 getTextureOffset(TextureID textureOffset) const {
				return vec2(((GLubyte)textureOffset & 0x0F) * texturePercentage.x,
					(((GLubyte)textureOffset & 0xF0) >> 4) * texturePercentage.y);
			}
		};
	}
}