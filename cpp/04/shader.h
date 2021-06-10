#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <iostream>

class Shader
{
public:
  unsigned int ID;

  Shader(const char *vertexPath, const char *fragmentPath)
  {
    // Shader ordering is important:
    // 1. We create the vertex shader to assemble the shape
    unsigned int vertexShader = compile_shader(vertexPath, GL_VERTEX_SHADER);
    // 2. We create the fragment shader to colorize the shape
    unsigned int fragmentShader = compile_shader(fragmentPath, GL_FRAGMENT_SHADER);
    // We attach the shaders in order to the program
    ID = create_shader_program(vertexShader, fragmentShader);
  };

  void use()
  {
    glUseProgram(ID);
  };

  void remove()
  {
    glDeleteProgram(ID);
  };

  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;

private:
  std::string read_file(const char *filename)
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
      std::cerr << "Error reading file: " + std::string(filename) << std::endl;
      return NULL;
    }
  };

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
  };

  unsigned int compile_shader(const char *shaderPath, int type)
  {
    unsigned int shader = glCreateShader(type);
    const char *serializedShader = NULL;
    serializedShader = read_file(shaderPath).c_str();
    glShaderSource(shader, 1, &serializedShader, NULL);
    glCompileShader(shader);
    check_shader_compile_status(shader);
    return shader;
  };

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
  };

  unsigned int create_shader_program(const unsigned int vertexShader, const unsigned int fragmentShader)
  {
    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    check_shader_program_compile_status(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
  };
};

#endif