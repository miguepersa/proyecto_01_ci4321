#ifndef OBJECT_H
#define OBJECT_H

#include "Mesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtx/vector_angle.hpp>#include <glad/glad.h>

class Object {
	
	public:
		Mesh mesh;
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 Position;
		glm::vec3 GetPosition() const { return Position; };
		float turretRotationAngle;
		float tankRotationY;
		bool firstClick = true;
		float speed = 5.0f;
		float prevTime = 0.0f;
		float deltaTime = 0.0f;
		float realSpeed = 0.0f;
		
		Object(Mesh& mesh);
		void HandleInput(GLFWwindow* window, glm::vec3 Orientation, float currentTime, int windowWidth, int windowHeight);

};

#endif