#pragma once
#ifndef DataCacheManager_hpp
#define DataCacheManager_hpp

#include "AnimatedSpriteData.hpp"
#include "DataCache.hpp"
#include "SpritesheetData.hpp"
#include <mutex>
#include <stdio.h>
#include <string>

using namespace std;

class DataCacheManagerDestroyer;

class DataCacheManager {
 public:
  /**
   * DataCacheManager should not be cloneable.
   */
  DataCacheManager(DataCacheManager& other) = delete;

  /**
   * DataCacheManager should not be assignable.
   */
  void operator=(DataCacheManager const&) = delete;

  static DataCacheManager* getInstance();

  SpritesheetData const& getSprite(string const& config, string const& img);
  AnimatedSpriteData const& getAnimatedSprite(string const& config);

  void updateEditor();

 protected:
  friend class DataCacheManagerDestroyer;
  virtual ~DataCacheManager();

 private:
  DataCacheManager();

  static DataCacheManager* sm_pInstance;
  static DataCacheManagerDestroyer sm_destroyer;
  static mutex sm_mutexInstance;

  DataCache<SpritesheetData> m_spriteCache;
  DataCache<AnimatedSpriteData> m_animatedSpriteCache;
};

class DataCacheManagerDestroyer {
 public:
  explicit DataCacheManagerDestroyer(DataCacheManager* = 0);
  ~DataCacheManagerDestroyer();
  void setSingleton(DataCacheManager* pDataCacheManager);

 private:
  DataCacheManager* m_pDataCacheManager;
};

#endif /* DataCacheManager_hpp */
