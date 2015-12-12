#pragma once

#include "../Utils/GL.hpp"

namespace Core {
	namespace Graphics {
		class Texture {
		public:
			static GLuint load(const char* texturePath);
		};
	}
}