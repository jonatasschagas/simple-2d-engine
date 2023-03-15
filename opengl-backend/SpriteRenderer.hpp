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

  void drawSprite(Shader& rShader, Texture2D const& rTexture,
                  glm::vec2 const& rPosition, glm::vec2 const& rSize,
                  glm::vec4 const& rTextureCoordinates, float rotate);

 private:
  void createTextureVAO(string textureName, glm::vec2 textureSize,
                        glm::vec4 textureCoordinates);

  map<string, unsigned int> m_textureVAOs;

  void initializeMembers() { m_textureVAOs.clear(); }
};

#endif