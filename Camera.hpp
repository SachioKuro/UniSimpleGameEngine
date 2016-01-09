#pragma once

#include "Core\Utils\GL.hpp"
#include "Core\Graphics\Window.hpp"

namespace Core {
	namespace Graphics {
		using namespace glm;

		class Camera
		{
		private:
			GLFWwindow* window;
			vec3 cameraPosition = vec3(1, 1, 1);
			double xCursorPos, yCursorPos;
			glm::mat4 view = mat4(1.0f);
		public:
			Camera(GLFWwindow* window);
			~Camera();
			vec3 getCameraPosition() { return cameraPosition; }
			void setCameraPosition(vec3 position) { cameraPosition = position; }
			double getXCursorPos() const { return xCursorPos; }
			double getYCursorPos() const { return yCursorPos; }
			mat4 updateCamera();
		};
	}

}