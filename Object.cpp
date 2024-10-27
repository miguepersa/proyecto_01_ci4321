#include "Object.h"
#include <cmath>  // For M_PI constant

Object::Object(Mesh& mesh) : mesh(mesh), tankRotationY(0.0f) {
}

void Object::HandleInput(GLFWwindow* window, glm::vec3 cameraOrientation, float currentTime, int windowWidth, int windowHeight) {

    // Initialize rotation angle for the tank
    static float tankRotationY = 0.0f;
    const float PI = 3.14159265358979323846;  // Define M_PI constant if missing

    // Calculate deltaTime for smooth movement
    deltaTime = currentTime - prevTime;
    prevTime = currentTime;
    realSpeed = speed * deltaTime;

    // Rotate the tank with A and D keys
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        tankRotationY += 90.0f * deltaTime;  // Rotate left
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        tankRotationY -= 90.0f * deltaTime;  // Rotate right
    }

    // Calculate forward direction based on tank's rotation
    glm::vec3 forwardDir = glm::vec3(sin(glm::radians(tankRotationY)), 0.0f, cos(glm::radians(tankRotationY)));

    // Move tank forward and backward with W and S keys
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        mesh.Position += realSpeed * forwardDir;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        mesh.Position -= realSpeed * forwardDir;
    }

    // Update the tank's orientation based on rotation
    mesh.Orientation = glm::vec3(sin(glm::radians(tankRotationY)), 0.0f, cos(glm::radians(tankRotationY)));

    // Mouse position capture
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    // Convert mouse position to normalized device coordinates (NDC)
    float normalizedMouseX = (2.0f * mouseX) / windowWidth - 1.0f;
    float normalizedMouseY = 1.0f - (2.0f * mouseY) / windowHeight;

    // Calculate world direction vector from tank position to projected mouse position
    glm::vec3 mouseWorldPos = glm::vec3(normalizedMouseX, 0.0f, normalizedMouseY);
    glm::vec3 directionToMouse = glm::normalize(mouseWorldPos - mesh.Position);

    // Calculate angle for turret rotation using atan2
    float turretRotation = atan2(directionToMouse.x, directionToMouse.z) * (180.0f / PI);

    // Store the turret rotation in the Object if Mesh lacks TurretOrientation
    this->turretRotationAngle = turretRotation;

    // Additional input handling (optional) for altitude control and speed boost
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
