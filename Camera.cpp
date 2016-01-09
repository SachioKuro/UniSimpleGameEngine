#include "Camera.hpp"

namespace Core {
	namespace Graphics {

		Camera::Camera(GLFWwindow* currentWindow)
		{
			window = currentWindow;
		}

		Camera::~Camera()
		{
		}

		mat4 Camera::updateCamera()
		{
			glfwGetCursorPos(window, &xCursorPos, &yCursorPos);
			
			// Compute new orientation
			double horizontalAngle = 0.0f;
			double verticalAngle = 0.0f;
			float mouseSpeed = 2.0f;
			float deltaTime = 0.05f;
			horizontalAngle += mouseSpeed * deltaTime / 10 * float(1024 / 2 - xCursorPos);
			verticalAngle += mouseSpeed * deltaTime / 10 * float(768 / 2 - yCursorPos);

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
				sin(horizontalAngle - 3.14f / 2.0f),
				0,
				cos(horizontalAngle - 3.14f / 2.0f)
				);

			// Up vector : perpendicular to both direction and right
			glm::vec3 up = glm::cross(right, direction);

			// Move forward
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
				cameraPosition += direction * deltaTime * mouseSpeed;
			}

			// Move backward
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
				cameraPosition -= direction * deltaTime * mouseSpeed;
			}

			// Strafe right
			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
				cameraPosition += right * deltaTime * mouseSpeed;
			}

			// Strafe left
			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
				cameraPosition -= right * deltaTime * mouseSpeed;
			}

			setCameraPosition(cameraPosition);

			view = lookAt(cameraPosition, cameraPosition + direction, vec3(0, 1, 0));

			return view;
		}

	}
}