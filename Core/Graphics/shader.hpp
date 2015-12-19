#pragma once

#include "../Utils/GL.hpp"

namespace Core {
	namespace Graphics {
		class Shader
		{
		public:
			static Shader *Block, *Sky;
		private:
			GLuint programID;
			GLchar errorFlags = 0x0000;
		public:
			static void init();
			static void del();
			Shader(const char* const vertexShaderPath, const char* const fragmentShaderPath);
			~Shader();
			void activate() const;
			void deactivate() const;
			void setUniformVector3(const char* location, const glm::vec3& vector);
			void setUniformMatrix4(const char* location, const glm::mat4& matrix);
		private:
			GLint getUniformLocation(const char* name);
			GLuint load(const char* const vertexShaderPath, const char* const fragmentShaderPath);
		};
	}
}