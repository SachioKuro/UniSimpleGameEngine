#include "Camera.hpp"
#include "..\Terrain\Chunk.hpp"
#include "..\Terrain\Block.hpp"
namespace Core {
	namespace Graphics {

		Camera::Camera(GLFWwindow* currentWindow)
		{
			window = currentWindow;
			glfwGetWindowSize(window, &winWidth, &winHeight);
		}

		Camera::~Camera()
		{
			delete[] planes;
		}

		mat4& Camera::updateCamera(Terrain::Chunk* currentChunk)
		{
			if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
			{
				freeFlight = !freeFlight;
			}

			if (freeFlight) {
				view = updateFreeFlightCamera();
			}
			else {
				view = updatePlayerCamera(currentChunk);
			}

			glfwSetCursorPos(window, winWidth >> 2, winHeight >> 2);

			return view;
		}

		mat4 Camera::updatePlayerCamera(Terrain::Chunk* currentChunk) {
			if (currentChunk != nullptr) {
				vec3 position = currentChunk->getPosition();
				Terrain::Block**** blocks = currentChunk->getBlocks();

				glm::ivec3 cameraDifference = ivec3(
					(int) (abs(position.x - floor(cameraPosition.x))) % CHUNK_SIZE_X,
					(int) (abs(position.y - floor(abs(cameraPosition.y)))) % CHUNK_SIZE_Y,
					(int) (abs(position.z - floor(cameraPosition.z))) % CHUNK_SIZE_Z
				);

				processGravity(blocks, cameraDifference);

				glfwGetCursorPos(window, &xCursorPos, &yCursorPos);

				// Compute new orientation
				horizontalAngle += mouseSpeed * deltaTimeAngle * float((winWidth >> 2) - xCursorPos);
				verticalAngle += mouseSpeed * deltaTimeAngle * float((winHeight >> 2) - yCursorPos);

				// restrict camera angle so the camera doesn't flip
				if (verticalAngle >= 1) { verticalAngle = 1; }
				else if (verticalAngle <= -1.15) { verticalAngle = -1.15; }

				// Direction : Spherical coordinates to Cartesian coordinates conversion
				glm::vec3 direction = getDirectionVector(horizontalAngle, verticalAngle);

				// Cut out the "y" direction as the play can't walk upwards without jumping
				walkDirection = getWalkDirectionVector(horizontalAngle, verticalAngle);

				// Right vector
				setRightVector(horizontalAngle);
				glm::vec3 right = getRightVector();

				// Up vector : perpendicular to both direction and right
				glm::vec3 up = glm::cross(right, direction);

				// Move forward
				if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
					moveForward(blocks, cameraDifference);
				}
				// Move backward
				else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
					moveBackwards(blocks, cameraDifference);
				}

