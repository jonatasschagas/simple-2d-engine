#include "OpenGLGraphicsManager.hpp"
#include "OpenGLShader.hpp"
#include "OpenGLTexture2d.hpp"

OpenGLGraphicsManager::OpenGLGraphicsManager(
    int screenWidth, int screenHeight, int screenWidthInGameUnits,
    ResourceProvider& rResourceProvider)
    : GraphicsManager(), m_rResourceProvider(rResourceProvider) {
  m_screenWidth = screenWidth;
  m_screenHeight = screenHeight;
  m_screenWidthInGameUnits = screenWidthInGameUnits;

  float aspectRatio = (float)screenWidth / (float)screenHeight;

  // the number of vertical units depends on the aspect ratio of the device
  m_screenHeightInGameUnits = ceil(m_screenWidthInGameUnits / aspectRatio);

  m_scaleFactorX = ((float)screenWidth) / m_screenWidthInGameUnits;
  m_scaleFactorY = ((float)screenHeight) / m_screenHeightInGameUnits;
}

OpenGLGraphicsManager::~OpenGLGraphicsManager() {}

void OpenGLGraphicsManager::initialize() {}

void OpenGLGraphicsManager::renderTexture(glm::mat4 const& transform,
                                          glm::vec4 const& textureCoordinates,
                                          string const& texturePath,
                                          Shader& rShader) {
  m_spriteRenderer.draw(rShader, transform,
                        m_resourceManager.getTexture(texturePath),
                        textureCoordinates);
}

void OpenGLGraphicsManager::renderColoredSprite(glm::mat4 const& transform,
                                                Shader& rShader) {
  m_spriteRenderer.draw(rShader, transform);
}

Texture OpenGLGraphicsManager::loadTexture(string const& path) {
  OpenGLTexture2d& texture2D =
      m_resourceManager.loadTexture(path, path, m_rResourceProvider);
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

int OpenGLGraphicsManager::getScreenWidth() const { return m_screenWidth; }

int OpenGLGraphicsManager::getScreenHeight() const { return m_screenHeight; }

void OpenGLGraphicsManager::getScaleFactor(float& x, float& y) const {
  x = m_scaleFactorX;
  y = m_scaleFactorY;
}

void OpenGLGraphicsManager::loadShader(string const& shaderName,
                                       string const& vertexPath,
                                       string const& fragmentPath,
                                       ResourceProvider& rResourceProvider) {
  // load shaders
  Shader& rShader = m_resourceManager.loadShader(vertexPath, fragmentPath,
                                                 shaderName, rResourceProvider);

  rShader.use();

  // assumes this projection matrix is used for all shaders
  glm::mat4 projection = glm::ortho(0.0f, (float)m_screenWidth,
                                    (float)m_screenHeight, 0.0f, -1.0f, 1.0f);
  rShader.setMatrix4("projection", projection);
}

Shader& OpenGLGraphicsManager::getShader(string const& shaderName) {
  return m_resourceManager.getShader(shaderName);
}
