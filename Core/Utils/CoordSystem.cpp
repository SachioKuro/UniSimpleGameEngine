#include "CoordSystem.hpp"

namespace Core {
	namespace Graphics {
		namespace Utils {
			CoordSystem::CoordSystem(vec3 position, GLboolean enabled) : enabled(enabled), Drawable(RenderMode::SOLID) {
				vec3* mesh = new vec3[108];

				/* Face Front */  // Z-Axis
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2));
				/* Face Right */
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2));
				/* Face Back */
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2));
				/* Face Left */
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2));
				/* Face Lower */
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2));
				/* Face Upper */
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2));

				/* Face Front */ // Y_Axis
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2));
				/* Face Right */
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2));
				/* Face Back */
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2));
				/* Face Left */
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2));
				/* Face Lower */
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2));
				/* Face Upper */
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2));

				/* Face Front */ // X_Axis
				*(mesh++) = vec3(position.x - (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2));
				/* Face Right */
				*(mesh++) = vec3(position.x + (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2));
				/* Face Back */
				*(mesh++) = vec3(position.x + (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2));
				/* Face Left */
				*(mesh++) = vec3(position.x - (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2));
				/* Face Lower */
				*(mesh++) = vec3(position.x - (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2));
				/* Face Upper */
				*(mesh++) = vec3(position.x + (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x + (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2));
				*(mesh++) = vec3(position.x - (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2));

				// Resets pointer
				mesh -= 108;

				// Set vertices
				for (GLsizei i = 0, j = 0, n = 0; i < 108; i++, n++) {
					setPosition(mesh[i], i);
					setblendColor(vec4(i >= 0 && i < 36 ? 1 : 0, i >= 36 && i < 72 ? 1 : 0, i >= 72 && i < 108 ? 1 : 0, 1), i);
				}

				delete[] mesh;

				renderer = new Renderer(3, 108, RenderMode::SOLID);
				renderer->useShader(Shader::Info3D);
			}
			
			CoordSystem::~CoordSystem() {
				delete renderer;
			}

			void CoordSystem::submit() {
				if (isEnabled()) renderer->submit((Drawable*)this);
			}

			void CoordSystem::draw(mat4 projection, mat4 view) {
				renderer->activateShader();
				renderer->start();
				renderer->getActiveShader()->setUniformMatrix4("MVP", projection * view);
				submit();
				renderer->end();
				renderer->draw();
				renderer->deactivateShader();
			}
		}
	}
}