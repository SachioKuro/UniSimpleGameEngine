#include "SkyBlockContext.hpp"

namespace Core {
	namespace Graphics {
		SkyBlockContext::SkyBlockContext() {
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

			mesh = new ivec3[36];
			normals = new ivec3[6];
			uvs = new vec2[6];

			/* Face Front */
			*(mesh++) = ivec3(-1, -1, -1); *(mesh++) = ivec3( 1,  1, -1); *(mesh++) = ivec3(-1,  1, -1);
			*(mesh++) = ivec3(-1, -1, -1); *(mesh++) = ivec3( 1, -1, -1); *(mesh++) = ivec3( 1,  1, -1);
			/* Face Right */
			*(mesh++) = ivec3( 1, -1, -1); *(mesh++) = ivec3( 1,  1,  1); *(mesh++) = ivec3( 1,  1, -1);
			*(mesh++) = ivec3( 1, -1, -1); *(mesh++) = ivec3( 1, -1,  1); *(mesh++) = ivec3( 1,  1,  1);
			/* Face Back */
			*(mesh++) = ivec3( 1, -1,  1); *(mesh++) = ivec3(-1,  1,  1); *(mesh++) = ivec3( 1,  1,  1);
			*(mesh++) = ivec3( 1, -1,  1); *(mesh++) = ivec3(-1, -1,  1); *(mesh++) = ivec3(-1,  1,  1);
			/* Face Left */
			*(mesh++) = ivec3(-1, -1,  1); *(mesh++) = ivec3(-1,  1, -1); *(mesh++) = ivec3(-1,  1,  1);
			*(mesh++) = ivec3(-1, -1,  1); *(mesh++) = ivec3(-1, -1, -1); *(mesh++) = ivec3(-1,  1, -1);
			/* Face Lower */
			*(mesh++) = ivec3(-1, -1,  1); *(mesh++) = ivec3( 1, -1, -1); *(mesh++) = ivec3(-1, -1, -1);
			*(mesh++) = ivec3(-1, -1,  1); *(mesh++) = ivec3( 1, -1,  1); *(mesh++) = ivec3( 1, -1, -1);
			/* Face Upper */
			*(mesh++) = ivec3(-1,  1, -1); *(mesh++) = ivec3( 1,  1,  1); *(mesh++) = ivec3(-1,  1,  1);
			*(mesh++) = ivec3(-1,  1, -1); *(mesh++) = ivec3( 1,  1, -1); *(mesh++) = ivec3( 1,  1,  1);

			*(normals++) = ivec3(0, 0, 1); *(normals++) = ivec3(-1, 0, 0); *(normals++) = ivec3(0,  0, -1);
			*(normals++) = ivec3(1, 0, 0); *(normals++) = ivec3( 0, 1, 0); *(normals++) = ivec3(0, -1,  0);

			*(uvs++) = vec2(0, 0); *(uvs++) = vec2(1, 1); *(uvs++) = vec2(0, 1);
			*(uvs++) = vec2(0, 0); *(uvs++) = vec2(1, 0); *(uvs++) = vec2(1, 1);

			mesh -= 36; normals -= 6; uvs -= 6;
		}

		SkyBlockContext::~SkyBlockContext() {
			delete[] mesh;
			delete[] normals;
			delete[] uvs;
		}
	}
}