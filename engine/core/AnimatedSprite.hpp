#pragma once
#ifndef AnimatedSprite_hpp
#define AnimatedSprite_hpp

#include "../core/Sprite.hpp"
#include <functional>
#include <map>
#include <stdio.h>
#include <string>

using namespace std;

class AnimatedSpriteData;
class AnimationStateData;
class SpritesheetData;
class SpriteData;

class AnimatedSprite : public Sprite {
 public:
  AnimatedSprite(AnimatedSpriteData const& rAnimatedSpriteData,
                 SpritesheetData const& rAnimatedSpritesheetData);
  ~AnimatedSprite();

  void update(float delta) override;
  void render(GraphicsManager& rGraphicsManager) override;
  void play(string const& animationName, bool const flip = false);

  bool const hasAnimation(string const& animationName) const;
  bool const isAnimationFinished(string const& animationName) const;
  AnimationStateData const& getCurrentAnimationState() const;
  string const& getCurrentAnimationName() const;
  bool const isPlaying(string const& animationName) const;
  float getProgressAnimation() const;

  bool isVisibleInParent(Sprite* pChild) const override;

  void stopAnimation();
  void resumeAnimation();
  bool isAnimationStopped() const;

  void setOnAnimationFinishedCallback(string const& animationName,
                                      function<void()> callback);

 private:
  void advanceStep();
  bool isAtLastSprite() const;

  AnimatedSpriteData const& m_rAnimatedSpriteData;
  AnimationStateData const* m_pCurrentAnimationStateData;
  SpritesheetData const& m_rSpritesheetData;
  SpriteData const* m_pCurrentSpriteData;

  int m_currentAnimationStateIndex;
  float m_spriteTimeAccumulator;
  bool m_stopAnimation;

  map<string, function<void()>> m_animationFinishedCallbacks;

  void initializeMembers() {
    m_spriteTimeAccumulator = 0.0f;
    m_currentAnimationStateIndex = 0;
    m_stopAnimation = false;
    m_animationFinishedCallbacks.clear();

    m_pCurrentAnimationStateData = nullptr;
    m_pCurrentSpriteData = nullptr;
  }
};

#endif /* AnimatedSprite_hpp */
