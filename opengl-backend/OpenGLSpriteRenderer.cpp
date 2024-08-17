#include "OpenGLSpriteRenderer.hpp"
#include "OpenGLResourceManager.hpp"
#include "utils/StringUtils.h"

OpenGLSpriteRenderer::OpenGLSpriteRenderer() {}

OpenGLSpriteRenderer::~OpenGLSpriteRenderer() {
  for (auto& pair : m_textureVAOs) {
    glDeleteVertexArrays(1, &pair.second);
  }
}

void OpenGLSpriteRenderer::draw(Shader& rShader, glm::mat4 const& rTransform,
                                OpenGLTexture2d const& rTexture,
                                glm::vec4 const& rTextureCoordinates) {
  rShader.use();

  rShader.setMatrix4("model", rTransform);

  glActiveTexture(GL_TEXTURE0);
  CheckOpenGLError("glActiveTexture");

  rTexture.bind();
  CheckOpenGLError("glActiveTexture");

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
  CheckOpenGLError("glBindVertexArray");
  glDrawArrays(GL_TRIANGLES, 0, 6);
  CheckOpenGLError("glDrawArrays");
  glBindVertexArray(0);
  CheckOpenGLError("glBindVertexArray");
}

void OpenGLSpriteRenderer::draw(Shader& rShader, glm::mat4 const& rTransform) {
  if (m_quadVAO == 0) {
    createQuadVAO();
  }

  rShader.use();

  CheckOpenGLError("shader.use");

  rShader.setMatrix4("model", rTransform);
  CheckOpenGLError("shader.setMatrix4");

  glBindVertexArray(m_quadVAO);
  CheckOpenGLError("glBindVertexArray");
  glDrawArrays(GL_TRIANGLES, 0, 6);
  CheckOpenGLError("glDrawArrays");
  glBindVertexArray(0);
  CheckOpenGLError("glBindVertexArray");
}

void OpenGLSpriteRenderer::createTextureVAO(string textureName,
                                            glm::vec2 textureSize,
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
  CheckOpenGLError("glGenVertexArrays");
  glGenBuffers(1, &VBO);
  CheckOpenGLError("glGenBuffers");

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  CheckOpenGLError("glBindBuffer");
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticesQuad), verticesQuad,
               GL_STATIC_DRAW);
  CheckOpenGLError("glBufferData");

  glBindVertexArray(textureVAO);
  CheckOpenGLError("glBindVertexArray");
  glEnableVertexAttribArray(0);
  CheckOpenGLError("glEnableVertexAttribArray");
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  CheckOpenGLError("glVertexAttribPointer");
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  CheckOpenGLError("glBindBuffer");
  glBindVertexArray(0);
  CheckOpenGLError("glBindVertexArray");

  m_textureVAOs.insert(
      std::pair<string, unsigned int>(textureName, textureVAO));
}

void OpenGLSpriteRenderer::createQuadVAO() {
  // configure VAO/VBO
  unsigned int VBO;

  float verticesQuad[] = {// pos      // tex
                          0.0f, 1.0f, 0, 0, 1.0f, 0.0f, 0, 0, 0.0f, 0.0f, 0, 0,

                          0.0f, 1.0f, 0, 0, 1.0f, 1.0f, 0, 0, 1.0f, 0.0f, 0, 0};

  glGenVertexArrays(1, &m_quadVAO);
  CheckOpenGLError("glGenVertexArrays");
  glGenBuffers(1, &VBO);
  CheckOpenGLError("glGenBuffers");

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  CheckOpenGLError("glBindBuffer");
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticesQuad), verticesQuad,
               GL_STATIC_DRAW);
  CheckOpenGLError("glBufferData");

  glBindVertexArray(m_quadVAO);
  CheckOpenGLError("glBindVertexArray");
  glEnableVertexAttribArray(0);
  CheckOpenGLError("glEnableVertexAttribArray");
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  CheckOpenGLError("glVertexAttribPointer");
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  CheckOpenGLError("glBindBuffer");
  glBindVertexArray(0);
  CheckOpenGLError("glBindVertexArray");
}