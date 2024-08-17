#include "ColoredSprite.hpp"

void ColoredSprite::renderSprite(GraphicsManager& rGraphicsManager) {
  if (m_pShader == nullptr) {
    // default shader
    m_pShader = &rGraphicsManager.getShader("colored");
    assert(m_pShader != nullptr && "Shader not found");
  }

  // enables it
  m_pShader->use();
  // updates the shader with the color
  m_pShader->setVector4f("color", m_color);

  rGraphicsManager.renderColoredSprite(m_worldTransform, *m_pShader);
}
