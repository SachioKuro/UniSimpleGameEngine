#include "CoordSystem.hpp"

namespace Core {
	namespace Graphics {
		namespace Utils {
			CoordSystem::CoordSystem(vec3 position, GLboolean enabled) : enabled(enabled), Drawable(RenderMode::SOLID, 108) {
				vec3 mesh[108];
				vec4 colors[6];
				vec4 colorToVertex[108];

				colors[0] = vec4(0, 0, 1, 1); // + x
				colors[1] = vec4(0, 0, 0, 1); // - x
				colors[2] = vec4(0, 1, 0, 1); // + y
				colors[3] = vec4(0, 0, 0, 1); // - y
				colors[4] = vec4(1, 0, 0, 1); // + z
				colors[5] = vec4(0, 0, 0, 1); // - z

				int i = 0, j = 0;
				/* Face Front */  // Z-Axis
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2)); colorToVertex[j++] = colors[4];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2)); colorToVertex[j++] = colors[4];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2)); colorToVertex[j++] = colors[4];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2)); colorToVertex[j++] = colors[4];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2)); colorToVertex[j++] = colors[4];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2)); colorToVertex[j++] = colors[4];
				/* Face Right */
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2)); colorToVertex[j++] = colors[4];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2)); colorToVertex[j++] = colors[5];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2)); colorToVertex[j++] = colors[4];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2)); colorToVertex[j++] = colors[4];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2)); colorToVertex[j++] = colors[5];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2)); colorToVertex[j++] = colors[5];
				/* Face Back */
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2)); colorToVertex[j++] = colors[5];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2)); colorToVertex[j++] = colors[5];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2)); colorToVertex[j++] = colors[5];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2)); colorToVertex[j++] = colors[5];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2)); colorToVertex[j++] = colors[5];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2)); colorToVertex[j++] = colors[5];
				/* Face Left */
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2)); colorToVertex[j++] = colors[5];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2)); colorToVertex[j++] = colors[4];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2)); colorToVertex[j++] = colors[5];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2)); colorToVertex[j++] = colors[5];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2)); colorToVertex[j++] = colors[4];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2)); colorToVertex[j++] = colors[4];
				/* Face Lower */
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2)); colorToVertex[j++] = colors[5];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2)); colorToVertex[j++] = colors[4];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2)); colorToVertex[j++] = colors[4];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2)); colorToVertex[j++] = colors[5];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2)); colorToVertex[j++] = colors[5];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2)); colorToVertex[j++] = colors[4];
				/* Face Upper */
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2)); colorToVertex[j++] = colors[5];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2)); colorToVertex[j++] = colors[4];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2)); colorToVertex[j++] = colors[4];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2)); colorToVertex[j++] = colors[5];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_SIZE / 2)); colorToVertex[j++] = colors[5];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_SIZE / 2)); colorToVertex[j++] = colors[4];

				/* Face Front */ // Y_Axis
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[3];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[2];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[2];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[3];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[3];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[2];
				/* Face Right */
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[3];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[2];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[2];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[3];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[3];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[2];
				/* Face Back */
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[3];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[2];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[2];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[3];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[3];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[2];
				/* Face Left */
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[3];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[2];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[2];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[3];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[3];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[2];
				/* Face Lower */
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[3];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[3];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[3];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[3];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[3];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y - (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[3];
				/* Face Upper */
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[2];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[2];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[2];
				mesh[i++] = vec3(position.x + (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[2];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[2];
				mesh[i++] = vec3(position.x - (COORD_THICKNESS / 2), position.y + (COORD_SIZE / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[2];

				/* Face Front */ // X_Axis
				mesh[i++] = vec3(position.x - (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[1];
				mesh[i++] = vec3(position.x + (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[0];
				mesh[i++] = vec3(position.x - (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[1];
				mesh[i++] = vec3(position.x - (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[1];
				mesh[i++] = vec3(position.x + (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[0];
				mesh[i++] = vec3(position.x + (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[0];
				/* Face Right */
				mesh[i++] = vec3(position.x + (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[0];
				mesh[i++] = vec3(position.x + (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[0];
				mesh[i++] = vec3(position.x + (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[0];
				mesh[i++] = vec3(position.x + (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[0];
				mesh[i++] = vec3(position.x + (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[0];
				mesh[i++] = vec3(position.x + (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[0];
				/* Face Back */
				mesh[i++] = vec3(position.x + (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[0];
				mesh[i++] = vec3(position.x - (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[1];
				mesh[i++] = vec3(position.x + (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[0];
				mesh[i++] = vec3(position.x + (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[0];
				mesh[i++] = vec3(position.x - (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[1];
				mesh[i++] = vec3(position.x - (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[1];
				/* Face Left */
				mesh[i++] = vec3(position.x - (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[1];
				mesh[i++] = vec3(position.x - (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[1];
				mesh[i++] = vec3(position.x - (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[1];
				mesh[i++] = vec3(position.x - (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[1];
				mesh[i++] = vec3(position.x - (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[1];
				mesh[i++] = vec3(position.x - (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[1];
				/* Face Lower */
				mesh[i++] = vec3(position.x - (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[1];
				mesh[i++] = vec3(position.x + (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[0];
				mesh[i++] = vec3(position.x - (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[1];
				mesh[i++] = vec3(position.x - (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[1];
				mesh[i++] = vec3(position.x + (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[0];
				mesh[i++] = vec3(position.x + (COORD_SIZE / 2), position.y - (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[0];
				/* Face Upper */
				mesh[i++] = vec3(position.x + (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[0];
				mesh[i++] = vec3(position.x - (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[1];
				mesh[i++] = vec3(position.x + (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[0];
				mesh[i++] = vec3(position.x + (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[0];
				mesh[i++] = vec3(position.x - (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z - (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[1];
				mesh[i++] = vec3(position.x - (COORD_SIZE / 2), position.y + (COORD_THICKNESS / 2), position.z + (COORD_THICKNESS / 2)); colorToVertex[j++] = colors[1];

				// Set vertices
				for (GLint i = 0, j = 0, n = 0; i < 108; i++, n++) {
					setPosition(mesh[i], i);
					setNormal(vec3(0), i);
					setUV(vec2(0), i);
					setblendColor(colorToVertex[i], i);
				}

				renderer = new Renderer(1, i, RenderMode::SOLID);
				renderer->useShader(Shader::Info3D);

				nrOfVertices = i;
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
				renderer->submit((Drawable*)this);
				renderer->end();
				renderer->draw();
				renderer->deactivateShader();
			}
		}
	}
}