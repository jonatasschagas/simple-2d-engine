#pragma once
#ifndef OpenGLSpriteRenderer_hpp
#define OpenGLSpriteRenderer_hpp

#include "OpenGLHeaders.h"
#include "OpenGLTexture2d.hpp"
#include "graphics/Shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include <string>

using std::map;
using std::string;

class OpenGLSpriteRenderer {
 public:
  OpenGLSpriteRenderer();
  ~OpenGLSpriteRenderer();

  void draw(Shader& rShader, glm::mat4 const& rTransform,
            OpenGLTexture2d const& rTexture,
            glm::vec4 const& rTextureCoordinates);

  void draw(Shader& rShader, glm::mat4 const& rTransform);

 private:
  void createTextureVAO(string textureName, glm::vec2 textureSize,
                        glm::vec4 textureCoordinates);

  void createQuadVAO();

  map<string, unsigned int> m_textureVAOs = {};
  unsigned int m_quadVAO = 0;

  void initializeMembers() { m_textureVAOs.clear(); }
};

#endif /* OpenGLSpriteRenderer_hpp */
