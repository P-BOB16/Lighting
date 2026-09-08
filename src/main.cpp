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

	glm::vec3 cubePositions[] = {
	   glm::vec3(0.0f,  0.0f,  0.0f),
	   glm::vec3(2.0f,  5.0f, -15.0f),
	   glm::vec3(-1.5f, -2.2f, -2.5f),
	   glm::vec3(-3.8f, -2.0f, -12.3f),
	   glm::vec3(2.4f, -0.4f, -3.5f),
	   glm::vec3(-1.7f,  3.0f, -7.5f),
	   glm::vec3(1.3f, -2.0f, -2.5f),
	   glm::vec3(1.5f,  2.0f, -2.5f),
	   glm::vec3(1.5f,  0.2f, -1.5f),
	   glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	ourShader.use();
	ourShader.setFloat("material.shininess", 32.0f);
	ourShader.setInt("material.diffuse", 0);
	ourShader.setInt("material.specular", 1);
	ourShader.setInt("material.emission", 2);

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
		ourShader.setFloat("time", glfwGetTime());

		ourShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		ourShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		ourShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		ourShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

		// point light 1
		ourShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		ourShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		ourShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		ourShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		ourShader.setFloat("pointLights[0].constant", 1.0f);
		ourShader.setFloat("pointLights[0].linear", 0.09f);
		ourShader.setFloat("pointLights[0].quadratic", 0.032f);
		// point light 2
		ourShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		ourShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		ourShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		ourShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		ourShader.setFloat("pointLights[1].constant", 1.0f);
		ourShader.setFloat("pointLights[1].linear", 0.09f);
		ourShader.setFloat("pointLights[1].quadratic", 0.032f);
		// point light 3
		ourShader.setVec3("pointLights[2].position", pointLightPositions[2]);
		ourShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		ourShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		ourShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		ourShader.setFloat("pointLights[2].constant", 1.0f);
		ourShader.setFloat("pointLights[2].linear", 0.09f);
		ourShader.setFloat("pointLights[2].quadratic", 0.032f);
		// point light 4
		ourShader.setVec3("pointLights[3].position", pointLightPositions[3]);
		ourShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		ourShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		ourShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		ourShader.setFloat("pointLights[3].constant", 1.0f);
		ourShader.setFloat("pointLights[3].linear", 0.09f);
		ourShader.setFloat("pointLights[3].quadratic", 0.032f);
		// spotLight
		ourShader.setVec3("spotLight.position", ourCamera.Position);
		ourShader.setVec3("spotLight.direction", ourCamera.Front);
		ourShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		ourShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		ourShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		ourShader.setFloat("spotLight.constant", 1.0f);
		ourShader.setFloat("spotLight.linear", 0.09f);
		ourShader.setFloat("spotLight.quadratic", 0.032f);
		ourShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		ourShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		glm::mat4 projection = glm::perspective(glm::radians(ourCamera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
		glm::mat4 view = ourCamera.GetViewMatrix();
		
		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			ourShader.setMat4("model", model);
			ourMesh.drawBox();
		}
		//model = glm::rotate(model, glm::radians((float)glfwGetTime()*90), glm::vec3(1.0f, 1.0f, 0.0f));

		lightShader.use();
		lightShader.setMat4("projection", projection);
		lightShader.setMat4("view", view);
		for (unsigned int i = 0; i < 4; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f));
			lightShader.setMat4("model", model);
			ourMesh.drawLight();
		}

		ourWindow.update();
	}

	glfwTerminate();
	return 0;
}