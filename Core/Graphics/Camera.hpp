#pragma once

#include "..\Utils\GL.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Core {
	namespace Graphics {
		using namespace glm;

		class Camera
		{
		private:
			GLFWwindow* window;
			int winWidth, winHeight;
			vec3 cameraPosition = vec3(1, 1, 1);
			double xCursorPos, yCursorPos;
			mat4 view = mat4(1.0f);

			double horizontalAngle = 0.0f;
			double verticalAngle = 0.0f;
			float mouseSpeed = 2.0f;
			float deltaTime = 0.05f;
			float deltaTimeAngle = 0.005f;
		public:
			Camera(GLFWwindow* window);
			~Camera();
			vec3 getCameraPosition() { return cameraPosition; }
			void setCameraPosition(vec3 position) { cameraPosition = position; }
			double getXCursorPos() const { return xCursorPos; }
			double getYCursorPos() const { return yCursorPos; }
			mat4& updateCamera();
		};
	}

}