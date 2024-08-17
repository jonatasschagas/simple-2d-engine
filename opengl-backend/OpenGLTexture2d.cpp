#include "OpenGLTexture2d.hpp"
#include "OpenGLHeaders.h"
#include <iostream>

OpenGLTexture2d::OpenGLTexture2d() {
  initializeMembers();
  glGenTextures(1, &m_id);
}

OpenGLTexture2d::~OpenGLTexture2d() {
  glDeleteTextures(1, &m_id);
  initializeMembers();
}

void OpenGLTexture2d::generate(unsigned int width, unsigned int height,
                               void* pData) {
  m_width = width;
  m_height = height;

  // create Texture
  glBindTexture(GL_TEXTURE_2D, m_id);
  glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, width, height, 0,
               m_imageFormat, GL_UNSIGNED_BYTE, pData);
  // set Texture wrap and filter modes
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMin);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMax);

  // unbind texture
  glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLTexture2d::bind() const { glBindTexture(GL_TEXTURE_2D, m_id); }
