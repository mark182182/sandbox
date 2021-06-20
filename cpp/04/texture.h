#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <iostream>
#include <stb_image.h>


class Texture {
  unsigned int ID;

public:
  Texture(const char *path, GLenum format, unsigned int type) {
    glGenTextures(1, &ID);
    load_texture(path, format, type);
  };

  void activiate_and_bind(GLenum texture) {
    glActiveTexture(texture);
    glBindTexture(GL_TEXTURE_2D, ID);
  };

private:
  void load_texture(const char *path, GLenum format, unsigned int type) {
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
      glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                   GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    } else {
      std::cerr << "unable to load the texture" << std::endl;
    }
    stbi_image_free(data);
  };
};

#endif