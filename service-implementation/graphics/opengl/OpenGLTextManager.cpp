#include "OpenGLTextManager.hpp"
#include "OpenGLHeaders.h"
#include "OpenGLUtils.h"
#include "utils/Logging.h"
#include "utils/StringUtils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

OpenGLTextManager::OpenGLTextManager(ResourceProvider& rResourceProvider)
    : m_rResourceProvider(rResourceProvider) {
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);
  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

OpenGLTextManager::~OpenGLTextManager() {
  FT_Done_Face(m_face);
  FT_Done_FreeType(m_library);

  delete[] m_pFontData;
}

void OpenGLTextManager::loadFont(string const& fontPath) {
  if (FT_Init_FreeType(&m_library)) {
    logMessage(LogLevel::Error, "TextManager",
               "Could not init FreeType Library");
    return;
  }

  std::size_t fileSize = 0;
  m_pFontData = m_rResourceProvider.readBytesFromFile(fontPath, fileSize);

  if (FT_New_Memory_Face(m_library, reinterpret_cast<FT_Byte*>(m_pFontData),
                         fileSize, 0, &m_face)) {
    logMessage(LogLevel::Error, "TextManager", "Could not load font: %s",
               fontPath.c_str());
    return;
  }

  // set size to load glyphs as
  FT_Set_Pixel_Sizes(m_face, 0, 48);

  logMessage(LogLevel::Info, "TextManager", "Font loaded: %s",
             fontPath.c_str());

  glBindTexture(GL_TEXTURE_2D, 0);
}

int OpenGLTextManager::loadCharacter(char c) {
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // disable byte-alignment restriction
  checkOpenGLError("glPixelStorei");

  if (FT_Load_Char(m_face, c, FT_LOAD_RENDER)) {
    logMessage(LogLevel::Error, "TextManager", "Failed to load Glyph, %c", c);
    return -1;
  }

  if (c == ' ') {
    return 0;
  }

  string glyph = bytesToHexString(
      reinterpret_cast<char const*>(m_face->glyph->bitmap.buffer),
      sizeof(m_face->glyph->bitmap.buffer));
  string glyphDebugMessage = "Loading Glyph as texture: " + std::string(1, c);
  logMessage(LogLevel::Debug, "TextManager", glyphDebugMessage.c_str());
  logMessage(LogLevel::Debug, "TextManager", glyph.c_str());

  int blendingColor = GL_RED;
#ifdef ANDROID
  blendingColor = GL_ALPHA;  // android uses alpha for blending
#endif

  unsigned int texture;
  glGenTextures(1, &texture);
  checkOpenGLError("glGenTextures");

  glBindTexture(GL_TEXTURE_2D, texture);
  checkOpenGLError("glBindTexture");

  glTexImage2D(GL_TEXTURE_2D, 0, blendingColor, m_face->glyph->bitmap.width,
               m_face->glyph->bitmap.rows, 0, blendingColor, GL_UNSIGNED_BYTE,
               m_face->glyph->bitmap.buffer);
  checkOpenGLError("glTexImage2D");

  // Set texture options
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  TextCharacter* pCharacter = new TextCharacter();
  pCharacter->textureID = texture;
  pCharacter->size =
      glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows);
  pCharacter->bearing =
      glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top);
  pCharacter->advance = (unsigned int)m_face->glyph->advance.x;

  m_characters.insert(std::make_pair(c, pCharacter));

  return 0;
}

float OpenGLTextManager::renderCharacter(char c, float scale, glm::vec3 color,
                                         glm::mat4 const& transform,
                                         Shader& rShader) {
  rShader.setMatrix4("model", transform);
  rShader.setVector3f("textColor", color);

  checkOpenGLError("shader use");

  glActiveTexture(GL_TEXTURE0);
  checkOpenGLError("glActiveTexture");

  glBindVertexArray(m_VAO);
  checkOpenGLError("glBindVertexArray");

  if (!m_characters.count(c)) {
    int result = loadCharacter(c);
    assert(result == 0 &&
           "Failed to load character from font file into memory buffer.");
  }

  TextCharacter* pCH = m_characters[c];

  if (pCH == nullptr) {
    return 0;
  }

  // float xpos = pCH->bearing.x * scale; // this looks weird for the characters
  // 1 and :
  float xpos = 0;
  float ypos = (pCH->size.y - pCH->bearing.y) * scale;

  // now advance cursors for next glyph (note that advance is number of 1/64
  // pixels)
  float totalWidth = (pCH->advance >> 6) * scale;
  float w = (pCH->size.x * 1.0f) / totalWidth;
  float h = (pCH->size.y * 1.0f) / totalWidth;

  // update VBO for each character
  // characters are drawn clockwise
  glFrontFace(GL_CW);

  float vertices[6][4] = {
      {xpos, ypos + h, 0.0f, 1.0f},    {xpos, ypos, 0.0f, 0.0f},
      {xpos + w, ypos, 1.0f, 0.0f},

      {xpos, ypos + h, 0.0f, 1.0f},    {xpos + w, ypos, 1.0f, 0.0f},
      {xpos + w, ypos + h, 1.0f, 1.0f}};

  // render glyph texture over quad
  glBindTexture(GL_TEXTURE_2D, pCH->textureID);
  checkOpenGLError("glBindTexture");

  // update content of VBO memory
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  checkOpenGLError("glBindBuffer");

  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
  checkOpenGLError("glBufferSubData");

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  checkOpenGLError("glBindBuffer");

  // render quad
  glDrawArrays(GL_TRIANGLES, 0, 6);
  checkOpenGLError("glDrawArrays");

  // reset to default
  glFrontFace(GL_CCW);

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);

  // now advance cursors for next glyph (note that advance is number of 1/64
  // pixels)
  return (pCH->advance >> 6) *
         scale;  // bitshift by 6 to get value in pixels (2^6 = 64)
}
