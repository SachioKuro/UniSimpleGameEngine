#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "shader.hpp"

#include "../Utils/output.hpp"

namespace Core {
	namespace Graphics {
		using namespace std;

		GLuint readShaderCode(const char* const, string&);
		void checkCode(GLuint);

		GLuint Shader::loadShaders(const char* const vertexShaderPath, const char* const fragmentShaderPath) {

			// Create Shaders
			GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

			// Read Shader-Code
			string vertexShaderCode;
			if (!readShaderCode(vertexShaderPath, vertexShaderCode))
				return 0;

			string fragmentShaderCode;
			if (!readShaderCode(fragmentShaderPath, fragmentShaderCode))
				return 0;

			// Compile Shader
			DEBUG_F("Compiling shader : %s\n", vertexShaderPath);

			char const* vertexSourcePointer = vertexShaderCode.c_str();
			glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
			glCompileShader(vertexShaderID);

			DEBUG_F("Compiling shader : %s\n", fragmentShaderPath);

			char const* fragmentShaderPointer = fragmentShaderCode.c_str();
			glShaderSource(fragmentShaderID, 1, &fragmentShaderPointer, NULL);
			glCompileShader(fragmentShaderID);

			// Check Shader
			checkCode(vertexShaderID);
			checkCode(fragmentShaderID);
			
			// Linking to a program
			DEBUG("Linking programm");

			GLuint programID = glCreateProgram();
			glAttachShader(programID, vertexShaderID);
			glAttachShader(programID, fragmentShaderID);
			glLinkProgram(programID);

			GLint result = GL_FALSE; 
			int infoLogLength;

			// Check the program
			glGetProgramiv(programID, GL_LINK_STATUS, &result);
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
			if (infoLogLength) {
				vector<char> programErrorMessage(infoLogLength + 1);
				glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
				ERROR_F("%s\n", &programErrorMessage[0]);
			}

			// Clean
			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);

			return programID;
		}

		/*
			Read Shader-Code from File
		*/
		inline GLuint readShaderCode(const char* const path, string& code) {
			ifstream vertexShaderStream(path, ios::in);
			if (vertexShaderStream.is_open()) {
				string line = "";
				while (getline(vertexShaderStream, line))
					code += "\n" + line;
				vertexShaderStream.close();
				return 1;
			} else {
				ERROR_F("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", path);
				return 0;
			}
		}

		inline void checkCode(GLuint shaderID) {
			GLint result = GL_FALSE; // Compilationresult
			int infoLogLength;

			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

			if (infoLogLength) {
				vector<char> shaderErrorMessage(infoLogLength + 1);
				glGetShaderInfoLog(shaderID, infoLogLength, NULL, &shaderErrorMessage[0]);
				ERROR_F("%s\n", &shaderErrorMessage[0]);
			}
		}
	}
}
