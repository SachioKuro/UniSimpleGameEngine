#include "SkyboxBlock.hpp"

namespace Core {
	namespace Terrain {
		SkyboxBlock::SkyboxBlock(SkyType stype, RenderMode mode) 
			: stype(stype), Drawable(mode, ivec3(0), TextureID::NONE, vec2(1, 1), 36) {
			

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