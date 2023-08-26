#include "TileMapSprite.hpp"
#include "data/TileMapData.hpp"

TileMapSprite::TileMapSprite() : Sprite() { initializeMembers(); }

TileMapSprite::TileMapSprite(Vector2 const& tileSizeWorldUnits,
                             TileMapData const* pMapData)
    : Sprite(), m_pCurrentMapData(pMapData) {
  initializeMembers();

  m_tileSizeInWorldUnits = tileSizeWorldUnits;

  setPivotAtCenter();
  loadMap("meta");
}

TileMapSprite::TileMapSprite(Vector2 const& tileSizeWorldUnits,
                             TileMapData const* pMapData,
                             TileMapMetaTileFactory* pTileMapMetaTileFactory,
                             string const& metaLayerName)
    : Sprite(), m_pCurrentMapData(pMapData) {
  initializeMembers();

  m_tileSizeInWorldUnits = tileSizeWorldUnits;
  m_pTileMapMetaTileFactory = pTileMapMetaTileFactory;

  setPivotAtCenter();
  loadMap(metaLayerName);
}

TileMapSprite::~TileMapSprite() { initializeMembers(); }

void TileMapSprite::update(float delta) {
  Sprite::update(delta);

  if (m_disableCamera) return;

  float x = getGamePosition().x;
  float y = getGamePosition().y;
  float targetX = -m_xOffSet;
  float targetY = -m_yOffSet;

  // smoothing the camera
  // http://www.mathforgameprogrammers.com/gdc2016/GDC2016_Eiserloh_Squirrel_JuicingYourCameras.pdf
  x = (.8 * x) + (.2 * targetX);
  y = (.8 * y) + (.2 * targetY);

  setXY(x, y);
}

void TileMapSprite::setDisableCamera(bool disableCamera) {
  m_disableCamera = disableCamera;
}

void TileMapSprite::loadMap(string const& metaLayerName) {
  m_curretMapMetaLayerName = metaLayerName;

  // creates the map as a huge sprite
  setXY(0, 0);
  setPivotAtCenter();

  m_mapSizeInGameUnits.x =
      m_pCurrentMapData->getWidth() * m_tileSizeInWorldUnits.x;
  m_mapSizeInGameUnits.y =
      m_pCurrentMapData->getHeight() * m_tileSizeInWorldUnits.y;
  setSize(m_mapSizeInGameUnits.x, m_mapSizeInGameUnits.y);

  loadMapLayers();
}

void TileMapSprite::loadMapLayers() {
  vector<TileMapLayer*> const& layersArray = m_pCurrentMapData->getLayers();
  for (int i = 0; i < layersArray.size(); i++) {
    TileMapLayer* pLayer = layersArray[i];
    string const& layerName = pLayer->getName();
    if (pLayer->isVisible()) {
      Sprite* pSpriteLayer = new Sprite();
      pSpriteLayer->setXY(0, 0);
      pSpriteLayer->setSize(pLayer->getWidth() * m_tileSizeInWorldUnits.x,
                            pLayer->getHeight() * m_tileSizeInWorldUnits.y);
      pSpriteLayer->setPivotAtCenter();
      pSpriteLayer->setTileMap(true);
      addChild(pSpriteLayer);

      if (m_curretMapMetaLayerName.compare(layerName) == 0) {
        m_pCurrentMapMetaLayer = pLayer;
      }

      for (int x = 0; x < pLayer->getWidth(); x++) {
        for (int y = 0; y < pLayer->getHeight(); y++) {
          if (m_curretMapMetaLayerName.compare(layerName) == 0 &&
              m_pTileMapMetaTileFactory != nullptr) {
            createMetaTile(x, y, pSpriteLayer, pLayer);
          } else {
            createTile(x, y, pSpriteLayer, pLayer);
          }
        }
      }
    }
  }
}

float const TileMapSprite::getWorldLimitX() const {
  return m_pCurrentMapData->getWidth() * m_tileSizeInWorldUnits.x;
}

int TileMapSprite::getTileX(float x) const {
  return (int)(x / m_tileSizeInWorldUnits.x);
}

int TileMapSprite::getTileY(float y) const {
  return (int)floor(y / m_tileSizeInWorldUnits.y);
}

int TileMapSprite::getTileMapWidth() const {
  return m_pCurrentMapData->getWidth();
}

int TileMapSprite::getTileMapHeight() const {
  return m_pCurrentMapData->getHeight();
}

float TileMapSprite::getXOffSet() const { return m_xOffSet; }

void TileMapSprite::setXOffSet(float xOffSet) { m_xOffSet = xOffSet; }

float TileMapSprite::getYOffSet() const { return m_yOffSet; }

void TileMapSprite::setYOffSet(float yOffSet) { m_yOffSet = yOffSet; }

