#include "Mesh.h"

const unsigned int windowWidth = 1000;
const unsigned int windowHeight = 1000;

float skyboxVertices[] =
{
	//   Coordinates
	-1.0f, -1.0f,  1.0f,//        7--------6
	 1.0f, -1.0f,  1.0f,//       /|       /|
	 1.0f, -1.0f, -1.0f,//      4--------5 |
	-1.0f, -1.0f, -1.0f,//      | |      | |
	-1.0f,  1.0f,  1.0f,//      | 3------|-2
	 1.0f,  1.0f,  1.0f,//      |/       |/
	 1.0f,  1.0f, -1.0f,//      0--------1
	-1.0f,  1.0f, -1.0f
};

unsigned int skyboxIndices[] =
{
	// Right
	1, 2, 6,
	6, 5, 1,
	// Left
	0, 4, 7,
	7, 3, 0,
	// Top
	4, 5, 6,
	6, 7, 4,
	// Bottom
	0, 3, 2,
	2, 1, 0,
	// Back
	0, 1, 5,
	5, 4, 0,
	// Front
	3, 7, 6,
	6, 2, 3
};

Vertex floorVertices[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
	Vertex{glm::vec3(-20.0f, 0.0f,  20.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-20.0f, 0.0f, -20.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 20.0f, 0.0f, -20.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3( 20.0f, 0.0f,  20.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

// Indices for vertices order
GLuint floorIndices[] =
{
	0, 1, 2,
	0, 2, 3
};

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
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

	Texture floorTextures[]
	{
		Texture("sand-ground-textured.jpg", "diffuse", 0)

	};

	// Generate shader program
	Shader shaderProgram("default.vert", "default.frag");

	std::vector<Vertex> floorVerts(floorVertices, floorVertices + sizeof(floorVertices) / sizeof(Vertex));
	std::vector<GLuint> floorInd(floorIndices, floorIndices + sizeof(floorIndices) / sizeof(GLuint));
	std::vector<Texture> floorTex(floorTextures, floorTextures + sizeof(floorTextures) / sizeof(floorTextures));

	Mesh floor(floorVerts, floorInd, floorTex);

	// Light Shader
	Shader lightShader("light.vert", "light.frag");
	std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector<GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint) );
	Mesh light(lightVerts, lightInd, floorTex);
	
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(1.0f, 10.0f, 1.0f);
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

	// Deltatime = crntTime - prevTime

	// Enable depth buffer
	glEnable(GL_DEPTH_TEST);

	Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.5f, 0.0f));

	double prevTime = 0.0;
	double currentTime = 0.0;
	double deltaTime;

	unsigned int counter = 0;

	glfwSwapInterval(1);

	// Main loop
	while (!glfwWindowShouldClose(window)) 
	{

		currentTime = glfwGetTime();
		deltaTime = currentTime - prevTime;
		counter++;
		if (deltaTime >= 1.0 / 30.0)
		{
			std::string FPS = std::to_string((1.0 / deltaTime) * counter);
			std::string ms = std::to_string((deltaTime / counter) * 1000);
			std::string windowTitle = "TankWars - " + FPS + "FPS / " + ms + "ms";
			glfwSetWindowTitle(window, windowTitle.c_str());
			prevTime = currentTime;
			counter = 0;
		}

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// Clean back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		floor.Draw(shaderProgram, camera);
		light.Draw(lightShader, camera);
		
		// Flip
		glfwSwapBuffers(window);

		// Calling of the update function
		glfwPollEvents();
	}

	// Deleting remaining objects 
	shaderProgram.Delete();
	lightShader.Delete();

	// Window closing
	glfwDestroyWindow(window);
	
	// GLFW closing
	glfwTerminate();

	return 0;
}