#pragma once
#ifndef OpenGLGraphicsManager_hpp
#define OpenGLGraphicsManager_hpp

#include "SpriteRenderer.hpp"
#include "platform/GraphicsManager.hpp"
#include "platform/ResourceProvider.hpp"
#include <string>

using namespace std;

class OpenGLGraphicsManager : public GraphicsManager {
 public:
  OpenGLGraphicsManager(int screenWidth,
                        int screenHeight,
                        int screenWidthInGameUnits,
                        ResourceProvider& rResourceProvider,
                        string& rVertexShaderPath,
                        string& rFragmentShaderPath);
  
  ~OpenGLGraphicsManager();

  void initialize() override;

  void setOffset(float x, float y) override;
  void renderTexture(const glm::mat4& transform, const glm::vec4& textureCoordinates, string const& texturePath) override;
  void renderTexture(DrawCall const& drawCall) override;
  Texture loadTexture(string const& path) override;

  int const getWorldLocationXFromScreenCoordinates(int x) const override;
  int const getWorldLocationYFromScreenCoordinates(int y) const override;

  const Vector2 getScreenSizeInGameUnits() const override;
  int getScreenWidth() const override;
  int getScreenHeight() const override;

 private:
  SpriteRenderer m_spriteRenderer;
  ResourceProvider& m_rResourceProvider;
  float m_offsetX;
  float m_offsetY;
  int m_screenWidth;
  int m_screenHeight;
  int m_screenWidthInGameUnits;
  int m_screenHeightInGameUnits;
  float m_scaleFactorX;
  float m_scaleFactorY;
  string m_vertexShaderPath;
  string m_fragmentShaderPath;

  void initializeMembers() {
    m_offsetX = 0.0f;
    m_offsetY = 0.0f;
    m_screenWidth = 0;
    m_screenHeight = 0;
    m_screenWidthInGameUnits = 0;
    m_screenHeightInGameUnits = 0;
    m_scaleFactorX = 0;
    m_scaleFactorY = 0;
    m_vertexShaderPath = "";
    m_fragmentShaderPath = "";
  }
};

#endif /* OpenGLGraphicsManager_hpp */
