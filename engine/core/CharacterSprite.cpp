#include "CharacterSprite.hpp"

CharacterSprite::CharacterSprite(char character, float scale, glm::vec3 color)
    : Sprite() {
  m_character = character;
  m_scale = scale;
  m_color = color;
}

CharacterSprite::~CharacterSprite() {}

void CharacterSprite::renderSprite(GraphicsManager& rGraphicsManager) {
  if (m_pShader == nullptr) {
    // default shader
    m_pShader = &rGraphicsManager.getShader("text");
    assert(m_pShader != nullptr && "Shader not found");
  }

  // enables it
  m_pShader->use();

  m_advance = rGraphicsManager.renderCharacter(m_character, m_worldTransform,
                                               m_scale, m_color, *m_pShader);
}

void CharacterSprite::setCharacter(char character) { m_character = character; }

void CharacterSprite::setScale(float scale) { m_scale = scale; }

void CharacterSprite::setColor(glm::vec3 color) { m_color = color; }

float CharacterSprite::getAdvance() { return m_advance; }
