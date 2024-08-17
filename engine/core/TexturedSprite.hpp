#pragma once
#ifndef TexturedSprite_hpp
#define TexturedSprite_hpp

#include "Sprite.hpp"

/**
 * TexturedSprite is a class that represents a sprite with a texture.
 * @ingroup graphics
 */
class TexturedSprite : public Sprite {
 public:
  /**
   * @brief returns whether the sprite has a texture
   * @return whether the sprite has a texture
   */
  bool hasTexture() const { return m_textureFilename.size() > 0; };

  /**
   * @brief returns whether the sprite is flipped
   * @return whether the sprite is flipped
   */
  bool const isFlipped() const { return m_flip; }

  /**
   * @brief sets the flip flag
   * @param flip the flag to set
   */
  void setFlip(bool const flip) { m_flip = flip; }

  /**
   * @brief sets the texture coordinates of the sprite
   * @param x the x coordinate of the texture
   * @param y the y coordinate of the texture
   * @param w the width of the texture
   * @param h the height of the texture
   */
  void setTextureCoordinates(float x, float y, float w, float h) {
    m_textureCoordinates = glm::vec4(x, y, w, h);
  }

  /**
   * @brief sets the parent of the sprite
   * @param pParent the parent to set
   */
  void setWholeTexture(bool useWholeTexture) {
    m_useWholeTexture = useWholeTexture;
  }

  /**
   * @brief sets the color of the sprite
   * @param color the color to set
   */
  void loadTexture(string const& textureFileName) {
    m_textureFilename = textureFileName;
  }

 private:
  void renderSprite(GraphicsManager& rGraphicsManager) override;

  glm::vec4 m_textureCoordinates = {0, 0, 0, 0};
  bool m_flip = false;
  string m_textureFilename = "";
  bool m_textureLoaded = false;
  int m_textureWidth = 0;
  int m_textureHeight = 0;
  bool m_useWholeTexture = false;
};

#endif /* TexturedSprite_hpp */