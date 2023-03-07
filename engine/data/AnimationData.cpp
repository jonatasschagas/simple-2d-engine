#include "AnimationData.hpp"

AnimationData::AnimationData(string const& name, ConstJSONObject* pJsonObject) {
  initializeMembers();

  m_timePerSprite = pJsonObject->FindMember("timePerSprite")->value.GetFloat();
  auto arraySprites = pJsonObject->FindMember("sprites")->value.GetArray();
  m_playOnce = pJsonObject->FindMember("playOnce")->value.GetBool();
  m_name = name;

  for (SizeType i = 0; i < arraySprites.Size(); i++) {
    string animationName = arraySprites[i].GetString();
    m_sprites.push_back(animationName);
  }

  if (pJsonObject->HasMember("leftOffsetX")) {
    m_leftOffset.x = pJsonObject->FindMember("leftOffsetX")->value.GetFloat();
    m_leftOffset.y = pJsonObject->FindMember("leftOffsetY")->value.GetFloat();
  }

  if (pJsonObject->HasMember("rightOffsetX")) {
    m_rightOffset.x = pJsonObject->FindMember("rightOffsetX")->value.GetFloat();
    m_rightOffset.y = pJsonObject->FindMember("rightOffsetY")->value.GetFloat();
  }

  if (pJsonObject->HasMember("offsetX")) {
    m_leftOffset.x = pJsonObject->FindMember("offsetX")->value.GetFloat();
    m_rightOffset.x = pJsonObject->FindMember("offsetX")->value.GetFloat();
  }

  if (pJsonObject->HasMember("offsetY")) {
    m_leftOffset.y = pJsonObject->FindMember("offsetY")->value.GetFloat();
    m_rightOffset.y = pJsonObject->FindMember("offsetY")->value.GetFloat();
  }

  if (pJsonObject->HasMember("soundEffect")) {
    m_soundEffect = pJsonObject->FindMember("soundEffect")->value.GetString();
  }

  if (pJsonObject->HasMember("advanceAnimationManually")) {
    m_advanceAnimationManually =
        pJsonObject->FindMember("advanceAnimationManually")->value.GetBool();
  }
}

AnimationData::AnimationData(string const& name, JSONObject* pJsonObject) {
  m_timePerSprite = pJsonObject->FindMember("timePerSprite")->value.GetFloat();
  auto arraySprites = pJsonObject->FindMember("sprites")->value.GetArray();
  m_playOnce = pJsonObject->FindMember("playOnce")->value.GetBool();
  m_name = name;

  for (SizeType i = 0; i < arraySprites.Size(); i++) {
    string animationName = arraySprites[i].GetString();
    m_sprites.push_back(animationName);
  }

  if (pJsonObject->HasMember("leftOffsetX")) {
    m_leftOffset.x = pJsonObject->FindMember("leftOffsetX")->value.GetFloat();
    m_leftOffset.y = pJsonObject->FindMember("leftOffsetY")->value.GetFloat();
  }

  if (pJsonObject->HasMember("rightOffsetX")) {
    m_rightOffset.x = pJsonObject->FindMember("rightOffsetX")->value.GetFloat();
    m_rightOffset.y = pJsonObject->FindMember("rightOffsetY")->value.GetFloat();
  }

  if (pJsonObject->HasMember("offsetX")) {
    m_leftOffset.x = pJsonObject->FindMember("offsetX")->value.GetFloat();
    m_rightOffset.x = pJsonObject->FindMember("offsetX")->value.GetFloat();
  }

  if (pJsonObject->HasMember("offsetY")) {
    m_leftOffset.y = pJsonObject->FindMember("offsetY")->value.GetFloat();
    m_rightOffset.y = pJsonObject->FindMember("offsetY")->value.GetFloat();
  }

  if (pJsonObject->HasMember("soundEffect")) {
    m_soundEffect = pJsonObject->FindMember("soundEffect")->value.GetString();
  }

  if (pJsonObject->HasMember("advanceAnimationManually")) {
    m_advanceAnimationManually =
        pJsonObject->FindMember("advanceAnimationManually")->value.GetBool();
  }
}

AnimationData::~AnimationData() {}

string const& AnimationData::loadNextSprite() {
  string const& currentSprite = m_sprites[m_currentSpriteIndex];
  if (m_currentSpriteIndex + 1 >= (int)m_sprites.size()) {
    if (m_playOnce) {
      return currentSprite;
    }
    m_currentSpriteIndex = 0;
  } else {
    m_currentSpriteIndex++;
  }
  return currentSprite;
}

bool AnimationData::isAnimationFinished() const {
  return m_currentSpriteIndex + 1 >= m_sprites.size();
};

Vector2 const& AnimationData::getLeftOffset() const { return m_leftOffset; };

Vector2 const& AnimationData::getRightOffset() const { return m_rightOffset; };

string const& AnimationData::getName() const { return m_name; };

float AnimationData::getTimePerSprite() const { return m_timePerSprite; };

bool AnimationData::isPlayOnce() const { return m_playOnce; };

void AnimationData::resetAnimation() { m_currentSpriteIndex = 0; }

bool AnimationData::isAdvanceManually() const {
  return m_advanceAnimationManually;
};

string const& AnimationData::getSoundEffect() const { return m_soundEffect; };
