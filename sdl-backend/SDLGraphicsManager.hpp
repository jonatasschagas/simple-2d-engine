#pragma once
#ifndef SDLGraphicsManager_hpp
#define SDLGraphicsManager_hpp

#include "LTexture.hpp"
#include "SDL.h"
#include "platform/GraphicsManager.hpp"
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

class SDLGraphicsManager : public GraphicsManager {
 public:
  SDLGraphicsManager(SDL_Renderer* pRenderer, int screenWidth,
                     int screenHeight);
  void renderTexture(DrawCall const& drawCall) override;
  void setOffset(float x, float y) override;

  void* loadTexture(string const& path) override;

  int const getWorldLocationXFromScreenCoordinates(int x) const override;
  int const getWorldLocationYFromScreenCoordinates(int y) const override;

  Vector2 const getScreenSizeInGameUnits() const override;

  int getScreenWidth() const override;
  int getScreenHeight() const override;

  ~SDLGraphicsManager();

 private:
  SDL_Renderer* m_pRenderer;
  vector<LTexture*> m_textures;
  vector<string> m_texturesNames;
  map<string, int> m_textureMap;
  int m_screenWidth;
  int m_screenHeight;
  float m_scaleFactorX;
  float m_scaleFactorY;
  float m_currentOffsetX;
  float m_currentOffsetY;
  int m_screenWidthInGameUnits;
  int m_screenHeightInGameUnits;

  void initializeMembers() {
    m_pRenderer = NULL;
    m_textures.clear();
    m_texturesNames.clear();
    m_textureMap.clear();
    m_scaleFactorX = 0.f;
    m_scaleFactorY = 0.f;
    m_screenWidthInGameUnits = 0;
    m_screenHeightInGameUnits = 0;
    m_currentOffsetX = 0;
    m_currentOffsetY = 0;
  }
};

#endif /* SDLGraphicsManager_hpp */