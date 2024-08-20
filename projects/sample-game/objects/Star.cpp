#include "Star.hpp"

Star::Star(glm::vec4 color) : ColoredSprite() {
  m_color = color;
  m_time = rand() % 1000;
}

void Star::update(float delta) {
  ColoredSprite::update(delta);
  m_time += delta;
}

void Star::renderSprite(GraphicsManager& rGraphicsManager) {
  if (m_pShader == nullptr) {
    // default shader
    m_pShader = &rGraphicsManager.getShader("circle");
    assert(m_pShader != nullptr && "Shader not found");
  }

  // enables it
  m_pShader->use();
  // updates the shader with the color
  m_pShader->setVector4f("color", m_color);

  glm::vec2 dpi;
  rGraphicsManager.getDpi(dpi.x, dpi.y);

  glm::vec2 shapeSize = getTrueSizeInPixels(rGraphicsManager) * dpi;
  m_pShader->setVector2f("shapeSize", shapeSize);

  glm::vec2 shapePosition = getTruePositionInPixels(rGraphicsManager) * dpi;
  m_pShader->setVector2f("shapePosition", shapePosition);

  glm::vec2 screenSize = glm::vec2(rGraphicsManager.getScreenWidth(),
                                   rGraphicsManager.getScreenHeight()) *
                         dpi;
  m_pShader->setVector2f("screenSize", screenSize);

  m_pShader->setFloat("time", m_time);

  rGraphicsManager.renderColoredSprite(m_worldTransform, *m_pShader);
}