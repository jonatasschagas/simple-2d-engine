#include "TexturedSprite.hpp"

void TexturedSprite::renderSprite(GraphicsManager& rGraphicsManager) {
  if (m_pShader == nullptr) {
    // default shader
    m_pShader = &rGraphicsManager.getShader("textured");
    assert(m_pShader != nullptr && "Shader not found");
  }

  // lazy texture loading
  if (hasTexture() && !m_textureLoaded) {
    Texture texture = rGraphicsManager.loadTexture(m_textureFilename);
    m_textureLoaded = true;
    if (m_useWholeTexture) {
      m_textureWidth = texture.width;
      m_textureHeight = texture.height;
      setTextureCoordinates(0, 0, m_textureWidth, m_textureHeight);
    }
  }

  // render
  rGraphicsManager.renderTexture(m_worldTransform, m_textureCoordinates,
                                 m_textureFilename, *m_pShader);
}