#pragma once
#ifndef AnimatedSpriteData_hpp
#define AnimatedSpriteData_hpp

#include "AnimationStateData.hpp"
#include "JSONTypes.h"
#include <map>
#include <stdio.h>
#include <string>

using namespace std;

class AnimatedSpriteData {
 public:
  AnimatedSpriteData();
  AnimatedSpriteData(string const& configurationJSONFilename);
  ~AnimatedSpriteData();

  string const& getConfigFile() const { return m_spritesheetConfigFile; };
  string const& getTextureFile() const { return m_spritesheetTextureFile; };
  AnimationStateData const* getAnimation(string const& animationName) const;
  bool hasAnimation(string const& animationName) const;
  AnimationStateData const* getDefaultAnimation() const;

 private:
  string m_spritesheetConfigFile;
  string m_spritesheetTextureFile;

  map<string, AnimationStateData> m_animationsMap;

  void initializeMembers() {
    m_spritesheetTextureFile = "";
    m_spritesheetConfigFile = "";
    m_animationsMap.clear();
  }
};

#endif /* AnimatedSpriteData_hpp */
