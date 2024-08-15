#pragma once
#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "OpenGLHeaders.h"
#include "Shader.hpp"
#include "Texture2D.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include <string>

using namespace std;

class SpriteRenderer {
 public:
  SpriteRenderer();
  ~SpriteRenderer();

  void draw(Shader& rShader, glm::mat4 const& rTransform,
            Texture2D const& rTexture, glm::vec4 const& rTextureCoordinates);

  void draw(Shader& rShader, glm::mat4 const& rTransform,
            glm::vec4 const& color);

 private:
  void createTextureVAO(string textureName, glm::vec2 textureSize,
                        glm::vec4 textureCoordinates);

  void createQuadVAO();

  map<string, unsigned int> m_textureVAOs = {};
  unsigned int m_quadVAO = 0;

  void initializeMembers() { m_textureVAOs.clear(); }
};

#endif
