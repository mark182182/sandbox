#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

std::string read_file(const char *filename)
{
  std::ifstream file(filename, std::ifstream::in);
  std::stringstream stream;

  if (file.good() && file.is_open())
  {
    while (file)
    {
      std::string buf;
      std::getline(file, buf, '\r');
      stream << buf;
    }
    file.close();
    return stream.str();
  }
  else
  {
    std::cerr << "Error reading file: " + std::string(filename) << std::endl;
    return NULL;
  }
};

#endif