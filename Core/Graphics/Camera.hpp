#pragma once

#include "..\Utils\GL.hpp"
//#include "..\Terrain\Block.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <stdio.h>

namespace Core {
	namespace Terrain {
		class Chunk;
	}
}

namespace Core {
	namespace Graphics {
		using namespace glm;
		
		class Camera
		{
		private:
			GLFWwindow* window;
			bool freeFlight = false;
			int winWidth, winHeight;
			vec3 cameraPosition = vec3(2, -14.2, 2);
			double xCursorPos, yCursorPos;
			mat4 view = mat4(1.0f);
			vec4* planes;

			float jumpTo = -50.f;
			double horizontalAngle = .5f;
			double verticalAngle = -1.0f;
			float mouseSpeed = 4.f;
			float deltaTime = 0.05f;
			float deltaTimeUpdate = 0.0f;
			float mouseSpeedUpdate = 1 / mouseSpeed;
			float deltaTimeAngle = 0.005f;

			mat4 updateFreeFlightCamera();
			mat4 updatePlayerCamera(Terrain::Chunk* currentChunk);
		public:
			Camera(GLFWwindow* window);
			~Camera();
			vec3 getCameraPosition() { return cameraPosition; }
			void setCameraPosition(vec3 position) { cameraPosition = position; }
			double getXCursorPos() const { return xCursorPos; }
			double getYCursorPos() const { return yCursorPos; }
			mat4& updateCamera(Terrain::Chunk* currentChunk);
			vec4* getFrustumPlanes(mat4* projection);
		};
	}

}