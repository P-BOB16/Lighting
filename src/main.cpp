#include <iostream>
#include <Shader.h>
#include <Mesh.h>
#include <Window.h>
#include <Camera.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void processInput(GLFWwindow* window);
Camera ourCamera(glm::vec3(0.0f, 0.0f, 3.0f));

int main()
{
	Window ourWindow(800, 600, "Lighting");
	glEnable(GL_DEPTH_TEST);
	Shader ourShader("Shaders/default.vs", "Shaders/default.fs");
	Mesh ourMesh;

	ourShader.use();
	ourShader.setInt("texture0", 0);

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
	};

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	ourWindow.viewCamera = &ourCamera;

	glClearColor(0.200f, 0.200f, 0.200f, 1.0f);
	while (ourWindow.isRunning()) 
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		ourWindow.processInput(deltaTime);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.use();

		glm::mat4 projection = glm::perspective(glm::radians(ourCamera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);

		glm::mat4 view = ourCamera.GetViewMatrix();
		ourShader.setMat4("view", view);

		for (unsigned int i = 0; i < 5; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.5f, 0.0f));
			ourShader.setMat4("model", model);
			ourMesh.draw();
		}

		ourWindow.update();
	}

	glfwTerminate();
	return 0;
}