#pragma once
#ifndef OpenGLGraphicsManager_hpp
#define OpenGLGraphicsManager_hpp

#include "OpenGLResourceManager.hpp"
#include "OpenGLSpriteRenderer.hpp"
#include "disk/ResourceProvider.hpp"
#include "graphics/GraphicsManager.hpp"
#include <string>

using std::string;

class OpenGLGraphicsManager : public GraphicsManager {
 public:
  OpenGLGraphicsManager(int screenWidth, int screenHeight,
                        int screenWidthInGameUnits, float dpiX, float dpiY,
                        ResourceProvider& rResourceProvider);

  ~OpenGLGraphicsManager();

  void initialize() override;

  void loadShader(string const& shaderName, string const& vertexPath,
                  string const& fragmentPath,
                  ResourceProvider& rResourceProvider) override;

  void updateScreenSize(int width, int height);

  Shader& getShader(string const& shaderName) override;

  glm::vec2 const getScreenSizeInGameUnits() const override {
    return glm::vec2(m_screenWidthInGameUnits, m_screenHeightInGameUnits);
  }

  void renderTexture(glm::mat4 const& transform,
                     glm::vec4 const& textureCoordinates,
                     string const& texturePath, Shader& rShader) override;

  void renderColoredSprite(glm::mat4 const& transform,
                           Shader& rShader) override;

  Texture loadTexture(string const& path) override;

  int const getWorldLocationXFromScreenCoordinates(int x) const override;
  int const getWorldLocationYFromScreenCoordinates(int y) const override;

  int getScreenWidth() const override;
  int getScreenHeight() const override;

  void getScaleFactor(float& x, float& y) const override;

  void getDpi(float& x, float& y) const override {
    x = m_dpiX;
    y = m_dpiY;
  };

 private:
  OpenGLSpriteRenderer m_spriteRenderer;
  OpenGLResourceManager m_resourceManager;
  ResourceProvider& m_rResourceProvider;
  float m_dpiX = 1;
  float m_dpiY = 1;
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
