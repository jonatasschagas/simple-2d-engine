#pragma once
#ifndef CharacterSprite_hpp
#define CharacterSprite_hpp

#include "Sprite.hpp"
#include <functional>
#include <map>
#include <memory>
#include <stdio.h>
#include <string>

using std::string;

class CharacterSprite : public Sprite {
 public:
  CharacterSprite(char character, float scale, glm::vec3 color);
  ~CharacterSprite();

  void renderSprite(GraphicsManager& rGraphicsManager) override;

  void setCharacter(char character);
  void setScale(float scale);
  void setColor(glm::vec3 color);
  float getAdvance();

 private:
  char m_character = '\0';
  float m_scale = 1.0f;
  float m_advance = 0.0f;
  glm::vec3 m_color = glm::vec3(1.0f, 1.0f, 1.0f);
};

#endif /* CharacterSprite_hpp */
