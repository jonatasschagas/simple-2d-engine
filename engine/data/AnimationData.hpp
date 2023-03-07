#ifndef AnimationData_hpp
#define AnimationData_hpp

#include "../core/Vector2.h"
#include "AnimationData.hpp"
#include "JSONTypes.h"
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class AnimationData {
 public:
  AnimationData(string const& name, ConstJSONObject* pJSONObject);
  AnimationData(string const& name, JSONObject* pJSONObject);
  ~AnimationData();

  string const& loadNextSprite();

  Vector2 const& getLeftOffset() const;
  Vector2 const& getRightOffset() const;

  string const& getName() const;
  float getTimePerSprite() const;
  bool isPlayOnce() const;
  bool isAnimationFinished() const;
  void resetAnimation();
  bool isAdvanceManually() const;
  string const& getSoundEffect() const;

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

  void initializeMembers() {
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
