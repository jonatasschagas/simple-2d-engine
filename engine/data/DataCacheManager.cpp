#include "DataCacheManager.hpp"
#include "DataCache.hpp"
#include "SpritesheetData.hpp"

#ifdef __APPLE__
#include <TargetConditionals.h>
#endif

#if defined(TARGET_OS_OSX) && defined(IMGUI_ENABLED)
#include "../../third-party/imgui/imgui.h"
#endif

DataCacheManager* DataCacheManager::sm_pInstance{nullptr};
mutex DataCacheManager::sm_mutexInstance;
DataCacheManagerDestroyer DataCacheManager::sm_destroyer;

DataCacheManager::DataCacheManager() { initializeMembers(); }

DataCacheManager::~DataCacheManager() {
  delete m_pSpriteCache;
  delete m_pAnimatedSpriteCache;
  delete m_pTileMapCache;
  delete m_pResourceProvider;
  initializeMembers();
}

DataCacheManager* DataCacheManager::getInstance() {
  lock_guard<mutex> lock(sm_mutexInstance);
  if (sm_pInstance == nullptr) {
    sm_pInstance = new DataCacheManager();
    sm_destroyer.setSingleton(sm_pInstance);
  }
  return sm_pInstance;
}

SpritesheetData const& DataCacheManager::getSprite(string const& config,
                                                   string const& img) {
  // make sure to set the resource provider before using the data cache manager
  assert(m_pSpriteCache != nullptr);
  return m_pSpriteCache->getData(config, img);
}

AnimatedSpriteData const& DataCacheManager::getAnimatedSprite(
    string const& config) {
  // make sure to set the resource provider before using the data cache manager
  assert(m_pAnimatedSpriteCache != nullptr);
  return m_pAnimatedSpriteCache->getData(config);
}

TileMapData const& DataCacheManager::getTileMapData(string const& config,
                                                    string const& levelsFolder,
                                                    string const& tilesFolder) {
  assert(m_pTileMapCache != nullptr);
  return m_pTileMapCache->getData(config, levelsFolder, tilesFolder);
}

void DataCacheManager::updateEditor() {}

DataCacheManagerDestroyer::DataCacheManagerDestroyer(
    DataCacheManager* pDataCacheManager) {
  m_pDataCacheManager = pDataCacheManager;
}

DataCacheManagerDestroyer::~DataCacheManagerDestroyer() {
  delete m_pDataCacheManager;
}

void DataCacheManagerDestroyer::setSingleton(
    DataCacheManager* pDataCacheManager) {
  m_pDataCacheManager = pDataCacheManager;
}

void DataCacheManager::setResourceProvider(
    ResourceProvider* pResourceProvider) {
  m_pResourceProvider = pResourceProvider;

  m_pSpriteCache = new DataCache<SpritesheetData>(*m_pResourceProvider);
  m_pAnimatedSpriteCache =
      new DataCache<AnimatedSpriteData>(*m_pResourceProvider);
  m_pTileMapCache = new DataCache<TileMapData>(*m_pResourceProvider);
}