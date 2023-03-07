#pragma once
#ifndef AnimationStateData_hpp
#define AnimationStateData_hpp

#include "JSONTypes.h"
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class AnimationStateData {
 public:
  AnimationStateData();
  AnimationStateData(JSONObject* pJSON);
  ~AnimationStateData() { initializeMembers(); }

  string const& getName() const { return m_name; };
  string const& getSoundEffect() const { return m_soundEffect; };
  bool const isPlayOnce() const { return m_playOnce; };
  bool const isAdvanceAnimationManually() const {
    return m_advanceAnimationManually;
  };
  vector<string> const& getSpriteNames() const { return m_spriteNames; };
  float const getTimePerSprite() const { return m_timePerSprite; };
  float const getOffsetX() const { return m_offsetX; };
  float const getOffsetY() const { return m_offsetY; };

 private:
  string m_name;
  string m_soundEffect;
  bool m_playOnce;
  bool m_advanceAnimationManually;
  vector<string> m_spriteNames;
  float m_timePerSprite;
  float m_offsetX;
  float m_offsetY;

  void initializeMembers() {
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