				// Strafe right
				if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
					strafeRight(blocks, cameraDifference);
				}
				// Strafe left
				else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
					strafeLeft(blocks, cameraDifference);
				}

				if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
					if (jumpTo == JUMP_DEFAULT_VALUE) {
						jumpTo = cameraPosition.y + 1;
					}
				}

				proceedJumpAnimation();

				view = lookAt(cameraPosition, cameraPosition + direction, vec3(0, 1, 0));

			}

			return view;
		}

		void Camera::moveForward(Terrain::Block**** blocks, ivec3 cameraDifference) {
			if (getBlockInFrontOfPlayer(blocks, cameraDifference)->isEnabled() == GL_TRUE) {
				if (abs(walkDirection.x) > abs(walkDirection.z))
				{
					walkDirection.x = 0;
				}
				else {
					walkDirection.z = 0;
				}
			}
#if 0
			if (getBlockLeftOfPlayer(blocks, cameraDifference)->isEnabled() == GL_TRUE) {
				DEBUG(walkDirection.x);
				if (abs(walkDirection.x) > abs(walkDirection.z))
				{
					walkDirection.z = 0;
				}
				else {
					walkDirection.x = 0;
				}
			}

			if (getBlockRightOfPlayer(blocks, cameraDifference)->isEnabled() == GL_TRUE) {
				DEBUG(walkDirection.x);
				if (abs(walkDirection.x) > abs(walkDirection.z))
				{
					walkDirection.z = 0;
				}
				else {
					walkDirection.x = 0;
				}
			}
#endif
			cameraPosition += walkDirection * deltaTime * mouseSpeed;
		}

		void Camera::moveBackwards(Terrain::Block**** blocks, ivec3 cameraDifference) {

			cameraPosition -= walkDirection * deltaTime * mouseSpeed;
		}

		void Camera::strafeLeft(Terrain::Block**** blocks, ivec3 cameraDifference) {
			cameraPosition -= getRightVector() * deltaTime * mouseSpeed;
		}

		void Camera::strafeRight(Terrain::Block**** blocks, ivec3 cameraDifference) {
			cameraPosition += getRightVector() * deltaTime * mouseSpeed;
		}

		void Camera::proceedJumpAnimation() {
			if (cameraPosition.y < jumpTo) {
				float diff = abs(jumpTo - cameraPosition.y);
				cameraPosition.y += 0.1f * 1 / diff;
			}
			else {
				jumpTo = JUMP_DEFAULT_VALUE;
			}
		}

		vec3 Camera::getDirectionVector(float horizontalAngle, float verticalAngle) {
			return vec3(
					cos(verticalAngle) * sin(horizontalAngle),
					sin(verticalAngle),
					cos(verticalAngle) * cos(horizontalAngle)
				);
		}

		vec3 Camera::getWalkDirectionVector(float horizontalAngle, float verticalAngle) {
			return vec3(
					cos(verticalAngle) * sin(horizontalAngle),
					0,
					cos(verticalAngle) * cos(horizontalAngle)
			);
		}

		void Camera::setRightVector(float horizontalAngle) {
			rightVector = glm::vec3(
				sin(horizontalAngle - pi<float>() / 2.0f),
				0,
				cos(horizontalAngle - pi<float>() / 2.0f)
			);
		}

		void Camera::processGravity(Terrain::Block**** blocks, ivec3 cameraDifference) {
			if (getBlockBelowPlayer(blocks, cameraDifference)->isEnabled() == false && jumpTo == JUMP_DEFAULT_VALUE)
			{
				cameraPosition.y -= 0.2f;
			}
		}

		Terrain::Block* Camera::getBlockBelowPlayer(Terrain::Block**** blocks, ivec3 cameraDifference) {
			

			return blocks[cameraDifference.z % CHUNK_SIZE_Z][(cameraDifference.y + 2) % CHUNK_SIZE_Y][cameraDifference.x % CHUNK_SIZE_X];
		}

		Terrain::Block* Camera::getBlockInFrontOfPlayer(Terrain::Block**** blocks, ivec3 cameraDifference) {
			if (abs(walkDirection.x) > abs(walkDirection.z))
			{
				if (cameraDifference.x == CHUNK_SIZE_X - 1) {
					cameraDifference.x -= 1;
				}
				return blocks[cameraDifference.z % CHUNK_SIZE_Z][(cameraDifference.y + 1) % CHUNK_SIZE_Y][(cameraDifference.x + 1) % CHUNK_SIZE_X];
			}

			if (cameraDifference.z == CHUNK_SIZE_Z - 1) {
				cameraDifference.z -= 1;
			}

			return blocks[(cameraDifference.z + 1) % CHUNK_SIZE_Z][(cameraDifference.y + 1) % CHUNK_SIZE_Y][cameraDifference.x % CHUNK_SIZE_X];
		}

		Terrain::Block* Camera::getBlockOfPlayer(Terrain::Block**** blocks, ivec3 cameraDifference) {
			return blocks[cameraDifference.z % CHUNK_SIZE_Z][(cameraDifference.y + 1) % CHUNK_SIZE_Y][cameraDifference.x % CHUNK_SIZE_X];
		}

		Terrain::Block* Camera::getBlockBehindPlayer(Terrain::Block**** blocks, ivec3 cameraDifference) {
			if (abs(walkDirection.x) > abs(walkDirection.z))
			{
				//if (cameraDifference.x == 0) { cameraDifference.x = CHUNK_SIZE_X; }
				//DEBUG_F("%-5f.0 %-5f.0 %-5f.0  \n", cameraDifference.z, (cameraDifference.y + 1) % CHUNK_SIZE_Y, cameraDifference.x - 1);
				return blocks[cameraDifference.z][(cameraDifference.y + 1) % CHUNK_SIZE_Y][(cameraDifference.x - 1) % CHUNK_SIZE_X];
			}

			return blocks[((cameraDifference.z - 1) % CHUNK_SIZE_Z) % CHUNK_SIZE_Z][(cameraDifference.y + 1) % CHUNK_SIZE_Y][cameraDifference.x];
		}

		Terrain::Block* Camera::getBlockLeftOfPlayer(Terrain::Block**** blocks, ivec3 cameraDifference) {
			if (abs(walkDirection.x) > abs(walkDirection.z))
			{
				int positionZ;
				if (walkDirection.x > 0)
				{
					positionZ = cameraDifference.z + 1;
				}
				else {
					positionZ = cameraDifference.z - 1;
				}

				return blocks[positionZ % CHUNK_SIZE_Z][(cameraDifference.y + 1) % CHUNK_SIZE_Y][cameraDifference.x % CHUNK_SIZE_X];
			}
			else {
				int positionX;
				if (walkDirection.z > 0)
				{
					positionX = cameraDifference.x + 1;
				}
				else {
					positionX = cameraDifference.x - 1;
				}

				//DEBUG_F("%i %i %i \n", cameraDifference.x, cameraDifference.y, cameraDifference.z);
				//DEBUG_F("%i %i %i \n", positionX, cameraDifference.y + 1, cameraDifference.z);

				return blocks[cameraDifference.z % CHUNK_SIZE_Z][(cameraDifference.y + 1) % CHUNK_SIZE_Y][positionX % CHUNK_SIZE_X];
			}
		}

		Terrain::Block* Camera::getBlockRightOfPlayer(Terrain::Block**** blocks, ivec3 cameraDifference) {
			if (abs(walkDirection.x) > abs(walkDirection.z))
			{
				int positionZ;
				if (walkDirection.x > 0)
				{
					positionZ = cameraDifference.z - 1;
				}
				else {
					positionZ = cameraDifference.z + 1;
				}
				return blocks[positionZ % CHUNK_SIZE_Z][(cameraDifference.y + 1) % CHUNK_SIZE_Y][cameraDifference.x % CHUNK_SIZE_X];
			}
			else {
				int positionX;
				if (walkDirection.z > 0)
				{
					positionX = cameraDifference.x - 1;
				}
				else {
					positionX = cameraDifference.x + 1;
				}
				DEBUG_F("%d %d %f \n", positionX, cameraDifference.y + 1, cameraDifference.z);

				return blocks[cameraDifference.z % CHUNK_SIZE_Z][(cameraDifference.y + 1) % CHUNK_SIZE_Y][positionX % CHUNK_SIZE_X];
			}

		}

		mat4 Camera::updateFreeFlightCamera() {
			glfwGetCursorPos(window, &xCursorPos, &yCursorPos);

			// Compute new orientation
			horizontalAngle += mouseSpeed * deltaTimeAngle * float((winWidth >> 2) - xCursorPos);
			verticalAngle += mouseSpeed * deltaTimeAngle * float((winHeight >> 2) - yCursorPos);

			// restrict camera angle so the camera doesn't flip
			if (verticalAngle >= 1) { verticalAngle = 1; }
			else if (verticalAngle <= -1.15) { verticalAngle = -1.15; }

			// Direction : Spherical coordinates to Cartesian coordinates conversion
			glm::vec3 direction(
				cos(verticalAngle) * sin(horizontalAngle),
				sin(verticalAngle),
				cos(verticalAngle) * cos(horizontalAngle)
				);

			walkDirection = vec3(
				cos(verticalAngle) * sin(horizontalAngle),
				sin(verticalAngle),
				cos(verticalAngle) * cos(horizontalAngle)
				);

			// Right vector
			rightVector = glm::vec3(
				sin(horizontalAngle - pi<float>() / 2.0f),
				0,
				cos(horizontalAngle - pi<float>() / 2.0f)
				);

			// Up vector : perpendicular to both direction and right
			glm::vec3 up = glm::cross(rightVector, direction);

			//deltaTimeUpdate += deltaTime;

			//if (deltaTimeUpdate > mouseSpeedUpdate) {
			// Move forward

			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
						cameraPosition += walkDirection * deltaTime * mouseSpeed;
			}
			// Move backward
			else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
				cameraPosition -= walkDirection * deltaTime * mouseSpeed;
			}

			// Strafe right
			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
				cameraPosition += rightVector * deltaTime * mouseSpeed;
			}
			// Strafe left
			else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
				cameraPosition -= rightVector * deltaTime * mouseSpeed;
			}

			view = lookAt(cameraPosition, cameraPosition + direction, vec3(0, 1, 0));

			return view;
		}

		/* With help of the paper:
		http://gamedevs.org/uploads/fast-extraction-viewing-frustum-planes-from-world-view-projection-matrix.pdf */
		vec4* Camera::getFrustumPlanes(mat4* projection) {
			mat4 pv = *projection * view;
			vec4 vX = row(pv, 0), vY = row(pv, 1), vZ = row(pv, 2), vW = row(pv, 3);
			
			planes = new vec4[6];

			planes[0] = normalize(vW + vX); planes[1] = normalize(vW - vX);
			planes[2] = normalize(vW + vY);	planes[3] = normalize(vW - vY);
			planes[4] = normalize(vW + vZ);	planes[5] = normalize(vW - vZ);

			for (int i = 0; i < 6; i++)
				planes[i] = -planes[i] / length(vec3(planes[i].x, planes[i].y, planes[i].z));

			return planes;
		}
	}
}