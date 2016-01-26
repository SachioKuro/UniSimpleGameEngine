#include "Camera.hpp"

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
			glfwGetCursorPos(window, &xCursorPos, &yCursorPos);

			// Compute new orientation
			horizontalAngle += mouseSpeed * deltaTimeAngle * float((winWidth >> 2) - xCursorPos);
			verticalAngle += mouseSpeed * deltaTimeAngle * float((winHeight >> 2) - yCursorPos);

			// restrict camera angle so the camera doesn't flip
			if (verticalAngle >= 1) { verticalAngle = 1; } else if (verticalAngle <= -1.15) { verticalAngle = -1.15; }

			// Direction : Spherical coordinates to Cartesian coordinates conversion
			glm::vec3 direction(
				cos(verticalAngle) * sin(horizontalAngle),
				sin(verticalAngle),
				cos(verticalAngle) * cos(horizontalAngle)
				);

			glm::vec3 walkDirection(
				cos(verticalAngle) * sin(horizontalAngle),
				0,
				cos(verticalAngle) * cos(horizontalAngle)
				);

			// Right vector
			glm::vec3 right = glm::vec3(
				sin(horizontalAngle - pi<float>() / 2.0f),
				0,
				cos(horizontalAngle - pi<float>() / 2.0f)
				);

			// Up vector : perpendicular to both direction and right
			glm::vec3 up = glm::cross(right, direction);

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
					cameraPosition += right * deltaTime * mouseSpeed;
				}
				// Strafe left
				else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
					cameraPosition -= right * deltaTime * mouseSpeed;
				}

				if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
					if (jumpTo == -50.f) {
						jumpTo = cameraPosition.y + 1;
					}
				}

				if (cameraPosition.y < jumpTo) {
					cameraPosition.y += 0.1f;
				}
				else {
					jumpTo = -50.f;
				}

				//deltaTimeUpdate = 0.0f;
			//}

			view = lookAt(cameraPosition, cameraPosition + direction, vec3(0, 1, 0));

			glfwSetCursorPos(window, winWidth >> 2, winHeight >> 2);

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