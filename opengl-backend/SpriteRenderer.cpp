#include "SpriteRenderer.hpp"
#include "ResourceManager.hpp"
#include "utils/StringUtils.h"

SpriteRenderer::SpriteRenderer() {}

SpriteRenderer::~SpriteRenderer() {
  for (auto& pair : m_textureVAOs) {
    glDeleteVertexArrays(1, &pair.second);
  }
}

void SpriteRenderer::draw(Shader& rShader, glm::mat4 const& rTransform,
                          Texture2D const& rTexture,
                          glm::vec4 const& rTextureCoordinates) {
  rShader.use();

  rShader.setMatrix4("model", rTransform);

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

void SpriteRenderer::draw(Shader& rShader, glm::mat4 const& rTransform,
                          glm::vec4 const& color) {
  if (m_quadVAO == 0) {
    createQuadVAO();
  }

  rShader.use();

  rShader.setMatrix4("model", rTransform);
  rShader.setVector4f("color", color);

  glBindVertexArray(m_quadVAO);
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

  float verticesQuad[] = {
      // pos      // tex
      0.0f, 1.0f, xs, ye, 1.0f, 0.0f, xe, ys, 0.0f, 0.0f, xs, ys,

      0.0f, 1.0f, xs, ye, 1.0f, 1.0f, xe, ye, 1.0f, 0.0f, xe, ys};

  unsigned int textureVAO;

  glGenVertexArrays(1, &textureVAO);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticesQuad), verticesQuad,
               GL_STATIC_DRAW);

  glBindVertexArray(textureVAO);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  m_textureVAOs.insert(
      std::pair<string, unsigned int>(textureName, textureVAO));
}

void SpriteRenderer::createQuadVAO() {
  // configure VAO/VBO
  unsigned int VBO;

  float verticesQuad[] = {// pos      // tex
                          0.0f, 1.0f, 0, 0, 1.0f, 0.0f, 0, 0, 0.0f, 0.0f, 0, 0,

                          0.0f, 1.0f, 0, 0, 1.0f, 1.0f, 0, 0, 1.0f, 0.0f, 0, 0};

  glGenVertexArrays(1, &m_quadVAO);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticesQuad), verticesQuad,
               GL_STATIC_DRAW);

  glBindVertexArray(m_quadVAO);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}