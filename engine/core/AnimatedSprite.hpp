#pragma once
#ifndef AnimatedSprite_hpp
#define AnimatedSprite_hpp

#include <stdio.h>
#include <string>
#include <functional>
#include <map>
#include "../core/Sprite.hpp"

using namespace std;

class DataCacheManager;
class PlatformManager;
class AnimatedSpriteData;
class AnimationStateData;
class SpritesheetData;
class SpriteData;

class AnimatedSprite : public Sprite
{
public:
    
    AnimatedSprite(PlatformManager* pPlatformManager, DataCacheManager& rDataCacheManager, const string& animationFile);
    ~AnimatedSprite();
    
    void update(float delta) override;
    void render() override;
    void play(const string& animationName, const bool flip=false);
    
    const bool hasAnimation(const string& animationName) const;
    const bool isAnimationFinished(const string& animationName) const;
    AnimationStateData* getCurrentAnimationState() const { return m_pCurrentAnimationStateData; };
    const string& getCurrentAnimationName() const;
    const bool isPlaying(const string& animationName) const;
    float getProgressAnimation() const;
    
    bool isVisibleInParent(Sprite* pChild) const override;
    
    void stopAnimation() { m_stopAnimation = true; }
    void resumeAnimation() { m_stopAnimation = false; }
    bool isAnimationStopped() const { return m_stopAnimation; }

    void setOnAnimationFinishedCallback(const string& animationName, function<void()> callback) { m_animationFinishedCallbacks[animationName] = callback; }

private:
    
    void advanceStep();
    bool isAtLastSprite() const;
    
    DataCacheManager& m_rDataCacheManager;
    const AnimatedSpriteData* m_pAnimatedSpriteData;
    AnimationStateData* m_pCurrentAnimationStateData;
    SpritesheetData* m_pSpritesheetData;
    SpriteData* m_pCurrentSpriteData;
    
    int m_currentAnimationStateIndex;
    float m_spriteTimeAccumulator;
    bool m_stopAnimation;
    
    map<string, function<void()>> m_animationFinishedCallbacks;
     
    void initializeMembers()
    {
        m_pAnimatedSpriteData = nullptr;
        m_pCurrentAnimationStateData = nullptr;
        m_pSpritesheetData = nullptr;
        m_pCurrentSpriteData = nullptr;
        m_spriteTimeAccumulator = 0.0f;
        m_currentAnimationStateIndex = 0;
        m_stopAnimation = false;
        m_animationFinishedCallbacks.clear();
    }
    
};


#endif /* AnimatedSprite_hpp */
