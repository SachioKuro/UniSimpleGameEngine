#pragma once

#include "..\Utils\GL.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

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
			vec4* planes;

			double horizontalAngle = 0.0f;
			double verticalAngle = 0.0f;
			float mouseSpeed = 4.f;
			float deltaTime = 0.05f;
			float deltaTimeUpdate = 0.0f;
			float mouseSpeedUpdate = 1 / mouseSpeed;
			float deltaTimeAngle = 0.005f;
		public:
			Camera(GLFWwindow* window);
			~Camera();
			vec3 getCameraPosition() { return cameraPosition; }
			void setCameraPosition(vec3 position) { cameraPosition = position; }
			double getXCursorPos() const { return xCursorPos; }
			double getYCursorPos() const { return yCursorPos; }
			mat4& updateCamera();
			vec4* getFrustumPlanes(mat4* projection);
		};
	}

}