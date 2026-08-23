#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Camera.h"

class Window
{
private:
    float lastX = 400.0f;
    float lastY = 300.0f;
    bool firstMouse = true;
    float change = 1.0f;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
    {
        Window* win = (Window*)glfwGetWindowUserPointer(window);

        if (win == nullptr || win->viewCamera == nullptr) return;

        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (win->firstMouse)
        {
            win->lastX = xpos;
            win->lastY = ypos;
            win->firstMouse = false;
        }

        float xoffset = xpos - win->lastX;
        float yoffset = win->lastY - ypos;
        win->lastX = xpos;
        win->lastY = ypos;

        win->viewCamera->ProcessMouseMovement(xoffset, yoffset);
    }

    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        Window* win = (Window*)glfwGetWindowUserPointer(window);

        if (win != nullptr && win->viewCamera != nullptr) {
            win->viewCamera->ProcessMouseScroll(static_cast<float>(yoffset));
        }
    }

public:
    GLFWwindow* window;
    Camera* viewCamera = nullptr;

    Window(int width, int height, const char* title)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }

        glfwSetWindowUserPointer(window, this);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        framebuffer_size_callback(window, width, height);

        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
    }

    float getChange() 
    {
        return change;
    }

    void processInput(float deltaTime)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (viewCamera != nullptr) {
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                viewCamera->ProcessKeyboard(FORWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                viewCamera->ProcessKeyboard(BACKWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                viewCamera->ProcessKeyboard(LEFT, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                viewCamera->ProcessKeyboard(RIGHT, deltaTime);

            if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
                change += 1 * deltaTime;

            if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
                change -= 1 * deltaTime;

            if (change < 0.0f) change = 0.0f;
            if (change > 1.0f) change = 1.0f;
        }
    }

    bool isRunning()
    {
        return !glfwWindowShouldClose(window);
    }

    void update()
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ~Window()
    {
        glfwTerminate();
    }
};

#endif