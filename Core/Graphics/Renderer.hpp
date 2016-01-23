#pragma once

#include "../Utils/GL.hpp"
#include "Shader.hpp"
#include "Drawable.hpp"
#include "PrimitiveContext.hpp"
#include "SkyBlockContext.hpp"
#include "Camera.hpp"

namespace Core {
	namespace Graphics {
		/* Handles the rendering */
		class Renderer {
		private:
			// VertexArrayObject, VertexBufferObject
			GLuint vao, vbo, bufferSize, vertexCount = 0;
			Vertex* vertexAttributes;
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
			void submit(Drawable* object, PrimitiveContext* context, vec2& range = vec2(0, 0));
			/* Draw all objects */
			void draw();
		};
	}
}