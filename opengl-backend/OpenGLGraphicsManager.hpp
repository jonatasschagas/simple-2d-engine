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
  OpenGLGraphicsManager(int screenWidth, int screenHeight,
                        int screenWidthInGameUnits,
                        ResourceProvider& rResourceProvider,
                        string& rVertexShaderPath, string& rFragmentShaderPath,
                        string& rColorShaderPath,
                        string& rColorFragmentShaderPath);

  ~OpenGLGraphicsManager();

  void initialize() override;

  void setOffset(float x, float y) override;

  void renderTexture(glm::mat4 const& transform,
                     glm::vec4 const& textureCoordinates,
                     string const& texturePath) override;

  Texture loadTexture(string const& path) override;

  void renderColoredSprite(glm::mat4 const& transform,
                           glm::vec4 const& color) override;

  int const getWorldLocationXFromScreenCoordinates(int x) const override;
  int const getWorldLocationYFromScreenCoordinates(int y) const override;

  Vector2 const getScreenSizeInGameUnits() const override;
  int getScreenWidth() const override;
  int getScreenHeight() const override;

  void getScaleFactor(float& x, float& y) const override;

  void initializeShader(string const& shaderName,
                        string const& vertexShaderPath,
                        string const& fragmentShaderPath);

 private:
  SpriteRenderer m_spriteRenderer;
  ResourceProvider& m_rResourceProvider;
  float m_offsetX = 0;
  float m_offsetY = 0;
  int m_screenWidth = 0;
  int m_screenHeight = 0;
  int m_screenWidthInGameUnits = 0;
  int m_screenHeightInGameUnits = 0;
  float m_scaleFactorX = 0;
  float m_scaleFactorY = 0;
  string m_vertexShaderPath = "";
  string m_fragmentShaderPath = "";
  string m_colorShaderPath = "";
  string m_colorFragmentShaderPath = "";
};

#endif /* OpenGLGraphicsManager_hpp */
