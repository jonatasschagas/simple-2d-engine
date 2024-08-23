#pragma once
#ifndef OpenGLTexture2d_hpp
#define OpenGLTexture2d_hpp

#include "OpenGLHeaders.h"

class OpenGLTexture2d {
 public:
  // constructor (sets default texture modes)
  OpenGLTexture2d();
  ~OpenGLTexture2d();

  // generates texture from image data
  void generate(unsigned int width, unsigned int height, void* pData);

  // binds the texture as the current active GL_TEXTURE_2D texture object
  void bind() const;

  // getters
  unsigned int getWidth() const { return m_width; }
  unsigned int getHeight() const { return m_height; }
  unsigned int getInternalFormat() const { return m_internalFormat; }
  unsigned int getImageFormat() const { return m_imageFormat; }
  unsigned int getWrapS() const { return m_wrapS; }
  unsigned int getWrapT() const { return m_wrapT; }
  unsigned int getFilterMin() const { return m_filterMin; }
  unsigned int getFilterMax() const { return m_filterMax; }
  unsigned int getId() const { return m_id; }

 private:
  // holds the ID of the texture object, used for all texture operations to
  // reference to this particular texture
  unsigned int m_id;
  // texture image dimensions
  unsigned int m_width;
  unsigned int m_height;

  // texture Format
  unsigned int m_internalFormat;  // format of texture object
  unsigned int m_imageFormat;     // format of loaded image

  // texture configuration
  unsigned int m_wrapS;      // wrapping mode on S axis
  unsigned int m_wrapT;      // wrapping mode on T axis
  unsigned int m_filterMin;  // filtering mode if texture pixels < screen pixels
  unsigned int m_filterMax;  // filtering mode if texture pixels > screen pixels

  void initializeMembers() {
    m_id = 0;
    m_width = 0;
    m_height = 0;
    m_internalFormat = GL_RGBA;
    m_imageFormat = GL_RGBA;
    m_wrapS = GL_CLAMP_TO_EDGE;  // Or GL_REPEAT if you prefer
    m_wrapT = GL_CLAMP_TO_EDGE;  // Or GL_REPEAT if you prefer
    m_filterMin = GL_LINEAR;
    m_filterMax = GL_LINEAR;
  }
};

#endif /* OpenGLTexture2d_hpp */