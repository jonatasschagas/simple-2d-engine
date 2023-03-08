#include "AnimatedSprite.hpp"
#include "data/AnimatedSpriteData.hpp"
#include "data/AnimationStateData.hpp"
#include "data/DataCacheManager.hpp"
#include "data/SpriteData.hpp"
#include "data/SpritesheetData.hpp"
#include "platform/GraphicsManager.hpp"

AnimatedSprite::AnimatedSprite(AnimatedSpriteData const& rAnimatedSpriteData,
                               SpritesheetData const& rSpriteSheetData)
    : m_rAnimatedSpriteData(rAnimatedSpriteData),
      m_rSpritesheetData(rSpriteSheetData) {
  initializeMembers();

  loadTexture(m_rAnimatedSpriteData.getTextureFile());
}

AnimatedSprite::~AnimatedSprite() { initializeMembers(); }

void AnimatedSprite::update(float delta) {
  Sprite::update(delta);

  if (m_stopAnimation) return;

  if (m_pCurrentAnimationStateData == nullptr ||
      m_pCurrentAnimationStateData->isAdvanceAnimationManually()) {
    return;
  }

  if (m_spriteTimeAccumulator >
      m_pCurrentAnimationStateData->getTimePerSprite()) {
    vector<string> const spriteNames =
        m_pCurrentAnimationStateData->getSpriteNames();
    m_currentAnimationStateIndex++;
    if (m_currentAnimationStateIndex >= spriteNames.size()) {
      if (m_pCurrentAnimationStateData->isPlayOnce()) {
        if (m_animationFinishedCallbacks.find(
                m_pCurrentAnimationStateData->getName()) !=
            m_animationFinishedCallbacks.end()) {
          function<void()> onAnimationFinishedCallback =
              m_animationFinishedCallbacks[m_pCurrentAnimationStateData
                                               ->getName()];
          if (onAnimationFinishedCallback) {
            onAnimationFinishedCallback();
          }
        }
        return;
      }
      m_currentAnimationStateIndex = 0;
    }

    string currentSpriteName = spriteNames[m_currentAnimationStateIndex];
    m_pCurrentSpriteData =
        m_rSpritesheetData.getSpriteByName(currentSpriteName);
    m_spriteTimeAccumulator = 0.0f;
  }

  m_spriteTimeAccumulator += delta;
}

void AnimatedSprite::render(GraphicsManager& rGraphicsManager) {
  if (m_pCurrentSpriteData == nullptr) return;

  float x, y;

  if (isFlipped()) {
    x = getX() - m_pCurrentAnimationStateData->getOffsetX();
    y = getY() - m_pCurrentAnimationStateData->getOffsetY();
  } else {
    x = getX() + m_pCurrentAnimationStateData->getOffsetX();
    y = getY() + m_pCurrentAnimationStateData->getOffsetY();
  }

  setXY(x, y);

  setTextureCoordinates(
      m_pCurrentSpriteData->getX(), m_pCurrentSpriteData->getY(),
      m_pCurrentSpriteData->getWidth(), m_pCurrentSpriteData->getHeight());

  Sprite::render(rGraphicsManager);
}

void AnimatedSprite::play(string const& animationName, bool const flip) {
  setFlip(flip);

  // animation is already playing
  if (isPlaying(animationName)) {
    return;
  }

  m_pCurrentAnimationStateData =
      m_rAnimatedSpriteData.getAnimation(animationName);
  m_spriteTimeAccumulator = 0;

  string soundEffect = m_pCurrentAnimationStateData->getSoundEffect();
  if (soundEffect.size() > 0) {
    playSoundEffect(soundEffect);
  }

  if (m_pCurrentAnimationStateData->isAdvanceAnimationManually()) {
    advanceStep();
    m_currentAnimationStateIndex++;
  } else {
    m_currentAnimationStateIndex = 0;
  }
}

bool const AnimatedSprite::isAnimationFinished(
    string const& animationName) const {
  if (m_pCurrentAnimationStateData->getName().compare(animationName) != 0) {
    return true;
  }

  return isAtLastSprite();
}

float AnimatedSprite::getProgressAnimation() const {
  vector<string> spriteNames = m_pCurrentAnimationStateData->getSpriteNames();
  return ((float)m_currentAnimationStateIndex) / ((float)spriteNames.size());
}

void AnimatedSprite::advanceStep() {
  if (isAtLastSprite()) {
    if (m_pCurrentAnimationStateData->isPlayOnce()) return;

    m_currentAnimationStateIndex = 0;
  }

  vector<string> const spriteNames =
      m_pCurrentAnimationStateData->getSpriteNames();
  string currentSpriteName = spriteNames[m_currentAnimationStateIndex];
  m_pCurrentSpriteData = m_rSpritesheetData.getSpriteByName(currentSpriteName);
  m_spriteTimeAccumulator = 0.0f;

  setTextureCoordinates(
      m_pCurrentSpriteData->getX(), m_pCurrentSpriteData->getY(),
      m_pCurrentSpriteData->getWidth(), m_pCurrentSpriteData->getHeight());
}

bool const AnimatedSprite::hasAnimation(string const& animationName) const {
  return m_rAnimatedSpriteData.hasAnimation(animationName);
}

bool AnimatedSprite::isAtLastSprite() const {
  vector<string> spriteNames = m_pCurrentAnimationStateData->getSpriteNames();
  return m_currentAnimationStateIndex >= (spriteNames.size() - 1);
}

string const& AnimatedSprite::getCurrentAnimationName() const {
  return m_pCurrentAnimationStateData->getName();
}

bool const AnimatedSprite::isPlaying(string const& animationName) const {
  if (m_pCurrentAnimationStateData == nullptr) return false;
  return m_pCurrentAnimationStateData->getName().compare(animationName) == 0;
}

void AnimatedSprite::setOnAnimationFinishedCallback(string const& animationName,
                                                    function<void()> callback) {
  m_animationFinishedCallbacks[animationName] = callback;
}

AnimationStateData const& AnimatedSprite::getCurrentAnimationState() const {
  return *m_pCurrentAnimationStateData;
};

void AnimatedSprite::stopAnimation() { m_stopAnimation = true; }

void AnimatedSprite::resumeAnimation() { m_stopAnimation = false; }

bool AnimatedSprite::isAnimationStopped() const { return m_stopAnimation; }
