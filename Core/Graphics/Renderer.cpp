#include "Renderer.hpp"

namespace Core {
	namespace Graphics {
		Renderer::Renderer(GLsizei maxObjectCount, GLsizei objectSize, RenderMode mode) : mode(mode) {
			// Generates vao and vbo
			glGenVertexArrays(1, &vao);
			glGenBuffers(1, &vbo);

			// Calculates needed sizes
			bufferSize = maxObjectCount * objectSize * sizeof(VertexAttr);
			vertexCount = maxObjectCount * objectSize;

			// Binds vao
			glBindVertexArray(vao);
			// Binds vbo
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			// Reserves memory on the VRAM
			glBufferData(GL_ARRAY_BUFFER, bufferSize * 3, 0, GL_DYNAMIC_DRAW);

			// Specifies the structur of the data, which will be send to the VRAM
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttr), (const GLvoid*)0);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttr), (const GLvoid*)(3 * sizeof(GLfloat)));

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexAttr), (const GLvoid*)(6 * sizeof(GLfloat)));

			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(VertexAttr), (const GLvoid*)(8 * sizeof(GLfloat)));

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
			vertexAttributes = (VertexAttr*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void Renderer::end() {
			// Release pointer
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void Renderer::submit(Drawable* object) {
			// Set vertex-information for each vertex
			for (GLsizei i = 0; i < object->getSize(); i++) {
				vertexAttributes->position = object->getPosition(i);
				vertexAttributes->normal = object->getNormal(i);
				vertexAttributes->uv = object->getUV(i);
				vertexAttributes->blendColor = object->getblendColor(i);
				vertexAttributes++;
			}
		}

		void Renderer::draw() {
			// Binds stuff
			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);

			// Draws all vertices
			switch (mode) {
			case RenderMode::SOLID:
				glDrawArrays(GL_TRIANGLES, 0, vertexCount);
				break;
			case RenderMode::WIRED:
				glDrawArrays(GL_LINE_STRIP, 0, vertexCount);
				break;
			}

			// Unbind all
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}
