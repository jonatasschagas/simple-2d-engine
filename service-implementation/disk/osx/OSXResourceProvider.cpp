#include "OSXResourceProvider.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "utils/FileUtils.h"

void* OSXResourceProvider::loadTexture(string const& path, int* pWidth,
                                       int* pHeight) {
  int n;
  unsigned char* data = stbi_load(path.c_str(), pWidth, pHeight, &n, 0);
  return data;
}

void OSXResourceProvider::readContentsFromFile(string const& path,
                                               string* pOutputString) {
  *pOutputString = loadFile(path);
}

char* OSXResourceProvider::readBytesFromFile(string const& path,
                                             std::size_t& fileSize) {
  std::ifstream file(path, std::ios::binary | std::ios::ate);

  assert(file.is_open() && "Error: Could not open the file.");

  fileSize = static_cast<std::size_t>(file.tellg());
  char* buffer = new char[fileSize];
  file.seekg(0, std::ios::beg);
  file.read(buffer, fileSize);
  file.close();

  return buffer;
}

void OSXResourceProvider::writeContentsToFile(string const& path,
                                              string const& contents) {
  std::ofstream file(path);
  file << contents;
  file.close();
}
