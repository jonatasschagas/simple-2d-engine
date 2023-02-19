#include "AnimatedSprite.hpp"

#include "data/DataCacheManager.hpp"
#include "data/AnimatedSpriteData.hpp"
#include "data/AnimationStateData.hpp"
#include "data/SpritesheetData.hpp"
#include "data/SpriteData.hpp"
#include "platform/PlatformManager.h"

AnimatedSprite::AnimatedSprite(PlatformManager* pPlatformManager, DataCacheManager& rDataCacheManager, const string& animationFile) : Sprite(pPlatformManager), m_rDataCacheManager(rDataCacheManager)
{
    initializeMembers();
    
    m_pAnimatedSpriteData = rDataCacheManager.getAnimatedSprite(animationFile);
    m_pSpritesheetData = m_rDataCacheManager.getSprite(m_pAnimatedSpriteData->getConfigFile(),
                                                     m_pAnimatedSpriteData->getTextureFile());
    // loading the texture
    loadTexture(m_pAnimatedSpriteData->getTextureFile());
}

AnimatedSprite::~AnimatedSprite()
{
    initializeMembers();
}

void AnimatedSprite::update(float delta)
{
    Sprite::update(delta);
    
    if (m_stopAnimation)
        return;

    if (m_pCurrentAnimationStateData == nullptr || m_pCurrentAnimationStateData->isAdvanceAnimationManually())
    {
        return;
    }
    
    if (m_spriteTimeAccumulator > m_pCurrentAnimationStateData->getTimePerSprite())
    {
        const vector<string> spriteNames = m_pCurrentAnimationStateData->getSpriteNames();
        m_currentAnimationStateIndex++;
        if (m_currentAnimationStateIndex >= spriteNames.size())
        {
            if (m_pCurrentAnimationStateData->isPlayOnce())
            {
                if (m_animationFinishedCallbacks.find(m_pCurrentAnimationStateData->getName()) != m_animationFinishedCallbacks.end())
                {
                    function<void()> onAnimationFinishedCallback = m_animationFinishedCallbacks[m_pCurrentAnimationStateData->getName()];
                    if (onAnimationFinishedCallback)
                    {
                        onAnimationFinishedCallback();
                    }
                }
                return;
            }
            m_currentAnimationStateIndex = 0;
        }
        
        string currentSpriteName = spriteNames[m_currentAnimationStateIndex];
        m_pCurrentSpriteData = m_pSpritesheetData->getSpriteByName(currentSpriteName);
        assert(m_pCurrentSpriteData != nullptr);
        m_spriteTimeAccumulator = 0.0f;
        
    }
    
    m_spriteTimeAccumulator += delta;
}

void AnimatedSprite::render()
{
    if (m_pCurrentAnimationStateData != nullptr)
    {
        float x, y;
        
        if (isFlipped())
        {
            x = getX() - m_pCurrentAnimationStateData->getOffsetX();
            y = getY() - m_pCurrentAnimationStateData->getOffsetY();
        }
        else
        {
            x = getX() + m_pCurrentAnimationStateData->getOffsetX();
            y = getY() + m_pCurrentAnimationStateData->getOffsetY();
        }
        
        setXY(x,y);
        
        if (m_pCurrentSpriteData != nullptr)
        {
            setTextureCoordinates(m_pCurrentSpriteData->getX(),
                                  m_pCurrentSpriteData->getY(),
                                  m_pCurrentSpriteData->getWidth(),
                                  m_pCurrentSpriteData->getHeight());
        }
        
    }
    
    Sprite::render();
}

void AnimatedSprite:: play(const string& animationName, const bool flip)
{
    setFlip(flip);

    // animation is already playing
    if (isPlaying(animationName))
    {
        return;
    }
        
    m_pCurrentAnimationStateData = m_pAnimatedSpriteData->getAnimation(animationName);
    m_spriteTimeAccumulator = 0;
    
    string soundEffect = m_pCurrentAnimationStateData->getSoundEffect();
    if (soundEffect.size() > 0)
    {
        playSoundEffect(soundEffect);
    }
    
    if (m_pCurrentAnimationStateData->isAdvanceAnimationManually())
    {
        advanceStep();
        m_currentAnimationStateIndex++;
    }
    else
    {
        m_currentAnimationStateIndex = 0;
    }
}

const bool AnimatedSprite::isAnimationFinished(const string& animationName) const
{
    if (m_pCurrentAnimationStateData == NULL ||
        m_pCurrentAnimationStateData->getName().compare(animationName) != 0)
    {
        return true;
    }
    
    return isAtLastSprite();
}

float AnimatedSprite::getProgressAnimation() const
{
    vector<string> spriteNames = m_pCurrentAnimationStateData->getSpriteNames();
    return ((float)m_currentAnimationStateIndex)/((float)spriteNames.size());
}

void AnimatedSprite::advanceStep()
{
    if (isAtLastSprite())
    {
        if (m_pCurrentAnimationStateData->isPlayOnce())
            return;
        
        m_currentAnimationStateIndex = 0;
    }
    
    const vector<string> spriteNames = m_pCurrentAnimationStateData->getSpriteNames();
    string currentSpriteName = spriteNames[m_currentAnimationStateIndex];
    m_pCurrentSpriteData = m_pSpritesheetData->getSpriteByName(currentSpriteName);
    m_spriteTimeAccumulator = 0.0f;
    
    setTextureCoordinates(m_pCurrentSpriteData->getX(),
                          m_pCurrentSpriteData->getY(),
                          m_pCurrentSpriteData->getWidth(),
                          m_pCurrentSpriteData->getHeight());
}

const bool AnimatedSprite::hasAnimation(const string& animationName) const
{
    return m_pAnimatedSpriteData->hasAnimation(animationName);
}

bool AnimatedSprite::isVisibleInParent(Sprite* pChild) const
{
    return true;
}

bool AnimatedSprite::isAtLastSprite() const
{
    vector<string> spriteNames = m_pCurrentAnimationStateData->getSpriteNames();
    return m_currentAnimationStateIndex >= (spriteNames.size() - 1);
}

const string& AnimatedSprite::getCurrentAnimationName() const
{
    return m_pCurrentAnimationStateData->getName();
}

const bool AnimatedSprite::isPlaying(const string& animationName) const
{
    if (m_pCurrentAnimationStateData == nullptr)
    {
        return false;
    }
    
    return m_pCurrentAnimationStateData->getName().compare(animationName) == 0;
}
