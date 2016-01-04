#include "SkyboxBlock.hpp"

namespace Core {
	namespace Terrain {
		SkyboxBlock::SkyboxBlock(SkyType stype, RenderMode mode) : stype(stype), Drawable(mode, 36) {
			// Setup texture-information
			texture.defineTextureInfo(vec2(6, 2), vec2(1024, 1024));

			// Texturepaths
			vector<const char*> texturePaths;
			texturePaths.push_back("Textures/SkyBox/Tag01/posx.png");
			texturePaths.push_back("Textures/SkyBox/Tag01/negx.png");
			texturePaths.push_back("Textures/SkyBox/Tag01/posy.png");
			texturePaths.push_back("Textures/SkyBox/Tag01/negy.png");
			texturePaths.push_back("Textures/SkyBox/Tag01/posz.png");
			texturePaths.push_back("Textures/SkyBox/Tag01/negz.png");

			// Load the textures
			texture.loadCubeMap(texturePaths);

			vec3* mesh = new vec3[36];
			vec3* normals = new vec3[6];

			/* Face Front */
			*(mesh++) = vec3(-0.5, -0.5, -0.5);
			*(mesh++) = vec3(0.5, 0.5, -0.5);
			*(mesh++) = vec3(-0.5, 0.5, -0.5);
			*(mesh++) = vec3(-0.5, -0.5, -0.5);
			*(mesh++) = vec3(0.5, -0.5, -0.5);
			*(mesh++) = vec3(0.5, 0.5, -0.5);
			/* Face Right */
			*(mesh++) = vec3(0.5, -0.5, -0.5);
			*(mesh++) = vec3(0.5, 0.5, 0.5);
			*(mesh++) = vec3(0.5, 0.5, -0.5);
			*(mesh++) = vec3(0.5, -0.5, -0.5);
			*(mesh++) = vec3(0.5, -0.5, 0.5);
			*(mesh++) = vec3(0.5, 0.5, 0.5);
			/* Face Back */
			*(mesh++) = vec3(0.5, -0.5, 0.5);
			*(mesh++) = vec3(-0.5, 0.5, 0.5);
			*(mesh++) = vec3(0.5, 0.5, 0.5);
			*(mesh++) = vec3(0.5, -0.5, 0.5);
			*(mesh++) = vec3(-0.5, -0.5, 0.5);
			*(mesh++) = vec3(-0.5, 0.5, 0.5);
			/* Face Left */
			*(mesh++) = vec3(-0.5, -0.5, 0.5);
			*(mesh++) = vec3(-0.5, 0.5, -0.5);
			*(mesh++) = vec3(-0.5, 0.5, 0.5);
			*(mesh++) = vec3(-0.5, -0.5, 0.5);
			*(mesh++) = vec3(-0.5, -0.5, -0.5);
			*(mesh++) = vec3(-0.5, 0.5, -0.5);
			/* Face Lower */
			*(mesh++) = vec3(-0.5, -0.5, 0.5);
			*(mesh++) = vec3(0.5, -0.5, -0.5);
			*(mesh++) = vec3(-0.5, -0.5, -0.5);
			*(mesh++) = vec3(-0.5, -0.5, 0.5);
			*(mesh++) = vec3(0.5, -0.5, 0.5);
			*(mesh++) = vec3(0.5, -0.5, -0.5);
			/* Face Upper */
			*(mesh++) = vec3(-0.5, 0.5, -0.5);
			*(mesh++) = vec3(0.5, 0.5, 0.5);
			*(mesh++) = vec3(-0.5, 0.5, 0.5);
			*(mesh++) = vec3(-0.5, 0.5, -0.5);
			*(mesh++) = vec3(0.5, 0.5, -0.5);
			*(mesh++) = vec3(0.5, 0.5, 0.5);

			*(normals++) = vec3(0, 0, 1);
			*(normals++) = vec3(-1, 0, 0);
			*(normals++) = vec3(0, 0, -1);
			*(normals++) = vec3(1, 0, 0);
			*(normals++) = vec3(0, 1, 0);
			*(normals++) = vec3(0, -1, 0);

			// Resets pointer
			mesh -= 36; normals -= 6;

			// Set vertices
			for (GLsizei i = 0, j = 0, n = 0; i < 36; i++, n++) {
				setPosition(mesh[i], i);
				setNormal(normals[j], i);
				setUV(vec2(0, 0), i);
				setblendColor(vec4(0, 0, 0, 0), i);
				if (n >= 5) {
					j++;
					n = -1;
				}
			}

			delete[] mesh;
			delete[] normals;
			nrOfVertices = 36;

			// Setup renderer
			renderer = new Renderer(1, 36, RenderMode::SOLID);
			renderer->useShader(Shader::Sky);
		}

		SkyboxBlock::~SkyboxBlock() {
			delete renderer;
		}

		void SkyboxBlock::draw(vec3& position, mat4& view, mat4& projection) {
			// Setup modelmatrix
			model[3].x = position.x;
			model[3].y = position.y;
			model[3].z = position.z;
			// Setup rendering
			renderer->activateShader();
			// Set shadervariables
			renderer->getActiveShader()->setUniformMatrix4("Model", model);
			renderer->getActiveShader()->setUniformMatrix4("View", view);
			renderer->getActiveShader()->setUniformMatrix4("Projection", projection);
			// Don't check for depth
			glDepthMask(GL_FALSE);
			renderer->start();
			// Submit Skybox
			renderer->submit((Drawable*)this);
			// Ready for render
			renderer->end();
			// Starts rendering
			renderer->draw();
			glDepthMask(GL_TRUE);
			renderer->deactivateShader();
		}
	}
}