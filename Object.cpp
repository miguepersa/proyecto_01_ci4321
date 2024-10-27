#include "Object.h"

Object::Object(Mesh& mesh) : mesh(mesh)
{
}

void Object::HandleInput(GLFWwindow* window, glm::vec3 Orientation, float currentTime) {

	deltaTime = currentTime - prevTime;
	prevTime = currentTime;
	realSpeed = speed * deltaTime;
	mesh.Orientation = glm::normalize(Orientation);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

		mesh.Position += realSpeed * glm::vec3(mesh.Orientation.x, 0.0f, mesh.Orientation.z);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {

		mesh.Position += realSpeed * -glm::normalize(glm::cross(mesh.Orientation, Up));
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

		mesh.Position += realSpeed * -glm::vec3(mesh.Orientation.x, 0.0f, mesh.Orientation.z);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {

		mesh.Position += realSpeed * glm::normalize(glm::cross(mesh.Orientation, Up));
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {

		mesh.Position += realSpeed * Up;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {

		if (mesh.Position.y >= 0.5f) mesh.Position += realSpeed * -Up;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {

		speed = 15.0f;

	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {

		speed = 5.0f;
	}

}