#pragma once

#define GLEW_STATIC
#include <GL\glew.h>

namespace Core {
	namespace Graphics {
		class Shader
		{
		public:
			static GLuint loadShaders(const char* const vertexShaderPath, const char* const fragmentShaderPath);
		};
	}
}