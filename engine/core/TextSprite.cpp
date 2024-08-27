#include "TextSprite.hpp"
#include "CharacterSprite.hpp"
#include "utils/Logging.h"

TextSprite::TextSprite(float scale, glm::vec4 color) : Sprite() {
  m_scale = scale;
  m_color = color;
}

TextSprite::~TextSprite() {
  for (CharacterSprite* pCharacter : m_characters) {
    delete pCharacter;
  }
  m_characters.clear();
}

void TextSprite::renderSprite(GraphicsManager& rGraphicsManager) {
  float advance = 0.0f;
  for (CharacterSprite* pCharacter : m_characters) {
    pCharacter->setColor(m_color);
    pCharacter->render(rGraphicsManager);
    advance = pCharacter->getWidth();
  }
}

void TextSprite::setText(string const& text) {
  assert(getWidth() > 0 && getHeight() > 0 &&
         "TextSprite::setText() - width and height must be set before calling "
         "setText()");

  m_text = text;

  // clean up characters
  if (m_text.size() < m_characters.size()) {
    for (long i = m_text.size(); i < m_characters.size(); i++) {
      removeChild(m_characters[i]);
      delete m_characters[i];
    }
    m_characters.erase(m_characters.begin() + m_text.size(),
                       m_characters.end());
  }

  // update characters
  float width = 100.0f / m_text.size();
  for (int i = 0; i < m_text.size(); i++) {
    if (i < m_characters.size()) {
      m_characters[i]->setCharacter(m_text[i]);
      m_characters[i]->setScale(m_scale);
      m_characters[i]->setColor(m_color);
      m_characters[i]->setX(i * width);
      m_characters[i]->setY(0);
      m_characters[i]->setSize(width, 100);
      continue;
    }

    // create new character
    CharacterSprite* characterSprite =
        new CharacterSprite(m_text[i], m_scale, m_color);
    addChild(characterSprite);
    characterSprite->setPivotAtCenter();
    characterSprite->setSize(width, 100);
    characterSprite->setY(0);
    characterSprite->setX(i * width);
    m_characters.push_back(characterSprite);
  }
}

void TextSprite::setScale(float scale) { m_scale = scale; }

void TextSprite::setColor(glm::vec4 color) { m_color = color; }
