#include "Renderer.hpp"

namespace Core {
	namespace Graphics {
		Renderer::Renderer(GLsizei maxObjectCount, GLsizei objectSize) {
			using namespace glm;
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
			glBufferData(GL_ARRAY_BUFFER, bufferSize, 0, GL_STATIC_DRAW);

			// Specifies the structur of the data, which will be send to the VRAM
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)0);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(vec3)));

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(vec3) + sizeof(vec2)));

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
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		// Todo: one base box + position
		void Renderer::submit(Drawable* object, PrimitiveContext* context, glm::vec2& range) {
			// Set vertex-information for each vertex
			for (glm::int8 i = range.x, n = (range.y == 0) ? object->getSize() : range.y; i < n; i++) {
				vertexAttributes->position = context->getMesh()[i] + object->getPosition();
				vertexAttributes->uv = context->getUVs(object->getTextureID())[k[i]];
				vertexAttributes->normal = context->getNormals()[j[i]];
				// Step to next Vertex
				vertexAttributes++;
				vertexCount ++;
			}
		}

		void Renderer::draw() {
			// Binds stuff
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, vertexCount);
			// Unbind all
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			vertexCount = 0;
		}
	}
}
