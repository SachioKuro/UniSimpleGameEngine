#include "Renderer.hpp"

namespace Core {
	namespace Graphics {
		Renderer::Renderer(GLsizei maxObjectCount, GLsizei objectSize, RenderMode mode) : mode(mode) {
			// Generates vao and vbo
			glGenVertexArrays(1, &vao);
			glGenBuffers(1, &vbo);

			// Calculates needed sizes
			bufferSize = maxObjectCount * objectSize * sizeof(Vertex);

			// Binds vao
			glBindVertexArray(vao);
			// Binds vbo
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			// Reserves memory on the VRAM
			if (bufferSize > 100000) glBufferData(GL_ARRAY_BUFFER, (bufferSize + 1) / 2, 0, GL_STATIC_DRAW);
			else					 glBufferData(GL_ARRAY_BUFFER, bufferSize, 0, GL_STATIC_DRAW);

			// Specifies the structur of the data, which will be send to the VRAM
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)0);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(3 * sizeof(GLfloat)));

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(6 * sizeof(GLfloat)));

			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(8 * sizeof(GLfloat)));

			// Release bindings
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		Renderer::~Renderer() {
			glDeleteBuffers(1, &vbo);
			glDeleteVertexArrays(1, &vao);
		}

		void Renderer::useShader(Shader * shader) {
			this->shader = shader;
		}

		void Renderer::activateShader() {
			shader->activate();
		}

		void Renderer::deactivateShader() {
			shader->deactivate();
		}

		void Renderer::start() {
			// Binds vbo
			glBindBuffer(GL_ARRAY_BUFFER, vbo);

			// Fetch the pointer to the memory on the VRAM
			vertexAttributes = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void Renderer::end() {
			// Release pointer
			//glInvalidateBufferData(vbo);
			glUnmapBuffer(GL_ARRAY_BUFFER);
			//glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		// seems awkward, but saves 72 %-Operations per submit
		int8 j[] = { 0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,4,5,5,5,5,5,5 };
		int8 k[] = {0,1,2,3,4,5,0,1,2,3,4,5,0,1,2,3,4,5,0,1,2,3,4,5,0,1,2,3,4,5,0,1,2,3,4,5};
		// Todo: one base box + position
		void Renderer::submit(Drawable* object, PrimitiveContext* context) {
			// Set vertex-information for each vertex
			for (int8 i = 0; i < object->getSize(); i++) {
				vertexAttributes->position = context->getMesh()[i] + object->getPosition();
				vertexAttributes->normal = context->getNormals()[j[i]];
				vertexAttributes->uv = context->getUVs(object->getTextureID())[k[i]];
				vertexAttributes->color = object->getColor();
				vertexAttributes++;
			}
			vertexCount += object->getSize();
		}

		void Renderer::draw() {
			// Binds stuff
			glBindVertexArray(vao);
			//glBindBuffer(GL_ARRAY_BUFFER, vbo);

			glDrawArrays(GL_TRIANGLES, 0, vertexCount);
			// Unbind all
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			vertexCount = 0;
		}
	}
}
