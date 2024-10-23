#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Texture.h"
#include "Camera.h"

const unsigned int windowWidth = 800;
const unsigned int windowHeight = 800;


// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		1.0f,	0.0f,		0.0f, -1.0f,  0.0f, // bottom side
	-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		1.0f,	1.0f,		0.0f, -1.0f,  0.0f, // bottom side
	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		0.0f,	1.0f,		0.0f, -1.0f,  0.0f, // bottom side
	 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		0.0f,	0.0f,		0.0f, -1.0f,  0.0f, // bottom side
	
	-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		0.0f,	0.0f,		0.0f,  0.0f,  1.0f, // back side
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		1.0f,	1.0f,		0.0f,  0.0f,  1.0f,	// back side
	-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		0.0f,	1.0f,		0.0f,  0.0f,  1.0f,	// back side
	 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		1.0f,	0.0f,		0.0f,  0.0f,  1.0f,	// back side

	 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		0.0f,	0.0f,		1.0f,  0.0f,  0.0f, // right side
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		0.0f,	1.0f,		1.0f,  0.0f,  0.0f,	// right side
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		1.0f,	1.0f,		1.0f,  0.0f,  0.0f,	// right side
	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		1.0f,	0.0f,		1.0f,  0.0f,  0.0f,	// right side

	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		0.0f,	0.0f,		0.0f,  0.0f, -1.0f, // front side
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		0.0f,	1.0f,		0.0f,  0.0f, -1.0f,	// front side
	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		1.0f,	1.0f,		0.0f,  0.0f, -1.0f,	// front side
	-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		1.0f,	0.0f,		0.0f,  0.0f, -1.0f,	// front side
	 
	-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		0.0f,	0.0f,	   -1.0f,  0.0f,  0.0f, // left side
	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		0.0f,	1.0f,	   -1.0f,  0.0f,  0.0f,	// left side
	-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		1.0f,	1.0f,	   -1.0f,  0.0f,  0.0f,	// left side
	-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		1.0f,	0.0f,	   -1.0f,  0.0f,  0.0f,	// left side

	-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		0.0f,	0.0f,	    0.0f,  1.0f,  0.0f, // top side
	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		0.0f,	1.0f,	    0.0f,  1.0f,  0.0f,	// top side
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		1.0f,	1.0f,	    0.0f,  1.0f,  0.0f,	// top side
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		1.0f,	0.0f,	    0.0f,  1.0f,  0.0f,	// top side
};

// Indices for vertices order
GLuint indices[] =
{
	 0,		 1,		 2, // bottom side
	 0,		 2,		 3, // bottom side

	 4,		 5,		 6, // back side
	 4,		 7,		 5, // back side

	 8,		 9,		10, // right side
	 8,		10,		11, // right side

	12,		13,		14, // front side
	12,		14,		15, // front side

	16,		17,		18, // left side
	16,		18,		19, // left side

	20,		21,		22, // top side
	20,		22,		23, // top side
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,

	0, 4, 7,
	0, 7, 3,

	3, 7, 6,
	3, 6, 2,

	2, 6, 5,
	2, 5, 1,

	1, 5, 4,
	1, 4, 0,

	4, 5, 6,
	4, 6, 7
};

int main() {

	// GLFW Initialization
	glfwInit();

	// OpenGL version setup for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Selecting core profile for OpenGL in GLFW
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window instantiation
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "OpenGL", NULL, NULL);

	// Window error check
	if (window == NULL) {
		std::cout << "Error" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Add the window to the context
	glfwMakeContextCurrent(window);

	// glad init
	gladLoadGL();

	// Specifying the viewport of OpenGL in the window
	// (0, 0) -> (800, 800)
	glViewport(0, 0, windowWidth, windowHeight);

	// Generate shader program
	Shader shaderProgram("default.vert", "default.frag");

	// Create vertex array object
	VertexArray vertexArray;
	vertexArray.Bind();

	// Create vertex buffer object
	VertexBuffer vertexBuffer(vertices, sizeof(vertices));
	ElementBuffer elementBuffer(indices, sizeof(indices));

	// Link vertex buffer and array
	vertexArray.linkAttrib(vertexBuffer, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*) 0);
	vertexArray.linkAttrib(vertexBuffer, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	vertexArray.linkAttrib(vertexBuffer, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	vertexArray.linkAttrib(vertexBuffer, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	// Unbind vertex array, vertex buffer and element buffer
	vertexArray.Unbind();
	vertexBuffer.Unbind();
	elementBuffer.Unbind();

	// Light Shader
	Shader lightShader("light.vert", "light.frag");

	VertexArray lightVertexArray;
	lightVertexArray.Bind();

	VertexBuffer lightVertexBuffer(lightVertices, sizeof(lightVertices));
	ElementBuffer lightElementBuffer(lightIndices, sizeof(lightIndices));

	lightVertexArray.linkAttrib(lightVertexBuffer, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	lightVertexArray.Unbind();
	lightVertexBuffer.Unbind();
	lightElementBuffer.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 objPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objModel = glm::mat4(1.0f);
	objModel = glm::translate(objModel, objPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	// Texture
	Texture berkano("b2.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	berkano.texUnit(shaderProgram, "tex0", 0);

	// Deltatime = crntTime - prevTime

	// Enable depth buffer
	glEnable(GL_DEPTH_TEST);

	Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 2.0f));

	// Main loop
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// Clean back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		
		// Activate shader program
		shaderProgram.Activate();
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");

		berkano.Bind();

		// Bind the vertex array to the program
		vertexArray.Bind();

		// Drawing the triangle
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		lightVertexArray.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// Flip
		glfwSwapBuffers(window);

		// Calling of the update function
		glfwPollEvents();
	}

	// Deleting remaining objects 
	vertexArray.Delete();
	vertexBuffer.Delete();
	elementBuffer.Delete();
	shaderProgram.Delete();
	berkano.Delete();

	lightVertexArray.Delete();
	lightVertexBuffer.Delete();
	lightElementBuffer.Delete();
	lightShader.Delete();

	// Window closing
	glfwDestroyWindow(window);
	
	// GLFW closing
	glfwTerminate();

	return 0;
}