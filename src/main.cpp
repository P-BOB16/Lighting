#include <iostream>
#include <Shader.h>
#include <Mesh.h>
#include <Window.h>
#include <Camera.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void processInput(GLFWwindow* window);
Camera ourCamera(glm::vec3(0.0f, 0.0f, 3.0f));
glm::vec3 lightPos(1.5f, 0.5f, 0.0f);

int main()
{
	Window ourWindow(800, 600, "Lighting");
	glEnable(GL_DEPTH_TEST);
	Shader ourShader("Shaders/default.vs", "Shaders/default.fs");
	Shader lightShader("Shaders/default.vs", "Shaders/light.fs");
	
	Mesh ourMesh;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	ourWindow.viewCamera = &ourCamera;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	ourShader.use();
	ourShader.setVec3("boxColor", 1.0f, 0.5f, 0.35f);
	ourShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	ourShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
	ourShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
	ourShader.setVec3("material.specular", 0.0f, 0.0f, 0.0f);
	ourShader.setFloat("material.shininess", 32.0f);

	ourShader.setInt("material.diffuse", 0);
	ourShader.setInt("material.specular", 1);

	while (ourWindow.isRunning()) 
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		ourWindow.processInput(deltaTime);

		//glm::vec3 lightPos((sin((float)glfwGetTime())*2) ,(cos((float)glfwGetTime())*2), 0.0f);


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.use();
		ourShader.setVec3("camPos", ourCamera.Position);
		ourShader.setVec3("light.position", lightPos);
		glm::vec3 lightColor(1.0f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
		ourShader.setVec3("light.ambient", ambientColor);
		ourShader.setVec3("light.diffuse", diffuseColor);
		ourShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

		glm::mat4 projection = glm::perspective(glm::radians(ourCamera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
		glm::mat4 view = ourCamera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians((float)glfwGetTime()*90), glm::vec3(1.0f, 1.0f, 0.0f));

		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);
		ourShader.setMat4("model", model);

		ourMesh.drawBox();

		lightShader.use();
		glm::vec3 reflectColor(1.0f);
		reflectColor = reflectColor * lightColor;

		model = glm::mat4(1.0);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		//model = glm::rotate(model, glm::radians((float)glfwGetTime() * 90), glm::vec3(0.0f, 0.0f, 1.0f));

		lightShader.setMat4("projection", projection);
		lightShader.setMat4("view", view);
		lightShader.setMat4("model", model);
		lightShader.setVec3("reflectColor", reflectColor);

		ourMesh.drawLight();

		ourWindow.update();
	}

	glfwTerminate();
	return 0;
}