#include "Texture.hpp"
#include "../Utils/Output.hpp"


namespace Core {
	namespace Graphics {
		GLboolean Texture::load2D(const char* texturePath, GLboolean withMipMaps) {
			// Gets filetype from headerfile
			FREE_IMAGE_FORMAT format = FreeImage_GetFileType(texturePath);

			// If it failed, it tries to get filetype from Ext.
			if (format == FIF_UNKNOWN)
				format = FreeImage_GetFIFFromFilename(texturePath);

			// Failed prozess
			if (format == FIF_UNKNOWN)
				return GL_FALSE;

			// Holds the bits from file
			FIBITMAP* bits;

			// If FreeImage supports the filetype, it loads the file
			if (FreeImage_FIFSupportsReading(format))
				bits = FreeImage_Load(format, texturePath);

			// If nothing was loaded, exit
			if (!bits)
				return false;

			// Data and information
			BYTE* data = FreeImage_GetBits(bits);
			GLuint width = FreeImage_GetWidth(bits);
			GLuint height = FreeImage_GetHeight(bits);
			GLubyte bytesPerPixel = FreeImage_GetBPP(bits);

			// No information = Fail
			if (data == 0 || width == 0 || height == 0)
				return GL_FALSE;

			// Generate and bind texture
			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);

			// Upload the data
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
			
			// Generate mipmap
			if (withMipMaps)
				glGenerateMipmap(GL_TEXTURE_2D);

			// Clear
			FreeImage_Unload(bits);

			// Generate samplers for dynamic information
			glGenSamplers(1, &textureSampler);

			// Typical configuration for CubeMaps
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


			return GL_TRUE;
		}
		
		GLboolean Texture::loadCubeMap(vector<const char*> texturePaths) {
			// Container for texturedata
			vector<FIBITMAP*> bits;
			vector<BYTE*> cubeData;

			// For each texturefile - s.o.
			for (const char* texturePath : texturePaths) {
				FREE_IMAGE_FORMAT format = FreeImage_GetFileType(texturePath);

				if (format == FIF_UNKNOWN)
					format = FreeImage_GetFIFFromFilename(texturePath);

				if (format == FIF_UNKNOWN)
					return GL_FALSE;

				if (FreeImage_FIFSupportsReading(format))
					bits.push_back(FreeImage_Load(format, texturePath));

				if (!bits.back())
					return false;

				cubeData.push_back(FreeImage_GetBits(bits.back()));

				if (cubeData.back() == 0)
					return GL_FALSE;
			}

			// Activate, generate and bind
			glActiveTexture(GL_TEXTURE0);
			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
			
			// Reserves memory on VRAM
			glTexStorage2D(GL_TEXTURE_CUBE_MAP, 1, GL_RGBA8, textureSize.x, textureSize.y);

			// Upload the data 
			for (GLsizei i = 0, n = cubeData.size(); i < n; i++)
				glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, 0, 0, FreeImage_GetWidth(bits[i]), FreeImage_GetHeight(bits[i]), GL_BGR, GL_UNSIGNED_BYTE, cubeData[i]);

			// Clean
			for (FIBITMAP* bitmap : bits)
				FreeImage_Unload(bitmap);

			// Typical configuration for CubeMaps
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

			return GL_TRUE;
		}
		
		void Texture::setFiltering(GLint magnification, GLint minification) const {
			glSamplerParameteri(textureSampler, GL_TEXTURE_MAG_FILTER, magnification);
			glSamplerParameteri(textureSampler, GL_TEXTURE_MIN_FILTER, minification);
		}
		
		void Texture::setCubeBoxParam() const {
			glSamplerParameterf(textureSampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glSamplerParameterf(textureSampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glSamplerParameterf(textureSampler, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}

		void Texture::bind(GLenum type, GLuint unit) const {
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(type, textureID);
			glBindSampler(unit, textureSampler);
		}

		void Texture::unbind(GLenum type, GLuint unit) const {
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(type, 0);
			glBindSampler(unit, 0);
		}

		void Texture::defineTextureInfo(vec2 textureElementCount, vec2 textureElementSize) {
			texturePercentage = textureElementSize / (textureElementSize * textureElementCount);
			textureSize = textureElementSize;
		}
	}
}
