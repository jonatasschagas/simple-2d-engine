#pragma once
#ifndef TextSprite_hpp
#define TextSprite_hpp

#include "CharacterSprite.hpp"
#include "Sprite.hpp"
#include <functional>
#include <map>
#include <memory>
#include <stdio.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

class CharacterSprite;

class TextSprite : public Sprite {
 public:
  TextSprite(float scale, glm::vec4 color);
  ~TextSprite();

  void renderSprite(GraphicsManager& rGraphicsManager) override;

  void setText(string const& text);
  void setScale(float scale);
  void setColor(glm::vec4 color);

 private:
  string m_text = "";
  float m_scale = 1.0f;
  glm::vec4 m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  vector<CharacterSprite*> m_characters = {};
};

#endif /* TextSprite_hpp */
