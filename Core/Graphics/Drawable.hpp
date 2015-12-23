#pragma once

#include "../Utils/GL.hpp"
#include "Texture.hpp"

namespace Core {
	namespace Graphics {
		using namespace glm;

		/* Information for the Shader */
		struct VertexAttr {
			vec3 position;
			vec3 normal;
			vec2 uv;
			vec4 blendColor;
		};

		/* Type of rendering (Solid/Wired) */
		enum class RenderMode { SOLID, WIRED };

		/* Entity, which will be rendered */
		class Drawable {
		protected:
			/* Information for each Vertex */
			VertexAttr vertexAttr[36];
			GLsizei nrOfVertices;
			RenderMode mode = RenderMode::SOLID;
			/* Texture information */
			vec2 textureOffset, textureSize;
		public:
			Drawable(RenderMode mode, vec2 textureOffset, vec2 textureSize) 
				: mode(mode), textureOffset(textureOffset), textureSize(textureSize) {};
			Drawable(RenderMode mode)
				: mode(mode) {};
			virtual ~Drawable() {}

			/* Switch RenderMode */
			void toggleRenderMode() { mode = mode == RenderMode::SOLID ? RenderMode::WIRED : RenderMode::SOLID; }

			void setRenderMode(RenderMode mode) { this->mode = mode; }
			RenderMode getRenderMode() const { return mode; }

			void setPosition(vec3 position, GLushort index) { vertexAttr[index].position = position; }
			vec3 getPosition(GLushort index) const { return vertexAttr[index].position; }

			void setNormal(vec3 normal, GLushort index) { vertexAttr[index].normal = normal; }
			vec3 getNormal(GLushort index) const { return vertexAttr[index].normal; }

			void setUV(vec2 uv, GLushort index) { vertexAttr[index].uv = uv; }
			vec2 getUV(GLushort index) const { return vertexAttr[index].uv; }

			void setblendColor(vec4 color, GLushort index) { vertexAttr[index].blendColor = color; }
			vec4 getblendColor(GLushort index) const { return vertexAttr[index].blendColor; }

			void setVertexAttr(VertexAttr vertexAttr, GLushort index) { this->vertexAttr[index] = vertexAttr; }
			VertexAttr getVertexAttr(GLushort index) const { return vertexAttr[index]; }

			GLsizei getSize() { return nrOfVertices; }
		};
	}
}