#pragma once
#ifndef AnimatedSpriteData_hpp
#define AnimatedSpriteData_hpp

#include <stdio.h>
#include <string>
#include <map>

#include "JSONTypes.h"

using namespace std;

class AnimationStateData;

class AnimatedSpriteData
{
public:
    
    AnimatedSpriteData(const string& configurationJSONFilename);
    ~AnimatedSpriteData();
    
    const string& getConfigFile() const { return m_spritesheetConfigFile; };
    const string& getTextureFile() const { return m_spritesheetTextureFile; };
    AnimationStateData* getAnimation(const string& animationName) const;
    bool hasAnimation(const string& animationName) const;
    
private:
    
    string m_spritesheetConfigFile;
    string m_spritesheetTextureFile;
    
    map<string,AnimationStateData*> m_animationsMap;
    
    void initializeMembers()
    {
        m_spritesheetTextureFile = "";
        m_spritesheetConfigFile = "";
        m_animationsMap.clear();
    }
    
};

#endif /* AnimatedSpriteData_hpp */
