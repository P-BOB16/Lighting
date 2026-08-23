#include <iostream>
#include <Shader.h>
#include <Mesh.h>
#include <Window.h>
#include <Camera.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void processInput(GLFWwindow* window);
Camera ourCamera(glm::vec3(0.0f, 0.0f, 3.0f));
glm::vec3 lightPos(1.2f, 0.0f, 2.0f);

int main()
{
	Window ourWindow(800, 600, "Lighting");
	glEnable(GL_DEPTH_TEST);
	Shader ourShader("Shaders/default.vs", "Shaders/default.fs");
	Shader lightShader("Shaders/default.vs", "Shaders/light.fs");
	
	Mesh ourMesh;

	//ourShader.use();
	//ourShader.setInt("texture0", 0);

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	ourWindow.viewCamera = &ourCamera;

	glClearColor(0.200f, 0.200f, 0.200f, 1.0f);

	ourShader.use();
	ourShader.setVec3("lightPos", lightPos);
	ourShader.setVec3("camPos", ourCamera.Position);

	while (ourWindow.isRunning()) 
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		ourWindow.processInput(deltaTime);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.use();
		ourShader.setVec3("boxColor", 1.0f, 0.5f, 0.35f);
		ourShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		glm::mat4 projection = glm::perspective(glm::radians(ourCamera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
		glm::mat4 view = ourCamera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.0f, 0.0, 0.0f));

		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);
		ourShader.setMat4("model", model);

		ourMesh.drawLight();

		lightShader.use();
		model = glm::mat4(1.0);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightShader.setMat4("projection", projection);
		lightShader.setMat4("view", view);
		lightShader.setMat4("model", model);

		ourMesh.drawBox();

		ourWindow.update();
	}

	glfwTerminate();
	return 0;
}