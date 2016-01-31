#include "SkyboxBlock.hpp"

namespace Core {
	namespace Terrain {
		SkyboxBlock::SkyboxBlock(SkyType stype) 
			: stype(stype), Drawable(glm::ivec3(0), Graphics::TextureID::NONE, glm::vec2(1, 1), 36) {
			// Setup renderer
			renderer = new Graphics::Renderer(1, 36);
			renderer->useShader(Graphics::Shader::Sky);
		}

		SkyboxBlock::~SkyboxBlock() {
			delete renderer;
		}

		void SkyboxBlock::draw(glm::vec3& position, glm::mat4& view, glm::mat4& projection, Graphics::Camera* camera) {
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
			renderer->getActiveShader()->setUniformInteger("FreeFlight", (int)camera->isFreeFlight());
			renderer->getActiveShader()->setUniformInteger("UnderWater", (int)(-(CHUNK_SIZE_Y - WATERLEVEL) > camera->getCameraPosition().y));
			// Don't check for depth
			glDepthMask(GL_FALSE);
			renderer->start();
			// Submit Skybox
			renderer->submit((Drawable*)this, &context);
			// Ready for render
			renderer->end();
			// Starts rendering
			renderer->draw();
			glDepthMask(GL_TRUE);
			renderer->deactivateShader();
		}
	}
}