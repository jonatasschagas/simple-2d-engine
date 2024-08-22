#include "OpenGLTexture2d.hpp"
#include "OpenGLHeaders.h"
#include "OpenGLUtils.h"
#include <iostream>

OpenGLTexture2d::OpenGLTexture2d() {
  initializeMembers();
  glGenTextures(1, &m_id);
  checkOpenGLError("glGenTextures");
}

OpenGLTexture2d::~OpenGLTexture2d() {
  glDeleteTextures(1, &m_id);
  checkOpenGLError("glDeleteTextures");
  initializeMembers();
}

void OpenGLTexture2d::generate(unsigned int width, unsigned int height,
                               void* pData) {
  m_width = width;
  m_height = height;

  // create Texture
  glBindTexture(GL_TEXTURE_2D, m_id);
  checkOpenGLError("glBindTexture");
  glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, width, height, 0,
               m_imageFormat, GL_UNSIGNED_BYTE, pData);
  checkOpenGLError("glTexImage2D");
  // set Texture wrap and filter modes
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  checkOpenGLError("glTexParameteri");
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  checkOpenGLError("glTexParameteri");
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMin);
  checkOpenGLError("glTexParameteri");
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMax);
  checkOpenGLError("glTexParameteri");

  // unbind texture
  glBindTexture(GL_TEXTURE_2D, 0);
  checkOpenGLError("glBindTexture");
}

void OpenGLTexture2d::bind() const {
  glBindTexture(GL_TEXTURE_2D, m_id);
  checkOpenGLError("glBindTexture");
}
