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
