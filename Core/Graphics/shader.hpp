#pragma once

#include "../Utils/GL.hpp"

namespace Core {
	namespace Graphics {
		class Shader
		{
		private:
			GLuint programID;
		public:
			Shader(const char* const vertexShaderPath, const char* const fragmentShaderPath);
			~Shader();
			void activate() const;
			void deactivate() const;

			void setUniformMatrix4(const char* location, const glm::mat4& matrix);
		private:
			GLint getUniformLocation(const char* name);
			GLuint load(const char* const vertexShaderPath, const char* const fragmentShaderPath);
		};
	}
}