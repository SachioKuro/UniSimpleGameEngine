#pragma once

#include "GL.hpp"
#include "../Graphics/Renderer.hpp"
#include "../Graphics/Drawable.hpp"

#define COORD_SIZE 1000
#define COORD_THICKNESS 0.2

namespace Core {
	namespace Graphics {
		namespace Utils {
			class CoordSystem : public Drawable {
			private:
				GLboolean enabled = GL_TRUE;
				Renderer* renderer;
			public:
				CoordSystem(vec3 position, GLboolean enabled);
				~CoordSystem();

				void enable() { enabled = GL_TRUE; }
				void disable() { enabled = GL_FALSE; }
				GLboolean isEnabled() { return enabled; }

				void submit();
				void draw(mat4 projection, mat4 view);
			};
		}
	}
}