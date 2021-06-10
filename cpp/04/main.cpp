#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <glm/vec3.hpp>
#include <bullet/btBulletDynamicsCommon.h>
#include <stb_image.h>
#include "shader.h"

bool WIREFRAME_MODE = false;
bool TAB_PRESSED = false;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  int TAB_PRESS = glfwGetKey(window, GLFW_KEY_TAB);

  if (TAB_PRESS == GLFW_PRESS && TAB_PRESSED != true)
  {
    TAB_PRESSED = true;
    WIREFRAME_MODE = !WIREFRAME_MODE;
    if (WIREFRAME_MODE)
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
  }
  if (TAB_PRESS == GLFW_RELEASE)
  {
    TAB_PRESSED = false;
  }
}

void bind_buffers(float vertices[], int vertices_size, unsigned int VBO, unsigned int VAO)
{
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
  // position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // color
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "Test engine", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to init GLAD" << std::endl;
    return -1;
  }
  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  Shader defaultShader = Shader("shaders/vertex.vs", "shaders/fragment.fs");
  Shader blueShader = Shader("shaders/vertex.vs", "shaders/shade_of_blue.fs");

  float triangle1[] = {
      0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
      0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f};

  float triangle2[] = {
      -0.4f, 0.4f, 0.0f, 0.0f, 0.0f, 0.6f,
      -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
      -0.5f, 0.0f, 0.0f, 0.8f, 0.0f, 1.0f};

  int width, height, nrChannels;
  unsigned char *data = stbi_load("honkler.jpg", &width, &height,
                                  &nrChannels, 0);

  float textureCoords[] = {
      0.0f, 0.0f,
      1.0f, 0.0f,
      1.0f, 1.0f};

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

  float borderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};

  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // unsigned int indices[] = {
  //     0, 1, 2,
  //     3, 4, 5};

  unsigned int VBOs[2], VAOs[2];
  glGenVertexArrays(2, VAOs);
  glGenBuffers(2, VBOs);

  bind_buffers(triangle1, sizeof(triangle1), VBOs[0], VAOs[0]);
  bind_buffers(triangle2, sizeof(triangle2), VBOs[1], VAOs[1]);

  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);
  std::cout << "buffers are bound" << std::endl;
  // glGenBuffers(1, &EBO);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  // glGenBuffers(2, &EBO);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  while (!glfwWindowShouldClose(window))
  {
    processInput(window);

    glClearColor(0.4f, 0.2f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(defaultShader.ID, "uniformColor");
    defaultShader.use();

    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    for (int i = 0; i < sizeof(VAOs) / sizeof(int); i++)
    {
      glBindVertexArray(VAOs[i]);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      blueShader.use();
    }

    // glDrawElements(GL_TRIANGLES, 20, GL_UNSIGNED_INT, 0);

    // glDrawElements(GL_TRIANGLES, vbo_arrays.size() * 3, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    // Swap front and back buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteVertexArrays(2, VAOs);
  glDeleteBuffers(2, VBOs);
  defaultShader.remove();
  glfwTerminate();
  return 0;
}