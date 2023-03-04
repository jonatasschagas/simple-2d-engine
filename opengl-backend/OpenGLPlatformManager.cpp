#include "OpenGLPlatformManager.hpp"
#include "ResourceManager.hpp"
#include "Shader.hpp"
#include "Texture2D.hpp"

OpenGLPlatformManager::OpenGLPlatformManager(int screenWidth, int screenHeight,
                                             int screenWidthInGameUnits)
    : PlatformManager() {
  initializeMembers();

  m_screenWidth = screenWidth;
  m_screenHeight = screenHeight;
  m_screenWidthInGameUnits = screenWidthInGameUnits;

  float aspectRatio = screenWidth / (screenHeight * 1.f);

  m_screenWidthInGameUnits = 100;
  // the number of vertical units depends on the aspect ratio from the device
  m_screenHeightInGameUnits = ceil(m_screenWidthInGameUnits / aspectRatio);

  m_scaleFactorX = ((float)screenWidth) / m_screenWidthInGameUnits;
  m_scaleFactorY = ((float)screenHeight) / m_screenHeightInGameUnits;
}

OpenGLPlatformManager::~OpenGLPlatformManager() {}

void OpenGLPlatformManager::initialize() {
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

void OpenGLPlatformManager::setOffsetY(float y) { m_offsetY = y; }

void OpenGLPlatformManager::renderTexture(DrawCall const& drawCall) {
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

void OpenGLPlatformManager::playSoundEffect(string const& name) {}

void OpenGLPlatformManager::playMusic(string const& path) {}

void OpenGLPlatformManager::stopSounds() {}

bool OpenGLPlatformManager::loadMusic(string const& path) { return false; }

bool OpenGLPlatformManager::loadSoundEffect(string const& name,
                                            string const& path) {
  return false;
}

void* OpenGLPlatformManager::loadTexture(string const& path) {
  return &ResourceManager::getInstance()->loadTexture(path, path);
}

int const OpenGLPlatformManager::getWorldLocationXFromScreenCoordinates(
    int x) const {
  return 0;
}

int const OpenGLPlatformManager::getWorldLocationYFromScreenCoordinates(
    int y) const {
  return 0;
}

const Vector2 OpenGLPlatformManager::getScreenSizeInGameUnits() const {
  return Vector2(m_screenWidthInGameUnits, m_screenHeightInGameUnits);
}

int OpenGLPlatformManager::getScreenWidth() const { return m_screenWidth; }

int OpenGLPlatformManager::getScreenHeight() const { return m_screenHeight; }

void OpenGLPlatformManager::setDebugMode(bool debugMode) {
  m_debugMode = debugMode;
}

bool OpenGLPlatformManager::isDebugMode() const { return m_debugMode; }

unsigned int OpenGLPlatformManager::getTicks() const { return 0; }

bool OpenGLPlatformManager::shouldScale() const { return false; }
