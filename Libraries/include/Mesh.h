#pragma once
#ifndef MESH_H
#define MESH_H
#include <glad/glad.h>
#include <vector>
#include <stb/stb_image.h>

class Mesh
{
private:
	unsigned int VAO, VBO, texture;
	int vertexCount, width, height, nrChannels;
    unsigned char* data;

public:
	Mesh()
	{
        std::vector<float> vertices = {
            // Front face
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom-Left
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Bottom-Right
             0.0f,  0.5f,  0.0f,  0.5f, 1.0f, // Apex (Top-Center)

             // Back face
              0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-Left
             -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom-Right
              0.0f,  0.5f,  0.0f,  0.5f, 1.0f, // Apex

              // Left face
              -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-Left
              -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Bottom-Right
               0.0f,  0.5f,  0.0f,  0.5f, 1.0f, // Apex

               // Right face
                0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom-Left
                0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom-Right
                0.0f,  0.5f,  0.0f,  0.5f, 1.0f, // Apex

                // Bottom face (square, requires 2 triangles - kept exact same as cube base)
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f
        };

		vertexCount = vertices.size() / 5;

		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_set_flip_vertically_on_load(true);
        data = stbi_load("Assets/Texture/void.jpg", &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);


		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}
	void draw()
	{
        glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vertexCount);
		glBindVertexArray(0);
	}

	~Mesh()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
};

#endif // !MODEL_H
