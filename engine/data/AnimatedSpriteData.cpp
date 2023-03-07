#include "AnimatedSpriteData.hpp"
#include "../utils/FileUtils.h"

AnimatedSpriteData::AnimatedSpriteData() { initializeMembers(); }

AnimatedSpriteData::AnimatedSpriteData(
    string const& configurationJSONFilename) {
  initializeMembers();

  string configurationJSON = loadFile(configurationJSONFilename);
  Document configurationDocument;
  configurationDocument.Parse(configurationJSON.c_str());

  m_spritesheetConfigFile =
      configurationDocument.FindMember("spriteSheetConfig")->value.GetString();
  m_spritesheetTextureFile =
      configurationDocument.FindMember("spriteSheetImage")->value.GetString();

  auto spritesArray =
      configurationDocument.FindMember("states")->value.GetArray();

  for (int i = 0; i < spritesArray.Size(); i++) {
    JSONObject spriteJSON = spritesArray[i].GetObject();
    string spriteName = spriteJSON.FindMember("name")->value.GetString();
    AnimationStateData animationStateData(&spriteJSON);
    m_animationsMap[spriteName] = animationStateData;
  }

  assert(m_animationsMap.size() > 0);
}

AnimatedSpriteData::~AnimatedSpriteData() { initializeMembers(); }

AnimationStateData const* AnimatedSpriteData::getAnimation(
    string const& animationName) const {
  return &m_animationsMap.at(animationName);
}

bool AnimatedSpriteData::hasAnimation(string const& animationName) const {
  auto it = m_animationsMap.find(animationName);
  return !(it == m_animationsMap.end());
}

AnimationStateData const* AnimatedSpriteData::getDefaultAnimation() const {
  return &m_animationsMap.begin()->second;
}
