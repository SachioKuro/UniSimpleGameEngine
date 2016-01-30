#include "WaterFBO.hpp"

namespace Core {
	namespace Graphics {
		WaterFBO::WaterFBO() {
			glGenFramebuffers(1, &reflectionFBO);
			glBindFramebuffer(GL_FRAMEBUFFER, reflectionFBO);
			glDrawBuffer(GL_COLOR_ATTACHMENT0);

			glGenTextures(1, &reflectionTexture);
			glBindTexture(GL_TEXTURE_2D, reflectionTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, REFLECTION_WIDTH, REFLECTION_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, reflectionTexture, 0);

			glGenRenderbuffers(1, &reflectionDepthBuffer);
			glBindRenderbuffer(GL_RENDERBUFFER, reflectionDepthBuffer);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, REFLECTION_WIDTH, REFLECTION_HEIGHT);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, reflectionDepthBuffer);
			
			glGenFramebuffers(1, &refractionFBO);
			glBindFramebuffer(GL_FRAMEBUFFER, refractionFBO);
			glDrawBuffer(GL_COLOR_ATTACHMENT0);

			glGenTextures(1, &refractionTexture);
			glBindTexture(GL_TEXTURE_2D, refractionFBO);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, REFRACTION_WIDTH, REFRACTION_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, refractionFBO, 0);

			glGenTextures(1, &refractionDepthTexture);
			glBindTexture(GL_TEXTURE_2D, refractionDepthTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, REFRACTION_WIDTH, REFRACTION_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, (void*)NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
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