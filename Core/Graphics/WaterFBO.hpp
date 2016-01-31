#pragma once

#include "../Utils/GL.hpp"

#define REFLECTION_WIDTH  320
#define REFLECTION_HEIGHT 180
#define REFRACTION_WIDTH  1280
#define REFRACTION_HEIGHT 720

namespace Core {
	namespace Graphics {
		/* Framebuffer for the Watertexture (Not in use at the moment) */
		class WaterFBO {
		private:
			GLuint reflectionFBO, refractionFBO;
			GLuint reflectionTexture, refractionTexture;
			GLuint reflectionDepthBuffer;
			GLuint refractionDepthTexture;
		public:
			WaterFBO();
			~WaterFBO();
			GLuint getReflectionTexture()		{ return reflectionTexture; }
			GLuint getRefractionTexture()		{ return refractionTexture; }
			GLuint getRefractionDepthTexture()  { return refractionDepthTexture; }
			void bindReflectionFBO();
			void bindRefractionFBO();
			void unbindFBO();
		};
	}
}