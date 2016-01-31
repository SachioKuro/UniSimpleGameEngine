#include "SkyBlockContext.hpp"

namespace Core {
	namespace Graphics {
		SkyBlockContext::SkyBlockContext() {
			using namespace glm;
			// Setup texture-information
			texture.defineTextureInfo(vec2(6, 2), vec2(1024, 1024));

			// Texturepaths
			std::vector<const char*> texturePaths;
			texturePaths.push_back("Textures/SkyBox/Tag01/posx.png");
			texturePaths.push_back("Textures/SkyBox/Tag01/negx.png");
			texturePaths.push_back("Textures/SkyBox/Tag01/posy.png");
			texturePaths.push_back("Textures/SkyBox/Tag01/negy.png");
			texturePaths.push_back("Textures/SkyBox/Tag01/posz.png");
			texturePaths.push_back("Textures/SkyBox/Tag01/negz.png");

			// Load the textures
			texture.loadCubeMap(texturePaths);

			mesh = new glm::vec3[36];
			normals = new glm::vec3[6];
			uvs = new glm::vec2[6];

			/* Face Front */
			*(mesh++) = vec3(-1, -1, -1); *(mesh++) = vec3( 1,  1, -1); *(mesh++) = vec3(-1,  1, -1);
			*(mesh++) = vec3(-1, -1, -1); *(mesh++) = vec3( 1, -1, -1); *(mesh++) = vec3( 1,  1, -1);
			/* Face Right */
			*(mesh++) = vec3( 1, -1, -1); *(mesh++) = vec3( 1,  1,  1); *(mesh++) = vec3( 1,  1, -1);
			*(mesh++) = vec3( 1, -1, -1); *(mesh++) = vec3( 1, -1,  1); *(mesh++) = vec3( 1,  1,  1);
			/* Face Back */
			*(mesh++) = vec3( 1, -1,  1); *(mesh++) = vec3(-1,  1,  1); *(mesh++) = vec3( 1,  1,  1);
			*(mesh++) = vec3( 1, -1,  1); *(mesh++) = vec3(-1, -1,  1); *(mesh++) = vec3(-1,  1,  1);
			/* Face Left */
			*(mesh++) = vec3(-1, -1,  1); *(mesh++) = vec3(-1,  1, -1); *(mesh++) = vec3(-1,  1,  1);
			*(mesh++) = vec3(-1, -1,  1); *(mesh++) = vec3(-1, -1, -1); *(mesh++) = vec3(-1,  1, -1);
			/* Face Lower */
			*(mesh++) = vec3(-1, -1,  1); *(mesh++) = vec3( 1, -1, -1); *(mesh++) = vec3(-1, -1, -1);
			*(mesh++) = vec3(-1, -1,  1); *(mesh++) = vec3( 1, -1,  1); *(mesh++) = vec3( 1, -1, -1);
			/* Face Upper */
			*(mesh++) = vec3(-1,  1, -1); *(mesh++) = vec3( 1,  1,  1); *(mesh++) = vec3(-1,  1,  1);
			*(mesh++) = vec3(-1,  1, -1); *(mesh++) = vec3( 1,  1, -1); *(mesh++) = vec3( 1,  1,  1);

			*(normals++) = vec3(0, 0, 1); *(normals++) = vec3(-1, 0, 0); *(normals++) = vec3(0,  0, -1);
			*(normals++) = vec3(1, 0, 0); *(normals++) = vec3( 0, 1, 0); *(normals++) = vec3(0, -1,  0);

			*(uvs++) = glm::vec2(0, 0); *(uvs++) = glm::vec2(1, 1); *(uvs++) = glm::vec2(0, 1);
			*(uvs++) = glm::vec2(0, 0); *(uvs++) = glm::vec2(1, 0); *(uvs++) = glm::vec2(1, 1);

			mesh -= 36; normals -= 6; uvs -= 6;
		}

		SkyBlockContext::~SkyBlockContext() {
			delete[] mesh;
			delete[] normals;
			delete[] uvs;
		}
	}
}