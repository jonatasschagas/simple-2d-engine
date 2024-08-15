#include "SDLResourceProvider.hpp"
#include "SDL_image.h"
#include "utils/FileUtils.h"
#include <iostream>

SDLResourceProvider::SDLResourceProvider() {}

SDLResourceProvider::~SDLResourceProvider() {}

void* SDLResourceProvider::loadTexture(string const& path, int* pWidth,
                                       int* pHeight) {
  SDL_Surface* surface = IMG_Load(path.c_str());
  if (surface == nullptr) {
    cout << "Failed to load image: " << path << endl;
    return nullptr;
  }

  *pWidth = surface->w;
  *pHeight = surface->h;

  return surface;
}

void SDLResourceProvider::readContentsFromFile(string const& path,
                                               string* pOutputString) {
  *pOutputString = loadFile(path);
}
