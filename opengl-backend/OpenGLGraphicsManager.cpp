#include "OpenGLGraphicsManager.hpp"
#include "ResourceManager.hpp"
#include "Shader.hpp"
#include "Texture2D.hpp"
#include "data/DataCacheManager.hpp"

OpenGLGraphicsManager::OpenGLGraphicsManager(
    int screenWidth, int screenHeight, int screenWidthInGameUnits,
    ResourceProvider& rResourceProvider, string& rVertexShaderPath,
    string& rFragmentShaderPath)
    : GraphicsManager(), m_rResourceProvider(rResourceProvider) {
  initializeMembers();

  m_screenWidth = screenWidth;
  m_screenHeight = screenHeight;
  m_screenWidthInGameUnits = screenWidthInGameUnits;
  m_vertexShaderPath = rVertexShaderPath;
  m_fragmentShaderPath = rFragmentShaderPath;

  float aspectRatio = (float)screenWidth / (float)screenHeight;

  // the number of vertical units depends on the aspect ratio of the device
  m_screenHeightInGameUnits = ceil(m_screenWidthInGameUnits / aspectRatio);

  m_scaleFactorX = ((float)screenWidth) / m_screenWidthInGameUnits;
  m_scaleFactorY = ((float)screenHeight) / m_screenHeightInGameUnits;
}

OpenGLGraphicsManager::~OpenGLGraphicsManager() {}

void OpenGLGraphicsManager::initialize() {
  DataCacheManager::getInstance()->setResourceProvider(&m_rResourceProvider);

  // load shaders
  ResourceManager::getInstance()->loadShader(
      m_vertexShaderPath, m_fragmentShaderPath, "sprite", m_rResourceProvider);
  // configure shaders
  glm::mat4 projection = glm::ortho(0.0f, (float)m_screenWidth,
                                    (float)m_screenHeight, 0.0f, -1.0f, 1.0f);
  Shader& rShader = ResourceManager::getInstance()->getShader("sprite");
  rShader.use().setInteger("image", 0);
  rShader.setMatrix4("projection", projection);
}

void OpenGLGraphicsManager::setOffset(float x, float y) {
  m_offsetX = x;
  m_offsetY = y;
}

void OpenGLGraphicsManager::renderTexture(const glm::mat4& transform, const glm::vec4& textureCoordinates, string const& texturePath)
{
  
  glm::mat4 updatedMat = glm::translate(transform, glm::vec3(m_offsetX, m_offsetY, 0)) * glm::scale(glm::mat4(1.0f), glm::vec3(m_scaleFactorX, m_scaleFactorY, 0));
  
  m_spriteRenderer.draw(ResourceManager::getInstance()->getShader("sprite"),
                        updatedMat,
                        ResourceManager::getInstance()->getTexture(texturePath),
                        textureCoordinates);
}

void OpenGLGraphicsManager::renderTexture(DrawCall const& drawCall) {
  float width = drawCall.spriteProperties.w;
  float height = drawCall.spriteProperties.h;
  float worldX = drawCall.spriteProperties.x;
  float worldY = drawCall.spriteProperties.y;

  worldY += m_offsetY;

  if (drawCall.settings.scale) {
    width = width * m_scaleFactorX;
    height = height * m_scaleFactorY;
  }

  // scaling to the size of the world
  worldX = worldX * m_scaleFactorX - width / 2;
  worldY = worldY * m_scaleFactorY - height / 2;

  m_spriteRenderer.drawSprite(
      ResourceManager::getInstance()->getShader("sprite"),
      ResourceManager::getInstance()->getTexture(drawCall.textureSettings.name),
      glm::vec2(worldX, worldY), glm::vec2(width, height),
      glm::vec4(drawCall.textureSettings.x, drawCall.textureSettings.y,
                drawCall.textureSettings.w, drawCall.textureSettings.h),
      drawCall.spriteProperties.rotation);
}

Texture OpenGLGraphicsManager::loadTexture(string const& path) {
    Texture2D& texture2D = ResourceManager::getInstance()->loadTexture(path, path, m_rResourceProvider);
    Texture texture;
    texture.texturePath = path;
    texture.width = texture2D.getWidth();
    texture.height = texture2D.getHeight();
    return texture;
}

int const OpenGLGraphicsManager::getWorldLocationXFromScreenCoordinates(int x) const {
  //TODO: Implement
  return 0;
}

int const OpenGLGraphicsManager::getWorldLocationYFromScreenCoordinates(int y) const {
  //TODO: Implement
  return 0;
}

const Vector2 OpenGLGraphicsManager::getScreenSizeInGameUnits() const {
  return Vector2(m_screenWidthInGameUnits, m_screenHeightInGameUnits);
}

int OpenGLGraphicsManager::getScreenWidth() const { return m_screenWidth; }

int OpenGLGraphicsManager::getScreenHeight() const { return m_screenHeight; }
