#pragma once

#include "..\Utils\GL.hpp"
//#include "..\Terrain\Block.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <stdio.h>

#define JUMP_DEFAULT_VALUE -50.0f

namespace Core {
	namespace Terrain {
		class Chunk;
		class Block;
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

			float jumpTo = JUMP_DEFAULT_VALUE;
			double horizontalAngle = .5f;
			double verticalAngle = -1.0f;
			float mouseSpeed = 4.f;
			float deltaTime = 0.05f;
			float deltaTimeUpdate = 0.0f;
			float mouseSpeedUpdate = 1 / mouseSpeed;
			float deltaTimeAngle = 0.005f;
			vec3 rightVector;
			vec3 walkDirection;
			vec3 getDirectionVector(float horizontalAngle, float verticalAngle);
			vec3 getWalkDirectionVector(float horizontalAngle, float verticalAngle);
			void setRightVector(float horizontalAngle);
			vec3 getRightVector() { return rightVector; }

			void strafeLeft(Terrain::Block**** blocks, ivec3 cameraDifference);
			void strafeRight(Terrain::Block**** blocks, ivec3 cameraDifference);
			void moveForward(Terrain::Block**** blocks, ivec3 cameraDifference);
			void moveBackwards(Terrain::Block**** blocks, ivec3 cameraDifference);

			void proceedJumpAnimation();

			void processGravity(Terrain::Block**** blocks, ivec3 cameraDifference);
			Terrain::Block *getBlockBelowPlayer(Terrain::Block**** blocks, ivec3 cameraDifference);
			Terrain::Block *getBlockOfPlayer(Terrain::Block**** blocks, ivec3 cameraDifference);
			Terrain::Block *getBlockInFrontOfPlayer(Terrain::Block**** blocks, ivec3 cameraDifference);
			Terrain::Block *getBlockBehindPlayer(Terrain::Block**** blocks, ivec3 cameraDifference);
			Terrain::Block *getBlockLeftOfPlayer(Terrain::Block**** blocks, ivec3 cameraDifference);
			Terrain::Block *getBlockRightOfPlayer(Terrain::Block**** blocks, ivec3 cameraDifference);

			mat4 updateFreeFlightCamera();
			mat4 updatePlayerCamera(Terrain::Chunk* currentChunk);
		public:
			Camera(GLFWwindow* window);
			~Camera();
			vec3 getCameraPosition() { return cameraPosition; }
			void setCameraPosition(vec3 position) { cameraPosition = position; }
			vec3 getWalkDirection() { return walkDirection; }
			double getXCursorPos() const { return xCursorPos; }
			double getYCursorPos() const { return yCursorPos; }
			mat4& updateCamera(Terrain::Chunk* currentChunk);
			vec4* getFrustumPlanes(mat4* projection);
		};
	}

}