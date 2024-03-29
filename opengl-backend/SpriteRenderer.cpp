#include "SpriteRenderer.hpp"
#include "ResourceManager.hpp"
#include "utils/StringUtils.h"

SpriteRenderer::SpriteRenderer() {}

SpriteRenderer::~SpriteRenderer() {
  for (auto& pair : m_textureVAOs) {
    glDeleteVertexArrays(1, &pair.second);
  }
}

void SpriteRenderer::draw(Shader& rShader, glm::mat4 const& rTransform, glm::vec2 const& rScaleFactor, Texture2D const& rTexture, glm::vec4 const& rTextureCoordinates)
{
  rShader.use();
  
  glm::mat4 model = glm::scale(rTransform, glm::vec3(rScaleFactor.x, rScaleFactor.y, 1.0f));  // scale factor -> to game units
  
  rShader.setMatrix4("model", model);
  
  glActiveTexture(GL_TEXTURE0);
  
  rTexture.bind();
  
  string textureName = stringFormat(
                                    "%d-(%.0f,%.0f,%.0f,%.0f)", rTexture.getId(), rTextureCoordinates.x,
                                    rTextureCoordinates.y, rTextureCoordinates.z, rTextureCoordinates.w);
  if (m_textureVAOs.find(textureName) == m_textureVAOs.end()) {
    createTextureVAO(textureName,
                     glm::vec2(rTexture.getWidth(), rTexture.getHeight()),
                     rTextureCoordinates);
  }
  unsigned int textureVAO = m_textureVAOs[textureName];
  
  glBindVertexArray(textureVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

void SpriteRenderer::drawSprite(Shader& rShader,
                                Texture2D const& rTexture,
                                glm::vec2 const& rPosition,
                                glm::vec2 const& rSize,
                                glm::vec4 const& rTextureCoordinates,
                                float rotate) {
  rShader.use();

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(rPosition,0.0f));
  // first translate (transformations are: scale
  // happens first, then rotation, and then final
  // translation happens; reversed order)

  model = glm::translate(
      model, glm::vec3(0.5f * rSize.x, 0.5f * rSize.y,
                       0.0f));  // move origin of rotation to center of quad
  model = glm::rotate(model, glm::radians(rotate),
                      glm::vec3(0.0f, 0.0f, 1.0f));  // then rotate
  model = glm::translate(model, glm::vec3(-0.5f * rSize.x, -0.5f * rSize.y,
                                          0.0f));  // move origin back

  model = glm::scale(model, glm::vec3(rSize, 1.0f));  // last scale

  rShader.setMatrix4("model", model);

  glActiveTexture(GL_TEXTURE0);

  rTexture.bind();

  string textureName = stringFormat(
      "%d-(%.0f,%.0f,%.0f,%.0f)", rTexture.getId(), rTextureCoordinates.x,
      rTextureCoordinates.y, rTextureCoordinates.z, rTextureCoordinates.w);
  if (m_textureVAOs.find(textureName) == m_textureVAOs.end()) {
    createTextureVAO(textureName,
                     glm::vec2(rTexture.getWidth(), rTexture.getHeight()),
                     rTextureCoordinates);
  }
  unsigned int textureVAO = m_textureVAOs[textureName];

  glBindVertexArray(textureVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

void SpriteRenderer::createTextureVAO(string textureName, glm::vec2 textureSize,
                                      glm::vec4 textureCoordinates) {
  float xs = textureCoordinates.x / textureSize.x;  // x start
  float xe =
      (textureCoordinates.x + textureCoordinates.w) / textureSize.x;  // x end
  float ys = textureCoordinates.y / textureSize.y;                    // y start
  float ye =
      (textureCoordinates.y + textureCoordinates.z) / textureSize.y;  // y end

  // configure VAO/VBO
  unsigned int VBO;
  float vertices[] = {
      // pos      // tex
      0.0f, 1.0f, xs, ye, 1.0f, 0.0f, xe, ys, 0.0f, 0.0f, xs, ys,

      0.0f, 1.0f, xs, ye, 1.0f, 1.0f, xe, ye, 1.0f, 0.0f, xe, ys};

  unsigned int textureVAO;

  glGenVertexArrays(1, &textureVAO);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(textureVAO);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  m_textureVAOs.insert(
      std::pair<string, unsigned int>(textureName, textureVAO));
}
