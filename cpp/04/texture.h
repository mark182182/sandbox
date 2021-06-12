#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <glad/glad.h>
#include <stb_image.h>

class Texture
{
  unsigned int ID;

public:
  Texture(const char *path, GLenum format)
  {
    glGenTextures(1, &ID);
    load_texture(path, format);
  };

  void activiate_and_bind(GLenum texture)
  {
    glActiveTexture(texture);
    glBindTexture(GL_TEXTURE_2D, ID);
  };

private:
  void load_texture(const char *path, GLenum format)
  {
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height,
                                    &nrChannels, 0);
    if (data)
    {
      glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
      std::cerr << "unable to load the texture" << std::endl;
    }
    stbi_image_free(data);
  };
};

#endif