int TileMapSprite::getTileData(int tileX, int tileY,
                               string const& tileLayerName) const {
  TileMapLayer* pTileLayer = nullptr;
  vector<TileMapLayer*> const& layers = m_pCurrentMapData->getLayers();
  for (int i = 0; i < layers.size(); i++) {
    TileMapLayer* pLayer = layers[i];
    if (strcmp(pLayer->getName().c_str(), tileLayerName.c_str()) == 0) {
      pTileLayer = pLayer;
      break;
    }
  }

  assert(pTileLayer != nullptr);

  vector<int> const& tiles = pTileLayer->getData();
  int index = tileY * pTileLayer->getWidth() + tileX;

  if (index >= tiles.size()) {
    return -1;
  }

  return tiles[index];
}

int TileMapSprite::getTileData(float x, float y,
                               string const& tileLayerName) const {
  return getTileData(getTileX(x), getTileY(y), tileLayerName);
}

void TileMapSprite::createTile(int x, int y, Sprite* pSpriteLayer,
                               TileMapLayer* pLayer) {
  // reading texture coordinates
  int tileMapIndex = y * m_pCurrentMapData->getWidth() + x;
  vector<int> const& tileDataArray = pLayer->getData();

  if (tileDataArray.size() <= tileMapIndex) {
    // invalid tile coordinates
    return;
  }

  int tileType = tileDataArray[tileMapIndex];

  TileSet* pTileSet = m_pCurrentMapData->getTileSetFromTileData(tileType);
  if (pTileSet == NULL) {
    // no tile set for this tileType
    return;
  }

  TileSetConfig* pTileSetConfig = pTileSet->getConfig();

  int tileNumberInTileSet = tileType - pTileSet->getFirstGid();

  TileConfig const* pTileConfig =
      pTileSetConfig->getTileConfig(tileNumberInTileSet);

  // finally, creating the sprite
  int width = m_tileSizeInWorldUnits.x;
  int height = m_tileSizeInWorldUnits.y;

  Sprite* pTileSprite = new Sprite();
  pTileSprite->setXY(x * width, y * height);
  pTileSprite->setSize(width, height);
  pTileSprite->setPivotAtCenter();
  pTileSprite->setTextureCoordinates(pTileConfig->getX(), pTileConfig->getY(),
                                     pTileConfig->getWidth(),
                                     pTileConfig->getHeight());
  pTileSprite->setTileMap(true);

  pTileSprite->loadTexture(pTileConfig->getImageName());
  pSpriteLayer->addChild(pTileSprite);
}

void TileMapSprite::createMetaTile(int x, int y, Sprite* pSpriteLayer,
                                   TileMapLayer* pLayer) {
  // reading texture coordinates
  int tileMapIndex = y * m_pCurrentMapData->getWidth() + x;
  vector<int> const& tileDataArray = pLayer->getData();

  if (tileDataArray.size() <= tileMapIndex) {
    // invalid tile coordinates
    return;
  }

  int tileType = tileDataArray[tileMapIndex];

  TileSet* pTileSet = m_pCurrentMapData->getTileSetFromTileData(tileType);
  if (pTileSet == NULL) {
    // no tile set for this tileType
    return;
  }

  TileSetConfig* pTileSetConfig = pTileSet->getConfig();

  int tileNumberInTileSet = tileType - pTileSet->getFirstGid();

  TileConfig const* pTileConfig =
      pTileSetConfig->getTileConfig(tileNumberInTileSet);

  int width = m_tileSizeInWorldUnits.x;
  int height = m_tileSizeInWorldUnits.y;
  Vector2 position(x * width, y * height);
  Vector2 size(width, height);

  Sprite* pMetaTileSprite = m_pTileMapMetaTileFactory->createMetaTile(
      x, y, pTileConfig, position, size);

  if (pMetaTileSprite == nullptr) {
    return;
  }

  if (pMetaTileSprite->getGamePosition() == Vector2::ZERO) {
    pMetaTileSprite->setXY(position.x, position.y);
  }

  if (pMetaTileSprite->getWidth() == 0 && pMetaTileSprite->getHeight() == 0) {
    pMetaTileSprite->setSize(size.x, size.y);
  }

  pMetaTileSprite->setPivotAtCenter();
  pMetaTileSprite->setTileMap(true);

  pSpriteLayer->addChild(pMetaTileSprite);
}

Vector2 const& TileMapSprite::getTileSizeInGameUnits() const {
  return m_tileSizeInWorldUnits;
}

Vector2 const& TileMapSprite::getMapSizeInGameUnits() const {
  return m_mapSizeInGameUnits;
}

bool TileMapSprite::isVisibleInParent(
    GraphicsManager const& rGraphicsManager) const {
  /*
  // not rendering/updating tiles that are not visible within the camera offset
  Vector2 const& screenSize = rGraphicsManager.getScreenSizeInGameUnits();

  Vector2 childCoords = getGamePosition();
  float lowerLimitX = m_xOffSet - m_tileSizeInWorldUnits.x;
  float higherLimitX = m_xOffSet + screenSize.x + m_tileSizeInWorldUnits.x;

  if (childCoords.x < lowerLimitX || childCoords.x > higherLimitX) return false;

  float lowerLimitY = m_yOffSet - m_tileSizeInWorldUnits.y;
  float higherLimitY = m_yOffSet + screenSize.y + m_tileSizeInWorldUnits.y;

  if (childCoords.y < lowerLimitY || childCoords.y > higherLimitY) return false;

  return true;
  */
  return true;
}
