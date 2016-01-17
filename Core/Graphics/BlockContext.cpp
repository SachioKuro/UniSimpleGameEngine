#include "BlockContext.hpp"

namespace Core {
	namespace Graphics {
		BlockContext::BlockContext() {
			// Define texturemap
			texture.load2D("Textures/texturemap128.png");
			texture.setCubeBoxParam();
			texture.defineTextureInfo(vec2(8, 8), vec2(128, 128));

			mesh = new ivec3[36];
			normals = new ivec3[6];

			center = vec4(0.5, -0.5, -0.5, 1);

			/* Face Front */
			*(mesh++) = ivec3(0,  0, -1); *(mesh++) = ivec3(1, -1, -1); *(mesh++) = ivec3(0, -1, -1);
			*(mesh++) = ivec3(0,  0, -1); *(mesh++) = ivec3(1,  0, -1); *(mesh++) = ivec3(1, -1, -1);
			/* Face Right */
			*(mesh++) = ivec3(1,  0, -1); *(mesh++) = ivec3(1, -1,  0); *(mesh++) = ivec3(1, -1, -1);
			*(mesh++) = ivec3(1,  0, -1); *(mesh++) = ivec3(1,  0,  0); *(mesh++) = ivec3(1, -1,  0);
			/* Face Back */
			*(mesh++) = ivec3(1,  0,  0); *(mesh++) = ivec3(0, -1,  0);	*(mesh++) = ivec3(1, -1,  0);
			*(mesh++) = ivec3(1,  0,  0); *(mesh++) = ivec3(0,  0,  0); *(mesh++) = ivec3(0, -1,  0);
			/* Face Left */
			*(mesh++) = ivec3(0,  0,  0); *(mesh++) = ivec3(0, -1, -1); *(mesh++) = ivec3(0, -1,  0);
			*(mesh++) = ivec3(0,  0,  0); *(mesh++) = ivec3(0,  0, -1); *(mesh++) = ivec3(0, -1, -1);
			/* Face Lower */
			*(mesh++) = ivec3(0,  0,  0); *(mesh++) = ivec3(1,  0, -1); *(mesh++) = ivec3(0,  0, -1);
			*(mesh++) = ivec3(0,  0,  0); *(mesh++) = ivec3(1,  0,  0); *(mesh++) = ivec3(1,  0, -1);
			/* Face Upper */
			*(mesh++) = ivec3(1, -1,  0); *(mesh++) = ivec3(0, -1, -1);	*(mesh++) = ivec3(1, -1, -1);
			*(mesh++) = ivec3(1, -1,  0); *(mesh++) = ivec3(0, -1,  0);	*(mesh++) = ivec3(0, -1, -1);

			*(normals++) = ivec3( 0, 0,  1); *(normals++) = ivec3(1,  0,  0); *(normals++) = ivec3(0, 0, -1);
			*(normals++) = ivec3(-1, 0,  0); *(normals++) = ivec3(0, -1,  0); *(normals++) = ivec3(0, 1,  0);

			uvs[TextureID::STONE01] = new vec2[6];
			*(uvs[TextureID::STONE01]++) = texture.getTextureOffset(TextureID::STONE01);
			*(uvs[TextureID::STONE01]++) = texture.getTextureOffset(TextureID::STONE01) + texture.getTexturePercentage();
			*(uvs[TextureID::STONE01]++) = vec2(texture.getTextureOffset(TextureID::STONE01).s, texture.getTextureOffset(TextureID::STONE01).t + texture.getTexturePercentage().t);
			*(uvs[TextureID::STONE01]++) = texture.getTextureOffset(TextureID::STONE01);
			*(uvs[TextureID::STONE01]++) = vec2(texture.getTextureOffset(TextureID::STONE01).s + texture.getTexturePercentage().s, texture.getTextureOffset(TextureID::STONE01).t);
			*(uvs[TextureID::STONE01]++) = texture.getTextureOffset(TextureID::STONE01) + texture.getTexturePercentage();
			uvs[TextureID::STONE01] -= 6;

			uvs[TextureID::STONE02] = new vec2[6];
			*(uvs[TextureID::STONE02]++) = texture.getTextureOffset(TextureID::STONE02);
			*(uvs[TextureID::STONE02]++) = texture.getTextureOffset(TextureID::STONE02) + texture.getTexturePercentage();
			*(uvs[TextureID::STONE02]++) = vec2(texture.getTextureOffset(TextureID::STONE02).s, texture.getTextureOffset(TextureID::STONE02).t + texture.getTexturePercentage().t);
			*(uvs[TextureID::STONE02]++) = texture.getTextureOffset(TextureID::STONE02);
			*(uvs[TextureID::STONE02]++) = vec2(texture.getTextureOffset(TextureID::STONE02).s + texture.getTexturePercentage().s, texture.getTextureOffset(TextureID::STONE02).t);
			*(uvs[TextureID::STONE02]++) = texture.getTextureOffset(TextureID::STONE02) + texture.getTexturePercentage();
			uvs[TextureID::STONE02] -= 6;

			uvs[TextureID::STONE03] = new vec2[6];
			*(uvs[TextureID::STONE03]++) = texture.getTextureOffset(TextureID::STONE03);
			*(uvs[TextureID::STONE03]++) = texture.getTextureOffset(TextureID::STONE03) + texture.getTexturePercentage();
			*(uvs[TextureID::STONE03]++) = vec2(texture.getTextureOffset(TextureID::STONE03).s, texture.getTextureOffset(TextureID::STONE03).t + texture.getTexturePercentage().t);
			*(uvs[TextureID::STONE03]++) = texture.getTextureOffset(TextureID::STONE03);
			*(uvs[TextureID::STONE03]++) = vec2(texture.getTextureOffset(TextureID::STONE03).s + texture.getTexturePercentage().s, texture.getTextureOffset(TextureID::STONE03).t);
			*(uvs[TextureID::STONE03]++) = texture.getTextureOffset(TextureID::STONE03) + texture.getTexturePercentage();
			uvs[TextureID::STONE03] -= 6;

			uvs[TextureID::KIES01] = new vec2[6];
			*(uvs[TextureID::KIES01]++) = texture.getTextureOffset(TextureID::KIES01);
			*(uvs[TextureID::KIES01]++) = texture.getTextureOffset(TextureID::KIES01) + texture.getTexturePercentage();
			*(uvs[TextureID::KIES01]++) = vec2(texture.getTextureOffset(TextureID::KIES01).s, texture.getTextureOffset(TextureID::KIES01).t + texture.getTexturePercentage().t);
			*(uvs[TextureID::KIES01]++) = texture.getTextureOffset(TextureID::KIES01);
			*(uvs[TextureID::KIES01]++) = vec2(texture.getTextureOffset(TextureID::KIES01).s + texture.getTexturePercentage().s, texture.getTextureOffset(TextureID::KIES01).t);
			*(uvs[TextureID::KIES01]++) = texture.getTextureOffset(TextureID::KIES01) + texture.getTexturePercentage();
			uvs[TextureID::KIES01] -= 6;

			uvs[TextureID::GRASS01] = new vec2[6];
			*(uvs[TextureID::GRASS01]++) = texture.getTextureOffset(TextureID::GRASS01);
			*(uvs[TextureID::GRASS01]++) = texture.getTextureOffset(TextureID::GRASS01) + texture.getTexturePercentage();
			*(uvs[TextureID::GRASS01]++) = vec2(texture.getTextureOffset(TextureID::GRASS01).s, texture.getTextureOffset(TextureID::GRASS01).t + texture.getTexturePercentage().t);
			*(uvs[TextureID::GRASS01]++) = texture.getTextureOffset(TextureID::GRASS01);
			*(uvs[TextureID::GRASS01]++) = vec2(texture.getTextureOffset(TextureID::GRASS01).s + texture.getTexturePercentage().s, texture.getTextureOffset(TextureID::GRASS01).t);
			*(uvs[TextureID::GRASS01]++) = texture.getTextureOffset(TextureID::GRASS01) + texture.getTexturePercentage();
			uvs[TextureID::GRASS01] -= 6;

            uvs[TextureID::GRASS02] = new vec2[6];
			*(uvs[TextureID::GRASS02]++) = texture.getTextureOffset(TextureID::GRASS02);
			*(uvs[TextureID::GRASS02]++) = texture.getTextureOffset(TextureID::GRASS02) + texture.getTexturePercentage();
			*(uvs[TextureID::GRASS02]++) = vec2(texture.getTextureOffset(TextureID::GRASS02).s, texture.getTextureOffset(TextureID::GRASS02).t + texture.getTexturePercentage().t);
			*(uvs[TextureID::GRASS02]++) = texture.getTextureOffset(TextureID::GRASS02);
			*(uvs[TextureID::GRASS02]++) = vec2(texture.getTextureOffset(TextureID::GRASS02).s + texture.getTexturePercentage().s, texture.getTextureOffset(TextureID::GRASS02).t);
			*(uvs[TextureID::GRASS02]++) = texture.getTextureOffset(TextureID::GRASS02) + texture.getTexturePercentage();
			uvs[TextureID::GRASS02] -= 6;
            
            uvs[TextureID::GRASS03] = new vec2[6];
			*(uvs[TextureID::GRASS03]++) = texture.getTextureOffset(TextureID::GRASS03);
			*(uvs[TextureID::GRASS03]++) = texture.getTextureOffset(TextureID::GRASS03) + texture.getTexturePercentage();
			*(uvs[TextureID::GRASS03]++) = vec2(texture.getTextureOffset(TextureID::GRASS03).s, texture.getTextureOffset(TextureID::GRASS03).t + texture.getTexturePercentage().t);
			*(uvs[TextureID::GRASS03]++) = texture.getTextureOffset(TextureID::GRASS03);
			*(uvs[TextureID::GRASS03]++) = vec2(texture.getTextureOffset(TextureID::GRASS03).s + texture.getTexturePercentage().s, texture.getTextureOffset(TextureID::GRASS03).t);
			*(uvs[TextureID::GRASS03]++) = texture.getTextureOffset(TextureID::GRASS03) + texture.getTexturePercentage();
			uvs[TextureID::GRASS03] -= 6;
            
            uvs[TextureID::SAND01] = new vec2[6];
			*(uvs[TextureID::SAND01]++) = texture.getTextureOffset(TextureID::SAND01);
			*(uvs[TextureID::SAND01]++) = texture.getTextureOffset(TextureID::SAND01) + texture.getTexturePercentage();
			*(uvs[TextureID::SAND01]++) = vec2(texture.getTextureOffset(TextureID::SAND01).s, texture.getTextureOffset(TextureID::SAND01).t + texture.getTexturePercentage().t);
			*(uvs[TextureID::SAND01]++) = texture.getTextureOffset(TextureID::SAND01);
			*(uvs[TextureID::SAND01]++) = vec2(texture.getTextureOffset(TextureID::SAND01).s + texture.getTexturePercentage().s, texture.getTextureOffset(TextureID::SAND01).t);
			*(uvs[TextureID::SAND01]++) = texture.getTextureOffset(TextureID::SAND01) + texture.getTexturePercentage();
			uvs[TextureID::SAND01] -= 6;
            
            uvs[TextureID::SNOW01] = new vec2[6];
			*(uvs[TextureID::SNOW01]++) = texture.getTextureOffset(TextureID::SNOW01);
			*(uvs[TextureID::SNOW01]++) = texture.getTextureOffset(TextureID::SNOW01) + texture.getTexturePercentage();
			*(uvs[TextureID::SNOW01]++) = vec2(texture.getTextureOffset(TextureID::SNOW01).s, texture.getTextureOffset(TextureID::SNOW01).t + texture.getTexturePercentage().t);
			*(uvs[TextureID::SNOW01]++) = texture.getTextureOffset(TextureID::SNOW01);
			*(uvs[TextureID::SNOW01]++) = vec2(texture.getTextureOffset(TextureID::SNOW01).s + texture.getTexturePercentage().s, texture.getTextureOffset(TextureID::SNOW01).t);
			*(uvs[TextureID::SNOW01]++) = texture.getTextureOffset(TextureID::SNOW01) + texture.getTexturePercentage();
			uvs[TextureID::SNOW01] -= 6;

			mesh -= 36; normals -= 6;
		}

		BlockContext::~BlockContext() {
			delete[] mesh;
			delete[] normals;
			delete[] uvs[TextureID::STONE01];
			delete[] uvs[TextureID::GRASS01];
		}
	}
}