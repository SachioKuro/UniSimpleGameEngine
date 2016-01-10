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
		}

		mat4& Camera::updateCamera()
		{
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

			// Right vector
			glm::vec3 right = glm::vec3(
				sin(horizontalAngle - pi<float>() / 2.0f),
				0,
				cos(horizontalAngle - pi<float>() / 2.0f)
				);

			// Up vector : perpendicular to both direction and right
			glm::vec3 up = glm::cross(right, direction);

			// Move forward
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
				cameraPosition += direction * deltaTime * mouseSpeed;
			}

			// Move backward
			else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
				cameraPosition -= direction * deltaTime * mouseSpeed;
			}

			// Strafe right
			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
				cameraPosition += right * deltaTime * mouseSpeed;
			}

			// Strafe left
			else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
				cameraPosition -= right * deltaTime * mouseSpeed;
			}
			
			
			view = lookAt(cameraPosition, cameraPosition + direction, vec3(0, 1, 0));

			//setCameraPosition(cameraPosition);
			glfwSetCursorPos(window, winWidth >> 2, winHeight >> 2);

			return view;
		}

	}
}