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

DataCacheManager::DataCacheManager() {}

DataCacheManager::~DataCacheManager() {}

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
  return m_spriteCache.getData(config, img);
}

AnimatedSpriteData const& DataCacheManager::getAnimatedSprite(
    string const& config) {
  return m_animatedSpriteCache.getData(config);
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
