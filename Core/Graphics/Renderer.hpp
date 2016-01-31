#pragma once

#include "../Utils/GL.hpp"
#include "Shader.hpp"
#include "Drawable.hpp"
#include "PrimitiveContext.hpp"

namespace Core {
	namespace Graphics {
		/* Handles the rendering */
		class Renderer {
		private:
			// VertexArrayObject, VertexBufferObject
			GLuint vao, vbo, bufferSize, vertexCount = 0;
			Vertex* vertexAttributes;
			Shader* shader;
			// seems awkward, but saves 72 %-Operations per submit
			const glm::int8 j[36] = { 0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,4,5,5,5,5,5,5 };
			const glm::int8 k[36] = { 0,1,2,3,4,5,0,1,2,3,4,5,0,1,2,3,4,5,0,1,2,3,4,5,0,1,2,3,4,5,0,1,2,3,4,5 };
		public:
			Renderer(GLsizei maxObjectCount, GLsizei objectSize);
			~Renderer();

			/* Select shader */
			void useShader(Shader* shader);
			void activateShader();
			void deactivateShader();

			Shader* getActiveShader() { return shader; }
			void setVertexCount(GLuint vertexCount) { this->vertexCount = vertexCount; }

			/* Ready for submission */
			void start();
			/* End the submission */
			void end();

			/* Submit an object for drawing */
			void submit(Drawable* object, PrimitiveContext* context, glm::vec2& range = glm::vec2(0, 0));
			/* Draw all objects */
			void draw();
		};
	}
}