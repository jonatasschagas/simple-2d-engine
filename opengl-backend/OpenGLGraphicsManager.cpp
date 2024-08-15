#include "OpenGLGraphicsManager.hpp"
#include "ResourceManager.hpp"
#include "Shader.hpp"
#include "Texture2D.hpp"

OpenGLGraphicsManager::OpenGLGraphicsManager(
    int screenWidth, int screenHeight, int screenWidthInGameUnits,
    ResourceProvider& rResourceProvider, string& rVertexShaderPath,
    string& rFragmentShaderPath, string& rColorShaderPath,
    string& rColorFragmentShaderPath)
    : GraphicsManager(), m_rResourceProvider(rResourceProvider) {
  m_screenWidth = screenWidth;
  m_screenHeight = screenHeight;
  m_screenWidthInGameUnits = screenWidthInGameUnits;
  m_vertexShaderPath = rVertexShaderPath;
  m_fragmentShaderPath = rFragmentShaderPath;
  m_colorShaderPath = rColorShaderPath;
  m_colorFragmentShaderPath = rColorFragmentShaderPath;

  float aspectRatio = (float)screenWidth / (float)screenHeight;

  // the number of vertical units depends on the aspect ratio of the device
  m_screenHeightInGameUnits = ceil(m_screenWidthInGameUnits / aspectRatio);

  m_scaleFactorX = ((float)screenWidth) / m_screenWidthInGameUnits;
  m_scaleFactorY = ((float)screenHeight) / m_screenHeightInGameUnits;
}

OpenGLGraphicsManager::~OpenGLGraphicsManager() {}

void OpenGLGraphicsManager::initialize() {
  initializeShader("sprite", m_vertexShaderPath, m_fragmentShaderPath);
  initializeShader("coloredSprite", m_colorShaderPath,
                   m_colorFragmentShaderPath);
}

void OpenGLGraphicsManager::initializeShader(string const& shaderName,
                                             string const& vertexShaderPath,
                                             string const& fragmentShaderPath) {
  // load shaders
  ResourceManager::getInstance()->loadShader(
      vertexShaderPath, fragmentShaderPath, shaderName, m_rResourceProvider);

  // configure shaders
  Shader& rShader = ResourceManager::getInstance()->getShader(shaderName);
  rShader.use();

  // assumes this projection matrix is used for all shaders
  glm::mat4 projection = glm::ortho(0.0f, (float)m_screenWidth,
                                    (float)m_screenHeight, 0.0f, -1.0f, 1.0f);
  rShader.setMatrix4("projection", projection);
}

void OpenGLGraphicsManager::setOffset(float x, float y) {
  m_offsetX = x;
  m_offsetY = y;
}

void OpenGLGraphicsManager::renderTexture(glm::mat4 const& transform,
                                          glm::vec4 const& textureCoordinates,
                                          string const& texturePath) {
  m_spriteRenderer.draw(ResourceManager::getInstance()->getShader("sprite"),
                        transform,
                        ResourceManager::getInstance()->getTexture(texturePath),
                        textureCoordinates);
}

void OpenGLGraphicsManager::renderColoredSprite(glm::mat4 const& transform,
                                                glm::vec4 const& color) {
  m_spriteRenderer.draw(
      ResourceManager::getInstance()->getShader("coloredSprite"), transform,
      color);
}

Texture OpenGLGraphicsManager::loadTexture(string const& path) {
  Texture2D& texture2D = ResourceManager::getInstance()->loadTexture(
      path, path, m_rResourceProvider);
  Texture texture;
  texture.texturePath = path;
  texture.width = texture2D.getWidth();
  texture.height = texture2D.getHeight();
  return texture;
}

int const OpenGLGraphicsManager::getWorldLocationXFromScreenCoordinates(
    int x) const {
  // TODO: Implement
  return 0;
}

int const OpenGLGraphicsManager::getWorldLocationYFromScreenCoordinates(
    int y) const {
  // TODO: Implement
  return 0;
}

Vector2 const OpenGLGraphicsManager::getScreenSizeInGameUnits() const {
  return Vector2(m_screenWidthInGameUnits, m_screenHeightInGameUnits);
}

int OpenGLGraphicsManager::getScreenWidth() const { return m_screenWidth; }

int OpenGLGraphicsManager::getScreenHeight() const { return m_screenHeight; }

void OpenGLGraphicsManager::getScaleFactor(float& x, float& y) const {
  x = m_scaleFactorX;
  y = m_scaleFactorY;
}