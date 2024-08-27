#pragma once
#ifndef OPENGL_TEXT_MANAGER_HPP
#define OPENGL_TEXT_MANAGER_HPP

#include <glm/glm.hpp>
#include <ft2build.h>
#include <map>
#include FT_FREETYPE_H
#include "disk/ResourceProvider.hpp"
#include "graphics/Shader.hpp"

typedef struct {
  unsigned int textureID;  // ID handle of the glyph texture
  glm::ivec2 size;         // Size of glyph
  glm::ivec2 bearing;      // Offset from baseline to left/top of glyph
  unsigned int advance;
} TextCharacter;

using std::map;
using std::string;

class OpenGLTextManager {
 public:
  OpenGLTextManager(ResourceProvider& rResourceProvider);
  ~OpenGLTextManager();

  void loadFont(string const& fontPath);

  /**
   * @brief Renders a character using the given parameters.
   * returns how much to advance the cursor after rendering the character.
   */
  float renderCharacter(char c, float scale, glm::vec3 color,
                        glm::mat4 const& transform, Shader& rShader);

 private:
  int loadCharacter(char c);

  ResourceProvider& m_rResourceProvider;
  FT_Library m_library;
  FT_Face m_face;
  map<char, TextCharacter*> m_characters = {};
  char* m_pFontData = nullptr;

  unsigned int m_VAO = 0;
  unsigned int m_VBO = 0;
};

#endif  // !OPENGL_TEXT_MANAGER_HPP
