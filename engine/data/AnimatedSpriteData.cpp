#include "AnimatedSpriteData.hpp"
#include "AnimationStateData.hpp"

#include "../utils/FileUtils.h"

AnimatedSpriteData::AnimatedSpriteData(const string& configurationJSONFilename)
{
    initializeMembers();
    
    string configurationJSON = loadFile(configurationJSONFilename);
    Document configurationDocument;
    configurationDocument.Parse(configurationJSON.c_str());
    
    m_spritesheetConfigFile = configurationDocument.FindMember("spriteSheetConfig")->value.GetString();
    m_spritesheetTextureFile = configurationDocument.FindMember("spriteSheetImage")->value.GetString();
    
    auto spritesArray = configurationDocument.FindMember("states")->value.GetArray();
    
    for(int i = 0; i < spritesArray.Size(); i++)
    {
        JSONObject spriteJSON = spritesArray[i].GetObject();
        string spriteName = spriteJSON.FindMember("name")->value.GetString();
        m_animationsMap[spriteName] = new AnimationStateData(&spriteJSON);
    }
}

AnimatedSpriteData::~AnimatedSpriteData()
{
    for( auto it = m_animationsMap.begin(); it != m_animationsMap.end(); ++it )
    {
        auto pData = it->second;
        delete pData;
    }
    
    initializeMembers();
}

AnimationStateData* AnimatedSpriteData::getAnimation(const string& animationName) const
{
    return m_animationsMap.at(animationName);
}

bool AnimatedSpriteData::hasAnimation(const string& animationName) const
{
    auto it = m_animationsMap.find(animationName);
    return !(it == m_animationsMap.end());
}
