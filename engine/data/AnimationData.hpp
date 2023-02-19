#ifndef AnimationData_hpp
#define AnimationData_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include "AnimationData.hpp"
#include "JSONTypes.h"

#include "../core/Vector2.h"

using namespace std;

class AnimationData
{
public:
    
    AnimationData(const string& name, ConstJSONObject* pJSONObject);
    AnimationData(const string& name, JSONObject* pJSONObject);
    ~AnimationData();
    
    string loadNextSprite();
    
    const Vector2& getLeftOffset() const { return m_leftOffset; };
    const Vector2& getRightOffset() const { return m_rightOffset; };
    
    string getName() const { return m_name; };
    float getTimePerSprite() const { return m_timePerSprite; };
    bool isPlayOnce() const { return m_playOnce; };
    bool isAnimationFinished() const { return m_currentSpriteIndex + 1 >= m_sprites.size(); };
    void resetAnimation() { m_currentSpriteIndex = 0; }
    bool isAdvanceManually() const { return m_advanceAnimationManually; };
    string getSoundEffect() const { return m_soundEffect; };

private:
    
    string m_name;
    vector<string> m_sprites;
    float m_timePerSprite;
    bool m_playOnce;
    bool m_advanceAnimationManually;
    int m_currentSpriteIndex;
    Vector2 m_leftOffset;
    Vector2 m_rightOffset;
    string m_soundEffect;
    
    void initializeMembers()
    {
        m_name = "";
        m_sprites.clear();
        m_timePerSprite = 0.f;
        m_playOnce = false;
        m_advanceAnimationManually = false;
        m_currentSpriteIndex = 0;
        m_soundEffect = "";
    }
    
};

#endif /* AnimationData_hpp */
