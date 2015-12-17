#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "shader.hpp"

#include "../Utils/output.hpp"

namespace Core {
	namespace Graphics {
		using namespace std;

		Shader *Shader::Block, *Shader::Sky;

		GLuint readShaderCode(const char* const, string&);
		void checkCode(GLuint);

		Shader::Shader(const char* const vertexShaderPath, const char* const fragmentShaderPath) {
			programID = load(vertexShaderPath, fragmentShaderPath);
		}

		Shader::~Shader() {
			glDeleteProgram(programID);
		}

		GLuint Shader::load(const char* const vertexShaderPath, const char* const fragmentShaderPath) {
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

			GLuint pr_id = glCreateProgram();
			glAttachShader(pr_id, vertexShaderID);
			glAttachShader(pr_id, fragmentShaderID);
			glLinkProgram(pr_id);

			GLint result = GL_FALSE;
			int infoLogLength;

			// Check the program
			glGetProgramiv(pr_id, GL_LINK_STATUS, &result);
			glGetProgramiv(pr_id, GL_INFO_LOG_LENGTH, &infoLogLength);
			if (infoLogLength) {
				vector<char> programErrorMessage(infoLogLength + 1);
				glGetProgramInfoLog(pr_id, infoLogLength, NULL, &programErrorMessage[0]);
				ERROR_F("%s\n", &programErrorMessage[0]);
			}

			// Clean
			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);

			return pr_id;
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

		void Shader::activate() const {
			glUseProgram(programID);
		}

		void Shader::deactivate() const {
			glUseProgram(0);
		}

		void Shader::init() {
			Block = new Shader("Shader/simpleVertex.glsl", "Shader/simpleFragment.glsl");
			Sky = new Shader("Shader/skyVertex.glsl", "Shader/skyFragment.glsl");
		}

		void Shader::del() {
			delete Block;
			delete Sky;
		}

		GLint Shader::getUniformLocation(const char * name)
		{
			GLint location = glGetUniformLocation(programID, name);
			
			// Todo: Cache the Location

			if (location == -1)
				ERROR_F("Could not find Location with the name: %s\n", name);

			return location;
		}

		void Shader::setUniformMatrix4(const char* location, const glm::mat4& matrix) {
			glUniformMatrix4fv(getUniformLocation(location), 1, GL_FALSE, &matrix[0][0]);
		}

		void Shader::setUniformVector3(const char* location, const glm::vec3& vector) {
			glUniform3f(getUniformLocation(location), vector.x, vector.y, vector.z);
		}
	}
}
