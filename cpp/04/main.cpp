#include "shader.h"
#include "texture.h"
#include <GLFW/glfw3.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <fstream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <stb_image.h>
#include <string>

const char *WINDOW_NAME = "Test engine";
GLFWwindow *window = NULL;
bool wireframe_mode = false;
bool tab_pressed = false;
bool up_pressed = false;
bool down_pressed = false;
float blend_amount = 0.5f;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void init_and_set_window_hints() {
  std::cout << "Starting " << WINDOW_NAME << "..." << std::endl;
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int create_window_and_init_libs() {
  window = glfwCreateWindow(800, 600, WINDOW_NAME, NULL, NULL);
  if (window == NULL) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to init GLAD" << std::endl;
    return -1;
  }
  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  return 1;
}

void process_Input(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  int tab_press = glfwGetKey(window, GLFW_KEY_TAB);

  int up_arrow_press = glfwGetKey(window, GLFW_KEY_UP);
  int down_arrow_press = glfwGetKey(window, GLFW_KEY_DOWN);

  if (tab_press == GLFW_PRESS && tab_pressed != true) {
    tab_pressed = true;
    wireframe_mode = !wireframe_mode;
    if (wireframe_mode) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
  }
  if (tab_press == GLFW_RELEASE) {
    tab_pressed = false;
  }

  if (blend_amount < 1.0f && up_arrow_press == GLFW_PRESS &&
      up_pressed != true) {
    up_pressed = true;
    blend_amount += 0.1f;
  } else if (blend_amount > 0.0f && down_arrow_press == GLFW_PRESS &&
             down_pressed != true) {
    down_pressed = true;
    blend_amount -= 0.1f;
  }

  if (up_arrow_press == GLFW_RELEASE) {
    up_pressed = false;
  }
  if (down_arrow_press == GLFW_RELEASE) {
    down_pressed = false;
  }
}

void bind_buffers(float vertices[], int vertices_size, unsigned int VBO,
                  unsigned int VAO) {
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
  // position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // color
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // texture
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);
}

void set_uniform_matrix_value(Shader shader, const char *uniformVarName,
                              int num_of_matrices, glm::mat4 transform) {
  int uniformLocation = glGetUniformLocation(shader.ID, uniformVarName);
  glUniformMatrix4fv(uniformLocation, num_of_matrices, GL_FALSE,
                     glm::value_ptr(transform));
}

int main() {
  init_and_set_window_hints();
  int isInitSuccessful = create_window_and_init_libs();
  if (!isInitSuccessful) {
    return -1;
  }
  Shader defaultShader = Shader("shaders/vertex.vs", "shaders/fragment.fs");
  Shader positionBasedShader =
      Shader("shaders/vertex.vs", "shaders/fragment_position.fs");

  float triangles[] = {0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                       0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
                       -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                       -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f};

  unsigned int indices[] = {0, 1, 3, 1, 2, 3};

  unsigned int vbo, vao, ebo;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  bind_buffers(triangles, sizeof(triangles), vbo, vao);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  std::cout << "Buffers are bound" << std::endl;

  stbi_set_flip_vertically_on_load(true);

  Texture woodTexture = Texture("textures/wood.jpg", GL_RGB, GL_REPEAT);
  Texture transparentTexture =
      Texture("textures/transparent.png", GL_RGBA, GL_REPEAT);

  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  std::cout << "Textures are set" << std::endl;

  defaultShader.use();
  defaultShader.setInt("texture1", 0);
  defaultShader.setInt("texture2", 1);

  while (!glfwWindowShouldClose(window)) {
    process_Input(window);
    glClearColor(0.4f, 0.2f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 trans1 = glm::mat4(1.0f);
    trans1 = glm::translate(trans1, glm::vec3(0.5f, -0.5f, 0.0f));
    trans1 =
        glm::rotate(trans1, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    set_uniform_matrix_value(defaultShader, "transform", 1, trans1);

    defaultShader.setFloat("blendAmount", std::sin(float(glfwGetTime())));
    woodTexture.activiate_and_bind(GL_TEXTURE0);
    transparentTexture.activiate_and_bind(GL_TEXTURE1);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glm::mat4 trans2 = glm::mat4(1.0f);
    trans2 = glm::translate(trans2, glm::vec3(std::sin((float)glfwGetTime()), 0.5f, 0.0f));
    trans2 =
        glm::scale(trans2, glm::vec3(std::abs(std::sin((float)glfwGetTime())),
                                     std::abs(std::sin((float)glfwGetTime())), 0.0f));
    trans2 =
        glm::rotate(trans2, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    set_uniform_matrix_value(defaultShader, "transform", 1, trans2);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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