#pragma once

#include "../Utils/GL.hpp"
#include <FreeImage.h>
#include <vector>

namespace Core {
	namespace Graphics {
		class Texture {
		private:
			GLuint width, height, bytesPerPixel;
			GLuint textureID, textureSampler;
		public:
			static GLuint load(const char * texturePath);
			GLboolean load2D(const char* texturePath, GLboolean withMipMaps = GL_TRUE);
			GLboolean loadCubeMap(vector<const char*> texturePaths, GLboolean withMipMaps = GL_TRUE);
			
			void setFiltering(GLint magnification, GLint minification) const;
			void setCubeBoxParam() const;
			GLuint getID() const { return textureID; }
			GLuint getSampler() const { return textureSampler; }
			void bind(GLuint unit) const;
		private:
			void retrieveData(BYTE* data);
		};
	}
}