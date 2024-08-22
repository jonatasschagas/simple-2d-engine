#pragma once
#ifndef OpenGLResourceManager_hpp
#define OpenGLResourceManager_hpp

#include "OpenGLHeaders.h"
#include "OpenGLShader.hpp"
#include "OpenGLTexture2d.hpp"
#include "disk/ResourceProvider.hpp"
#include <map>
#include <memory>
#include <mutex>
#include <string>

using std::map;
using std::string;

class OpenGLResourceManager {
 public:
  OpenGLResourceManager();
  ~OpenGLResourceManager();

  OpenGLShader& loadShader(string const& vertexShaderFile,
                           string const& fragShaderFile, string const& name,
                           ResourceProvider& rResourceProvider);

  OpenGLShader& getShader(string const& name);

  OpenGLTexture2d& loadTexture(string const& file, string const& name,
                               ResourceProvider& rResourceProvider);

  OpenGLTexture2d& getTexture(string const& name);

 private:
  map<string, OpenGLShader*> m_shadersMap;
  map<string, OpenGLTexture2d*> m_texturesMap;

  void initializeMembers() {
    m_shadersMap.clear();
    m_texturesMap.clear();
  }
};

#endif /* OpenGLResourceManager_hpp */