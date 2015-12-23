#pragma once

#include "../Utils/GL.hpp"
#include "Shader.hpp"
#include "Drawable.hpp"

namespace Core {
	namespace Graphics {
		/* Handles the rendering */
		class Renderer {
		private:
			// VertexArrayObject, VertexBufferObject
			GLuint vao, vbo, bufferSize, vertexCount;
			VertexAttr* vertexAttributes;
			Shader* shader;
			RenderMode mode;
		public:
			Renderer(GLsizei maxObjectCount, GLsizei objectSize, RenderMode mode);
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
			void submit(Drawable* object);
			/* Draw all objects */
			void draw();
		};
	}
}