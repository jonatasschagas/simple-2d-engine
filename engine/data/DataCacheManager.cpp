#include "DataCacheManager.hpp"

#include "DataCache.hpp"
#include "SpritesheetData.hpp"

#ifdef __APPLE__
    #include <TargetConditionals.h>
#endif

#if defined(TARGET_OS_OSX) && defined(IMGUI_ENABLED)
#include "../../third-party/imgui/imgui.h"
#endif

DataCacheManager::DataCacheManager()
{
    initializeMembers();
}

DataCacheManager::~DataCacheManager()
{
    initializeMembers();
}

SpritesheetData* DataCacheManager::getSprite(const string& config, const string& img)
{
    return m_spriteCache.getData(config, img);
}

AnimatedSpriteData* DataCacheManager::getAnimatedSprite(const string& config)
{
    return m_animatedSpriteCache.getData(config);
}

void DataCacheManager::updateEditor()
{
}
