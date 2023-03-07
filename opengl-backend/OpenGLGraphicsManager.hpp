#pragma once
#ifndef OpenGLGraphicsManager_hpp
#define OpenGLGraphicsManager_hpp

#include "SpriteRenderer.hpp"
#include "platform/GraphicsManager.hpp"

class OpenGLGraphicsManager : public GraphicsManager {
 public:
  OpenGLGraphicsManager(int screenWidth, int screenHeight,
                        int screenWidthInGameUnits);
  ~OpenGLGraphicsManager();

  void initialize() override;

  void setOffset(float x, float y) override;
  void renderTexture(DrawCall const& drawCall) override;
  void* loadTexture(string const& path) override;

  int const getWorldLocationXFromScreenCoordinates(int x) const override;
  int const getWorldLocationYFromScreenCoordinates(int y) const override;

  const Vector2 getScreenSizeInGameUnits() const override;
  int getScreenWidth() const override;
  int getScreenHeight() const override;

 private:
  SpriteRenderer m_spriteRenderer;
  float m_offsetX;
  float m_offsetY;
  int m_screenWidth;
  int m_screenHeight;
  int m_screenWidthInGameUnits;
  int m_screenHeightInGameUnits;
  float m_scaleFactorX;
  float m_scaleFactorY;

  void initializeMembers() {
    m_offsetX = 0.0f;
    m_offsetY = 0.0f;
    m_screenWidth = 0;
    m_screenHeight = 0;
    m_screenWidthInGameUnits = 0;
    m_screenHeightInGameUnits = 0;
    m_scaleFactorX = 0;
    m_scaleFactorY = 0;
  }
};

#endif /* OpenGLGraphicsManager_hpp */