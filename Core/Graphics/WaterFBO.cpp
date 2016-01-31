#include "WaterFBO.hpp"

namespace Core {
	namespace Graphics {
		WaterFBO::WaterFBO() {
			/* Generate the Framebuffer for the reflection */
			glGenFramebuffers(1, &reflectionFBO);
			glBindFramebuffer(GL_FRAMEBUFFER, reflectionFBO);
			/* Use the 0. Colorbuffer as attachment */
			glDrawBuffer(GL_COLOR_ATTACHMENT0);

			/* Generate the reflectiontexture */
			glGenTextures(1, &reflectionTexture);
			glBindTexture(GL_TEXTURE_2D, reflectionTexture);
			/* Reserves Memory for the Texture */
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, REFLECTION_WIDTH, REFLECTION_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)NULL);
			/* Set Filter Options */
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			/* Bind the 0. Colorbuffer to the Framebuffer */
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, reflectionTexture, 0);

			/* Generate the Depthbuffer for the reflection */
			glGenRenderbuffers(1, &reflectionDepthBuffer);
			glBindRenderbuffer(GL_RENDERBUFFER, reflectionDepthBuffer);
			/* Reserves Memory for the Depthbuffer */
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, REFLECTION_WIDTH, REFLECTION_HEIGHT);
			/* Attach the Depthbuffer to the Framebuffer */
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, reflectionDepthBuffer);

			/* Generate the Framebuffer for the refraction */
			glGenFramebuffers(1, &refractionFBO);
			glBindFramebuffer(GL_FRAMEBUFFER, refractionFBO);
			/* Use the 0. Colorbuffer as attachment */
			glDrawBuffer(GL_COLOR_ATTACHMENT0);

			/* Generate the reflectiontexture */
			glGenTextures(1, &refractionTexture);
			glBindTexture(GL_TEXTURE_2D, refractionFBO);
			/* Reserves Memory for the Texture */
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, REFRACTION_WIDTH, REFRACTION_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)NULL);
			/* Set Filter Options */
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			/* Bind the 0. Colorbuffer to the Framebuffer */
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, refractionFBO, 0);

			/* Generate the reflectiondepthtexture */
			glGenTextures(1, &refractionDepthTexture);
			glBindTexture(GL_TEXTURE_2D, refractionDepthTexture);
			/* Reserves Memory for the Texture */
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, REFRACTION_WIDTH, REFRACTION_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, (void*)NULL);
			/* Set Filter Options */
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			/* Bind the 0. depthbuffer to the Framebuffer */
			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, refractionDepthTexture, 0);
			
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		WaterFBO::~WaterFBO() {
			glDeleteFramebuffers(1, &reflectionFBO);
			glDeleteFramebuffers(1, &refractionFBO);
			glDeleteTextures(1, &reflectionTexture);
			glDeleteTextures(1, &refractionTexture);
			glDeleteTextures(1, &refractionDepthTexture);
			glDeleteRenderbuffers(1, &reflectionDepthBuffer);
		}

		void WaterFBO::bindReflectionFBO() {
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindFramebuffer(GL_FRAMEBUFFER, reflectionFBO);
			glViewport(0, 0, REFLECTION_WIDTH, REFLECTION_HEIGHT);
		}
		void WaterFBO::bindRefractionFBO() {
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindFramebuffer(GL_FRAMEBUFFER, refractionFBO);
			glViewport(0, 0, REFRACTION_WIDTH, REFRACTION_HEIGHT);
		}
		void WaterFBO::unbindFBO() {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0, 0, 1200, 800);

		}
	}
}