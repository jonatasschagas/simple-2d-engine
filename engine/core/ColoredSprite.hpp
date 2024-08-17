#pragma once
#ifndef ColoredSprite_hpp
#define ColoredSprite_hpp

#include "Sprite.hpp"

/**
 * ColoredSprite is a class that represents a sprite with a color.
 * @ingroup graphics
 */
class ColoredSprite : public Sprite {
 public:
  /**
   * @brief sets the color of the sprite
   * @param r the red component of the color
   * @param g the green component of the color
   * @param b the blue component of the color
   * @param a the alpha component of the color
   */
  void setColor(float r, float g, float b, float a) {
    m_color = glm::vec4(r, g, b, a);
  }

  /**
   * @brief returns the color of the sprite
   * @return the color of the sprite
   */
  glm::vec4 getColor() const { return m_color; }

 protected:
  glm::vec4 m_color = {0, 0, 0, 0};

 private:
  void renderSprite(GraphicsManager& rGraphicsManager) override;
};

#endif /* ColoredSprite_hpp */