#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <glm/vec3.hpp>
#include <bullet/btBulletDynamicsCommon.h>
#include <stb_image.h>
#include "shader.h"
#include "texture.h"

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
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // color
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // texture
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);
}

void set_time_based_float_value(Shader shader, const char *uniformVarName)
{
  float timeValue = glfwGetTime();
  float timeBasedValue = sin(timeValue) / 10;
  int uniformLocation = glGetUniformLocation(shader.ID, uniformVarName);
  shader.use();
  shader.setFloat(uniformVarName, timeBasedValue);
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
  Shader positionBasedShader = Shader("shaders/vertex.vs", "shaders/fragment_position.fs");

  float triangles[] = {
      0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
      0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
      -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f};

  unsigned int indices[] = {
      0, 1, 3,
      1, 2, 3};

  unsigned int vbo, vao, EBO;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &EBO);

  bind_buffers(triangles, sizeof(triangles), vbo, vao);
  std::cout << "buffers are bound" << std::endl;

  stbi_set_flip_vertically_on_load(true);

  Texture woodTexture = Texture("textures/wood.jpg", GL_RGB, GL_REPEAT);
  Texture transparentTexture = Texture("textures/transparent.png", GL_RGBA, GL_REPEAT);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  defaultShader.use();
  defaultShader.setInt("texture1", 0);
  defaultShader.setInt("texture2", 1);

  while (!glfwWindowShouldClose(window))
  {
    processInput(window);
    glClearColor(0.4f, 0.2f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // set_time_based_float_value(defaultShader, "xOffset");

    // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    // for (int i = 0; i < sizeof(VAOs) / sizeof(int); i++)
    // {
    //   glBindVertexArray(VAOs[i]);
    //   glDrawArrays(GL_TRIANGLES, 0, 3);
    //   set_time_based_float_value(positionBasedShader, "xOffset");
    // }

    woodTexture.activiate_and_bind(GL_TEXTURE0);
    transparentTexture.activiate_and_bind(GL_TEXTURE1);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // glDrawElements(GL_TRIANGLES, vbo_arrays.size() * 3, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    // Swap front and back buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  defaultShader.remove();
  positionBasedShader.remove();
  glfwTerminate();
  return 0;
}