#include "OpenGLGraphicsManager.hpp"
#include "ResourceManager.hpp"
#include "Shader.hpp"
#include "Texture2D.hpp"

OpenGLGraphicsManager::OpenGLGraphicsManager(int screenWidth, int screenHeight,
                                             int screenWidthInGameUnits)
    : GraphicsManager() {
  initializeMembers();

  m_screenWidth = screenWidth;
  m_screenHeight = screenHeight;
  m_screenWidthInGameUnits = screenWidthInGameUnits;

  float aspectRatio = screenWidth / (screenHeight * 1.f);

  // the number of vertical units depends on the aspect ratio from the device
  m_screenHeightInGameUnits = ceil(m_screenWidthInGameUnits / aspectRatio);

  m_scaleFactorX = ((float)screenWidth) / m_screenWidthInGameUnits;
  m_scaleFactorY = ((float)screenHeight) / m_screenHeightInGameUnits;
}

OpenGLGraphicsManager::~OpenGLGraphicsManager() {}

void OpenGLGraphicsManager::initialize() {
  // load shaders
  ResourceManager::getInstance()->loadShader(
      "assets/shaders/sprite.vs", "assets/shaders/sprite.frag", "sprite");
  // configure shaders
  glm::mat4 projection = glm::ortho(0.0f, (float)m_screenWidth,
                                    (float)m_screenHeight, 0.0f, -1.0f, 1.0f);
  ResourceManager::getInstance()->getShader("sprite").use().setInteger("image",
                                                                       0);
  ResourceManager::getInstance()->getShader("sprite").setMatrix4("projection",
                                                                 projection);
}

void OpenGLGraphicsManager::setOffset(float x, float y) {
  m_offsetX = x;
  m_offsetY = y;
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

void* OpenGLGraphicsManager::loadTexture(string const& path) {
  return &ResourceManager::getInstance()->loadTexture(path, path);
}

int const OpenGLGraphicsManager::getWorldLocationXFromScreenCoordinates(
    int x) const {
  return 0;
}

int const OpenGLGraphicsManager::getWorldLocationYFromScreenCoordinates(
    int y) const {
  return 0;
}

const Vector2 OpenGLGraphicsManager::getScreenSizeInGameUnits() const {
  return Vector2(m_screenWidthInGameUnits, m_screenHeightInGameUnits);
}

int OpenGLGraphicsManager::getScreenWidth() const { return m_screenWidth; }

int OpenGLGraphicsManager::getScreenHeight() const { return m_screenHeight; }
