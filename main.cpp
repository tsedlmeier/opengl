#include "shader.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
 
#include <iostream>
#include <stdlib.h>
#include <string>
 
 
int screen_width{ 1080 };
int screen_height{ 1080 };
 
int num_frames{ 0 };
float last_time{ 0.0f };
 
float vertices[] = 
{
//    x      y      z   
    -1.0f, -1.0f, -0.0f,
     1.0f,  1.0f, -0.0f,
    -1.0f,  1.0f, -0.0f,
     1.0f, -1.0f, -0.0f
};
 
unsigned int indices[] = 
{
//  2---,1
//  | .' |
//  0'---3
    0, 1, 2,
    0, 3, 1
};
 
 
void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
    glViewport(0, 0, width, height);
}
 
void countFPS()
{
    double current_time = glfwGetTime();
    num_frames++;
    if (current_time - last_time >= 1.0)
    {
        std::cout << 1000.0 / num_frames << "ms / frame\n";
        num_frames = 0;
        last_time += 1.0;
    }
}
 
float center_x{ 0.0f };
float center_y{ 0.0f };
float zoom{ 1.0 };
 
void process_input(GLFWwindow * window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
 
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        center_y = center_y + 0.015f * zoom;
        if (center_y > 1.0f)
        {
            center_y = 1.0f;
    }
    }
 
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        center_y = center_y - 0.015f * zoom;
        if (center_y < -1.0f)
        {
            center_y = -1.0f;
        }
    }
 
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        center_x = center_x - 0.015f * zoom;
        if (center_x < -1.0f)
        {
            center_x = -1.0f;
        }
    }
 
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        center_x = center_x + 0.015f * zoom;
        if (center_x > 1.0f)
        {
            center_x = 1.0f;
        }
    }
 
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        zoom = zoom * 1.1f;
        if (zoom > 1.0f)
        {
            zoom = 1.0f;
        }
    }
 
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        zoom = zoom * 0.9f;
        if (zoom < 0.00001f)
        {
            zoom = 0.00001f;
        }
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "Mandelbrot", NULL, NULL);
 
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window!\n";
        glfwTerminate();
        return -1;
    }
 
    glfwMakeContextCurrent(window);
 
    if (glewInit())
    {
        std::cout << "Failed initializing GLEW\n";
    }
 
    glViewport(0, 0, screen_width, screen_height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
 
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
 
    glBindVertexArray(VAO);
 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
 

    Shader shader("shaders/basic.vs", "shaders/basic.fs");
    shader.bind();
 
    last_time = glfwGetTime();
 
    glEnable(GL_DEPTH_TEST);
 
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.0f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
        countFPS();

        process_input(window);
        shader.use_shader();
        shader.pass_uniform1f(zoom, "zoom");
        shader.pass_uniform1f(center_x, "center_x");
        shader.pass_uniform1f(center_y, "center_y");
        glBindVertexArray(VAO);
         
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
 
        glfwSwapBuffers(window);
        glfwPollEvents();
 
    }
 
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
 
    glfwTerminate();
    return 0;
}
