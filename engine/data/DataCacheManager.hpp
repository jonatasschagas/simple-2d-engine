#pragma once
#ifndef DataCacheManager_hpp
#define DataCacheManager_hpp

#include <stdio.h>
#include <string>

#include "DataCache.hpp"
#include "SpritesheetData.hpp"
#include "AnimatedSpriteData.hpp"
#include "TileMapData.hpp"

using namespace std;

class DataCacheManager
{
public:
    
    DataCacheManager();
    ~DataCacheManager();
    
    SpritesheetData* getSprite(const string& config, const string& img);
    AnimatedSpriteData* getAnimatedSprite(const string& config);

    void updateEditor();
    
private:
    
    DataCache<SpritesheetData> m_spriteCache;
    DataCache<AnimatedSpriteData> m_animatedSpriteCache;
    
    void initializeMembers()
    {
    }
    
};

#endif /* DataCacheManager_hpp */
