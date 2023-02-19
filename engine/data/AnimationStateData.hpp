#pragma once
#ifndef AnimationStateData_hpp
#define AnimationStateData_hpp

#include <stdio.h>
#include <string>
#include <vector>

#include "JSONTypes.h"

using namespace std;

class AnimationStateData
{
public:
    
    AnimationStateData(JSONObject* pJSON);
    ~AnimationStateData()
    {
        initializeMembers();
    }
    
    const string& getName() { return m_name; };
    const string& getSoundEffect() { return m_soundEffect; };
    const bool isPlayOnce() { return m_playOnce; };
    const bool isAdvanceAnimationManually() { return m_advanceAnimationManually; };
    const vector<string>& getSpriteNames() { return m_spriteNames; };
    const float getTimePerSprite() { return m_timePerSprite; };
    const float getOffsetX() { return m_offsetX; };
    const float getOffsetY() { return m_offsetY; };
    
private:
    
    string m_name;
    string m_soundEffect;
    bool m_playOnce;
    bool m_advanceAnimationManually;
    vector<string> m_spriteNames;
    float m_timePerSprite;
    float m_offsetX;
    float m_offsetY;
    
    void initializeMembers()
    {
        m_playOnce = false;
        m_advanceAnimationManually = false;
        m_timePerSprite = 0;
        m_offsetX = 0;
        m_offsetY = 0;
        m_name = "";
        m_soundEffect = "";
        m_spriteNames.clear();
    }
    
};

#endif /* AnimationStateData_hpp */
