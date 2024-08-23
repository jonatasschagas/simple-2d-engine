#include "OpenGLSpriteRenderer.hpp"
#include "OpenGLResourceManager.hpp"
#include "OpenGLUtils.h"
#include "utils/StringUtils.h"

OpenGLSpriteRenderer::OpenGLSpriteRenderer() {}

OpenGLSpriteRenderer::~OpenGLSpriteRenderer() {
  for (auto& pair : m_textureVAOs) {
    glDeleteVertexArrays(1, &pair.second);
    checkOpenGLError("glDeleteVertexArrays");
  }
}

void OpenGLSpriteRenderer::draw(Shader& rShader, glm::mat4 const& rTransform,
                                OpenGLTexture2d const& rTexture,
                                glm::vec4 const& rTextureCoordinates) {
  rShader.use();

  rShader.setMatrix4("model", rTransform);

  glActiveTexture(GL_TEXTURE0);
  checkOpenGLError("glActiveTexture");

  rTexture.bind();
  checkOpenGLError("glActiveTexture");

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
  checkOpenGLError("glBindVertexArray");

  glDrawArrays(GL_TRIANGLES, 0, 6);
  checkOpenGLError("glDrawArrays");

  glBindVertexArray(0);
  checkOpenGLError("glBindVertexArray");
}

void OpenGLSpriteRenderer::draw(Shader& rShader, glm::mat4 const& rTransform) {
  if (m_quadVAO == 0) {
    createQuadVAO();
  }

  rShader.use();

  checkOpenGLError("shader.use");

  rShader.setMatrix4("model", rTransform);
  checkOpenGLError("shader.setMatrix4");

  glBindVertexArray(m_quadVAO);
  checkOpenGLError("glBindVertexArray");

  glDrawArrays(GL_TRIANGLES, 0, 6);
  checkOpenGLError("glDrawArrays");

  glBindVertexArray(0);
  checkOpenGLError("glBindVertexArray");
}

void OpenGLSpriteRenderer::createTextureVAO(string textureName,
                                            glm::vec2 textureSize,
                                            glm::vec4 textureCoordinates) {
  float xs = textureCoordinates.x / textureSize.x;  // x start
  float xe =
      (textureCoordinates.x + textureCoordinates.z) / textureSize.x;  // x end
  float ys = textureCoordinates.y / textureSize.y;                    // y start
  float ye =
      (textureCoordinates.y + textureCoordinates.w) / textureSize.y;  // y end

  // Configure VAO/VBO
  unsigned int VBO;

  float verticesQuad[] = {
      // Positions    // Texture Coords
      0.0f, 1.0f, xs, ye,  // Top-left
      1.0f, 0.0f, xe, ys,  // Bottom-right
      0.0f, 0.0f, xs, ys,  // Bottom-left

      0.0f, 1.0f, xs, ye,  // Top-left
      1.0f, 1.0f, xe, ye,  // Top-right
      1.0f, 0.0f, xe, ys   // Bottom-right
  };

  unsigned int textureVAO;

  glGenVertexArrays(1, &textureVAO);
  checkOpenGLError("glGenVertexArrays");

  glGenBuffers(1, &VBO);
  checkOpenGLError("glGenBuffers");

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  checkOpenGLError("glBindBuffer");

  glBufferData(GL_ARRAY_BUFFER, sizeof(verticesQuad), verticesQuad,
               GL_STATIC_DRAW);
  checkOpenGLError("glBufferData");

  glBindVertexArray(textureVAO);
  checkOpenGLError("glBindVertexArray");

  glEnableVertexAttribArray(0);
  checkOpenGLError("glEnableVertexAttribArray");

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  checkOpenGLError("glVertexAttribPointer");

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  checkOpenGLError("glBindBuffer");

  glBindVertexArray(0);
  checkOpenGLError("glBindVertexArray");

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
  checkOpenGLError("glGenVertexArrays");

  glGenBuffers(1, &VBO);
  checkOpenGLError("glGenBuffers");

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  checkOpenGLError("glBindBuffer");

  glBufferData(GL_ARRAY_BUFFER, sizeof(verticesQuad), verticesQuad,
               GL_STATIC_DRAW);
  checkOpenGLError("glBufferData");

  glBindVertexArray(m_quadVAO);
  checkOpenGLError("glBindVertexArray");

  glEnableVertexAttribArray(0);
  checkOpenGLError("glEnableVertexAttribArray");

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  checkOpenGLError("glVertexAttribPointer");

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  checkOpenGLError("glBindBuffer");

  glBindVertexArray(0);
  checkOpenGLError("glBindVertexArray");
}