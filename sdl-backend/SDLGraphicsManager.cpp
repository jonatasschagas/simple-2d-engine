#include "SDLGraphicsManager.hpp"

SDLGraphicsManager::SDLGraphicsManager(SDL_Renderer* pRenderer, int screenWidth,
                                       int screenHeight) {
  initializeMembers();

  m_pRenderer = pRenderer;

  m_screenWidth = screenWidth;
  m_screenHeight = screenHeight;

  float aspectRatio = screenWidth / (screenHeight * 1.f);

  m_screenWidthInGameUnits = 100;
  // the number of vertical units depends on the aspect ratio from the device
  m_screenHeightInGameUnits = ceil(m_screenWidthInGameUnits / aspectRatio);

  m_scaleFactorX = (screenWidth * 1.0f) / m_screenWidthInGameUnits;
  m_scaleFactorY = (screenHeight * 1.0f) / m_screenHeightInGameUnits;
}

void SDLGraphicsManager::renderTexture(DrawCall const& drawCall) {
  string path = drawCall.textureSettings.name;

  SDL_Rect textureClip;
  textureClip.x = drawCall.textureSettings.x;
  textureClip.y = drawCall.textureSettings.y;
  textureClip.w = drawCall.textureSettings.w;
  textureClip.h = drawCall.textureSettings.h;

  int const index = m_textureMap.at(path);
  LTexture* pTexture = m_textures.at(index);

  float width = drawCall.spriteProperties.w;
  float height = drawCall.spriteProperties.h;
  float worldX = drawCall.spriteProperties.x;
  float worldY = drawCall.spriteProperties.y;

  worldY += m_currentOffsetX;
  worldY += m_currentOffsetY;

  if (drawCall.settings.scale) {
    width = width * m_scaleFactorX;
    height = height * m_scaleFactorY;
  }

  // scaling to the size of the world
  worldX = worldX * m_scaleFactorX - width / 2;
  worldY = worldY * m_scaleFactorY - height / 2;

  // applying alpha
  int alpha = drawCall.textureSettings.alpha * 255;
  pTexture->setAlpha(alpha);

  // render the sprite
  pTexture->render(m_pRenderer, worldX, worldY, &textureClip, width, height, 0,
                   drawCall.settings.flipHorizontal);
}

void SDLGraphicsManager::setOffset(float x, float y) {
  m_currentOffsetX = x;
  m_currentOffsetY = y;
}

void* SDLGraphicsManager::loadTexture(string const& path) {
  if (!m_pRenderer) {
    printf(
        "SDLManager has not been initialized yet! SDL_Renderer is null. !\n");
    return nullptr;
  }

  map<string, int>::iterator itTexMap = m_textureMap.find(path);
  if (itTexMap != m_textureMap.end()) {
    // texture already loaded
    int const index = m_textureMap.at(path);
    LTexture* pTexture = m_textures.at(index);
    return pTexture->getTexture();
  }

  LTexture* pNewTexture = new LTexture();

  // Loading success flag
  bool success = true;

  // Load sprite sheet texture
  if (!pNewTexture->loadFromFile(m_pRenderer, path)) {
    printf("Failed to load texture!\n");
    success = false;
    return nullptr;
  } else {
    m_textures.push_back(pNewTexture);
    m_texturesNames.push_back(path);
    int const index = (int)m_textures.size() - 1;
    m_textureMap[path] = index;
    return pNewTexture->getTexture();
  }
}

int const SDLGraphicsManager::getWorldLocationXFromScreenCoordinates(
    int x) const {
  return x / m_scaleFactorX;
}

int const SDLGraphicsManager::getWorldLocationYFromScreenCoordinates(
    int y) const {
  return m_screenHeightInGameUnits - y / m_scaleFactorY;
}

const Vector2 SDLGraphicsManager::getScreenSizeInGameUnits() const {
  return Vector2(m_screenWidthInGameUnits, m_screenHeightInGameUnits);
}

int SDLGraphicsManager::getScreenWidth() const { return m_screenWidth; }

int SDLGraphicsManager::getScreenHeight() const { return m_screenHeight; }

SDLGraphicsManager::~SDLGraphicsManager() {
  for (int i = 0; i < m_textures.size(); i++) {
    auto pSDLTex = m_textures.at(i);
    pSDLTex->free();
    pSDLTex = nullptr;
  }
  initializeMembers();
}
