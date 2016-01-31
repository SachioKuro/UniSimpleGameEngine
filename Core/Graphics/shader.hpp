#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "../Utils/GL.hpp"

namespace Core {
	namespace Graphics {
		/* Integer-Wrapper with a default-value of -2 */
		struct IntCache {
			GLint value = -2;
			IntCache() {};
			IntCache(GLint _value) : value(_value) {};
		};

		/* Handles the shader */
		class Shader
		{
		public:
			// Shaderprograms
			static Shader *Block, *Sky, *Water;
		private:
			GLuint programID;
			// Cache for the location of shader-variables
			std::map<const char*, IntCache> locationCache;
		public:
			/* Initialize shaders */
			static void init();
			/* delete shaders */
			static void del();
			Shader(const char* const vertexShaderPath, const char* const fragmentShaderPath);
			~Shader();
			
			/* Activates the shaderprogram */
			void activate() const;
			/* Deactivates the shaderprogram */
			void deactivate() const;
			/* Wrapper */
			/* Sets Integer-Variable in the Shader */
			void setUniformInteger(const char* location, const int value);
			/* Sets Vector3-Variable in the Shader */
			void setUniformVector3(const char* location, const glm::vec3& vector);
			/* Sets Vector4-Variable in the Shader */
			void setUniformVector4(const char* location, const glm::vec4& vector);
			/* Sets Matrix4x4-Variable in the Shader */
			void setUniformMatrix4(const char* location, const glm::mat4& matrix);
		private:
			/* Get the cached location of a variable in the shader */
			GLint getUniformLocation(const char* name);
			/* Load shader from file */
			GLuint load(const char* const vertexShaderPath, const char* const fragmentShaderPath);
		};
	}
}