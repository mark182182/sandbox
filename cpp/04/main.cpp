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
const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;
bool wireframe_mode = false;
bool tab_pressed = false;
bool up_pressed = false;
bool down_pressed = false;
bool z_pressed = false;
float fov_amount = 90.0f;
float prev_fov_amount = fov_amount;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float lastX = WINDOW_WIDTH / 2, lastY = WINDOW_HEIGHT / 2;

bool firstMouse = true;

float yaw = -90.f;
float pitch = -90.f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

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

void mouse_callback(GLFWwindow *window, double xPos, double yPos) {
  if (firstMouse) {
    lastX = xPos;
    lastY = yPos;
    firstMouse = false;
  }

  float xOffset = xPos - lastX;
  float yOffset = yPos - lastY;
  lastX = xPos;
  lastY = yPos;

  const float sensivity = 0.2f;
  xOffset *= sensivity;
  yOffset *= sensivity * -1.0f;

  yaw += xOffset;
  pitch += yOffset;

  if (pitch > 89.0f) {
    pitch = 89.0f;
  }
  if (pitch < -89.0f) {
    pitch = -89.0f;
  }
};

void scroll_callback(GLFWwindow *window, double xOffset, double yOffset) {
  std::cout << fov_amount << std::endl;
  fov_amount -= (float)yOffset;
  if (fov_amount < 1.0f) {
    fov_amount = 1.0f;
  }
  if (fov_amount > 90.0f) {
    fov_amount = 90.0f;
  }
  std::cout << fov_amount << std::endl;
}

int create_window_and_init_libs() {
  window =
      glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL);
  if (window == NULL) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to init GLAD" << std::endl;
    return -1;
  }
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
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

  if (up_arrow_press == GLFW_RELEASE) {
    up_pressed = false;
  }
  if (down_arrow_press == GLFW_RELEASE) {
    down_pressed = false;
  }

  int z_press = glfwGetKey(window, GLFW_KEY_Z);
  if (z_press == GLFW_PRESS && z_pressed != true) {
    fov_amount = 30.0f;
  }

  if (z_press == GLFW_RELEASE) {
    z_pressed = false;
    fov_amount = prev_fov_amount;
  }

  float speedMultiplier = 1.0f;

  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    speedMultiplier = 3.0f;
  }

  const float cameraSpeed = 3.2f * deltaTime * speedMultiplier;

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    cameraPos += cameraSpeed * cameraFront;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    cameraPos -= cameraSpeed * cameraFront;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    cameraPos -=
        glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    cameraPos +=
        glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  }
}

void bind_buffers(float vertices[], int vertices_size, unsigned int VBO,
                  unsigned int VAO) {
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
  // position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // texture
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
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

  float triangles[] = {
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

      -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
      0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

  unsigned int indices[] = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11,
                            12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
                            24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};

  glm::vec3 manyCubePositions[] = {
      glm::vec3(1.3f, -2.0f, -2.5f),
      glm::vec3((std::rand() % 4 + 1), (std::rand() % 4 + 1),
                (std::rand() % 4 + 1)),
      glm::vec3((std::rand() % 4 + 1), (std::rand() % 4 + 1),
                (std::rand() % 4 + 1)),
      glm::vec3((std::rand() % 4 + 1), (std::rand() % 4 + 1),
                (std::rand() % 4 + 1)),
      glm::vec3((std::rand() % 4 + 1), (std::rand() % 4 + 1),
                (std::rand() % 4 + 1)),
      glm::vec3((std::rand() % 4 + 1), (std::rand() % 4 + 1),
                (std::rand() % 4 + 1)),
      glm::vec3((std::rand() % 4 + 1), (std::rand() % 4 + 1),
                (std::rand() % 4 + 1)),
      glm::vec3((std::rand() % 4 + 1), (std::rand() % 4 + 1),
                (std::rand() % 4 + 1)),
      glm::vec3((std::rand() % 4 + 1), (std::rand() % 4 + 1),
                (std::rand() % 4 + 1)),
      glm::vec3((std::rand() % 4 + 1), (std::rand() % 4 + 1),
                (std::rand() % 4 + 1)),
      glm::vec3((std::rand() % 4 + 1), (std::rand() % 4 + 1),
                (std::rand() % 4 + 1))};

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
  glEnable(GL_DEPTH_TEST);

  std::cout << "Textures are set" << std::endl;

  defaultShader.use();
  defaultShader.setInt("texture1", 0);
  defaultShader.setInt("texture2", 1);

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

  glm::mat4 projection;

  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
    projection = glm::perspective(glm::radians(fov_amount),
                                  (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
                                  0.1f, 100.0f);

    process_Input(window);
    glClearColor(0.4f, 0.2f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);

    glm::mat4 view;
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    set_uniform_matrix_value(defaultShader, "model", 1, model);
    set_uniform_matrix_value(defaultShader, "view", 1, view);
    set_uniform_matrix_value(defaultShader, "projection", 1, projection);

    float timeBasedValue =
        std::sin(float(glfwGetTime())) * ((std::rand() % 2 + 1) - 1);

    model = glm::rotate(model, timeBasedValue * glm::radians(timeBasedValue),
                        glm::vec3(0.5f, 1.0f, 0.0f));

    int vertexColor = glGetUniformLocation(defaultShader.ID, "vertexColor");
    glUniform3f(vertexColor, 0.4f, 0.8f, std::sin(float(glfwGetTime())));

    defaultShader.setFloat("blendAmount", std::sin(float(glfwGetTime())));
    woodTexture.activiate_and_bind(GL_TEXTURE0);
    transparentTexture.activiate_and_bind(GL_TEXTURE1);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    for (size_t i = 0; i < 10; i++) {
      glm::mat4 model = glm::mat4(1.0f);
      glm::vec3 current = manyCubePositions[i];
      current.x += i;
      model = glm::translate(model, current);
      model = glm::rotate(
          model, std::sin(float(glfwGetTime())) * glm::radians(45.0f * i),
          glm::vec3(1.0f, 0.2f, 0.8f));

      set_uniform_matrix_value(defaultShader, "model", 1, model);
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

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