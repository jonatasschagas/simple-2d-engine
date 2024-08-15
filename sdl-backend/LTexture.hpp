#pragma once
#ifndef LTexture_hpp
#define LTexture_hpp

#include "SDL.h"
#include <stdio.h>
#include <string>

// Texture wrapper class
class LTexture {
 public:
  LTexture();

  // Deallocates memory
  ~LTexture();

  // Loads image at specified path
  bool loadFromFile(SDL_Renderer* pSDLRenderer, std::string path);

  // Deallocates texture
  void free();

  // Set color modulation
  void setColor(Uint8 red, Uint8 green, Uint8 blue);

  // Set blending
  void setBlendMode(SDL_BlendMode blending);

  // Set alpha modulation
  void setAlpha(Uint8 alpha);

  // Renders texture at given point
  void render(SDL_Renderer* pSDLRenderer, float x, float y, SDL_Rect* clip,
              float w, float h, float angle, bool flipHorizontal = false);

  // Gets image dimensions
  int getWidth();
  int getHeight();

  SDL_Texture* getTexture();

 private:
  // The actual hardware texture
  SDL_Texture* m_pTexture = NULL;

  // Image dimensions
  int m_width;
  int m_height;
};

#endif /* LTexture_hpp */
