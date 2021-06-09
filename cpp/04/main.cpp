#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <glm/vec3.hpp>
#include <bullet/btBulletDynamicsCommon.h>

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

std::string read_file(std::string filename)
{
  std::ifstream file;
  std::string output;
  file.open(filename);

  if (file.good() && file.is_open())
  {
    while (file)
    {
      std::string buff;
      std::getline(file, buff);
      output += buff.append("\n");
    }
    file.close();
    return output;
  }
  else
  {
    std::cerr << "Error reading file: " + filename << std::endl;
    return NULL;
  }
}

void check_shader_compile_status(unsigned int vertexShader)
{
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
}

unsigned int compile_shader(const char *serializedShader, int type)
{
  unsigned int shader = glCreateShader(type);
  glShaderSource(shader, 1, &serializedShader, NULL);
  glCompileShader(shader);
  check_shader_compile_status(shader);
  return shader;
}

void check_shader_program_compile_status(unsigned int shaderProgram)
{
  int success;
  char infoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
}

void bind_buffers(float vertices[], int vertices_size, unsigned int VBO, unsigned int VAO)
{
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0); // Vertex attributes stay the same
  glEnableVertexAttribArray(0);
}

int main()
{
  std::string vertexShaderStr = read_file("shaders/vertex.vs");
  std::string fragmentShaderStr = read_file("shaders/fragment.fs");
  std::string blueShaderStr = read_file("shaders/shade_of_blue.fs");

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

  // Shader ordering is important:
  // 1. We create the vertex shader to assemble the shape
  unsigned int vertexShader = compile_shader(vertexShaderStr.c_str(), GL_VERTEX_SHADER);

  // 2. We create the fragment shader to colorize the shape
  unsigned int fragmentShader = compile_shader(fragmentShaderStr.c_str(), GL_FRAGMENT_SHADER);

  // Same with the blue one
  unsigned int blueShader = compile_shader(blueShaderStr.c_str(), GL_FRAGMENT_SHADER);

  unsigned int shaderProgram = glCreateProgram();

  // We attach the shaders in order to the program
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // what is this, a washing machine? lol
  unsigned int blueProgram = glCreateProgram();

  // Same with the blue one
  glAttachShader(blueProgram, vertexShader);
  glAttachShader(blueProgram, blueShader);
  glLinkProgram(blueProgram);

  check_shader_program_compile_status(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  float triangle1[] = {
      0.5f, 0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      -0.5f, -0.5f, 0.0f};

  float triangle2[] = {
      -0.4f, 0.4f, 0.0f,
      -0.5f, 0.5f, 0.0f,
      -0.5f, 0.0f, 0.0f};

  // unsigned int indices[] = {
  //     0, 1, 2,
  //     3, 4, 5};

  unsigned int VBOs[2], VAOs[2];
  glGenVertexArrays(2, VAOs);
  glGenBuffers(2, VBOs);

  bind_buffers(triangle1, sizeof(triangle1), VBOs[0], VAOs[0]);
  bind_buffers(triangle2, sizeof(triangle2), VBOs[1], VAOs[1]);
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

    glUseProgram(shaderProgram);
    // glBindVertexArray(VAO);
    for (int i = 0; i < sizeof(VAOs) / sizeof(int); i++)
    {
      glBindVertexArray(VAOs[i]);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      glUseProgram(blueProgram);
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
  glDeleteProgram(shaderProgram);
  glfwTerminate();
  return 0;
}