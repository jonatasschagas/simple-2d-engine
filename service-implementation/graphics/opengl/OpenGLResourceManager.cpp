#include "OpenGLResourceManager.hpp"
#include "OpenGLHeaders.h"
#include "OpenGLShader.hpp"
#include "utils/FileUtils.h"
#include <fstream>
#include <iostream>
#include <sstream>

OpenGLResourceManager::OpenGLResourceManager() { initializeMembers(); }

OpenGLResourceManager::~OpenGLResourceManager() {
  for (auto pShader : m_shadersMap) {
    delete pShader.second;
  }

  for (auto pTexture : m_texturesMap) {
    delete pTexture.second;
  }

  initializeMembers();
}

OpenGLShader& OpenGLResourceManager::loadShader(
    string const& vertexShaderFile, string const& fragShaderFile,
    string const& name, ResourceProvider& rResourceProvider) {
  string vertexCode;
  rResourceProvider.readContentsFromFile(vertexShaderFile, &vertexCode);
  string fragmentCode;
  rResourceProvider.readContentsFromFile(fragShaderFile, &fragmentCode);

  OpenGLShader* pShader = new OpenGLShader();
  pShader->load(vertexCode.c_str(), fragmentCode.c_str());

  m_shadersMap[name] = pShader;

  return *pShader;
}

OpenGLShader& OpenGLResourceManager::getShader(string const& name) {
  return *m_shadersMap[name];
}

OpenGLTexture2d& OpenGLResourceManager::loadTexture(
    string const& file, string const& name,
    ResourceProvider& rResourceProvider) {
  if (m_texturesMap.count(name) > 0) {
    return *m_texturesMap[name];
  }

  OpenGLTexture2d* pTexture = new OpenGLTexture2d();

  int width, height;
  void* data = rResourceProvider.loadTexture(file, &width, &height);

  pTexture->generate(width, height, data);

  delete[] data;

  m_texturesMap[name] = pTexture;

  return *pTexture;
}

OpenGLTexture2d& OpenGLResourceManager::getTexture(string const& name) {
  return *m_texturesMap[name];
}
