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
			*(mesh++) = vec3(-0.5, -0.5, -0.5); *(mesh++) = vec3( 0.5,  0.5, -0.5); *(mesh++) = vec3(-0.5,  0.5, -0.5);
			*(mesh++) = vec3(-0.5, -0.5, -0.5); *(mesh++) = vec3( 0.5, -0.5, -0.5); *(mesh++) = vec3( 0.5,  0.5, -0.5);
			/* Face Right */
			*(mesh++) = vec3( 0.5, -0.5, -0.5); *(mesh++) = vec3( 0.5,  0.5,  0.5); *(mesh++) = vec3( 0.5,  0.5, -0.5);
			*(mesh++) = vec3( 0.5, -0.5, -0.5); *(mesh++) = vec3( 0.5, -0.5,  0.5); *(mesh++) = vec3( 0.5,  0.5,  0.5);
			/* Face Back */
			*(mesh++) = vec3( 0.5, -0.5,  0.5); *(mesh++) = vec3(-0.5,  0.5,  0.5); *(mesh++) = vec3( 0.5,  0.5,  0.5);
			*(mesh++) = vec3( 0.5, -0.5,  0.5); *(mesh++) = vec3(-0.5, -0.5,  0.5); *(mesh++) = vec3(-0.5,  0.5,  0.5);
			/* Face Left */
			*(mesh++) = vec3(-0.5, -0.5,  0.5); *(mesh++) = vec3(-0.5,  0.5, -0.5); *(mesh++) = vec3(-0.5,  0.5,  0.5);
			*(mesh++) = vec3(-0.5, -0.5,  0.5); *(mesh++) = vec3(-0.5, -0.5, -0.5); *(mesh++) = vec3(-0.5,  0.5, -0.5);
			/* Face Lower */
			*(mesh++) = vec3(-0.5, -0.5,  0.5); *(mesh++) = vec3( 0.5, -0.5, -0.5); *(mesh++) = vec3(-0.5, -0.5, -0.5);
			*(mesh++) = vec3(-0.5, -0.5,  0.5); *(mesh++) = vec3( 0.5, -0.5,  0.5); *(mesh++) = vec3( 0.5, -0.5, -0.5);
			/* Face Upper */
			*(mesh++) = vec3(-0.5,  0.5, -0.5); *(mesh++) = vec3( 0.5,  0.5,  0.5); *(mesh++) = vec3(-0.5,  0.5,  0.5);
			*(mesh++) = vec3(-0.5,  0.5, -0.5); *(mesh++) = vec3( 0.5,  0.5, -0.5); *(mesh++) = vec3( 0.5,  0.5,  0.5);

			*(normals++) = vec3(0, 0, 1); *(normals++) = vec3(-1, 0, 0); *(normals++) = vec3(0,  0, -1);
			*(normals++) = vec3(1, 0, 0); *(normals++) = vec3( 0, 1, 0); *(normals++) = vec3(0, -1,  0);

			*(uvs++) = vec2(0, 0); *(uvs++) = texture.getTexturePercentage(); *(uvs++) = vec2(0, texture.getTexturePercentage().t);
			*(uvs++) = vec2(0, 0); *(uvs++) = vec2(texture.getTexturePercentage().s, 0); *(uvs++) = texture.getTexturePercentage();
		}

		SkyBlockContext::~SkyBlockContext() {
			delete[] mesh;
			delete[] normals;
			delete[] uvs;
		}
	}
}