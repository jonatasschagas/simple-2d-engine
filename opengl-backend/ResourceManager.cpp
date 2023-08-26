#include "ResourceManager.hpp"
#include "OpenGLHeaders.h"
#include "utils/FileUtils.h"
#include <fstream>
#include <iostream>
#include <sstream>

ResourceManager* ResourceManager::sm_pInstance{nullptr};
mutex ResourceManager::sm_mutexInstance;
ResourceManagerDestroyer ResourceManager::sm_destroyer;

ResourceManager::ResourceManager() { initializeMembers(); }

ResourceManager::~ResourceManager() { initializeMembers(); }

ResourceManager* ResourceManager::getInstance() {
  lock_guard<mutex> lock(sm_mutexInstance);
  if (sm_pInstance == nullptr) {
    sm_pInstance = new ResourceManager();
    sm_destroyer.setSingleton(sm_pInstance);
  }
  return sm_pInstance;
}

Shader& ResourceManager::loadShader(string const& vertexShaderFile,
                                    string const& fragShaderFile,
                                    string const& name,
                                    ResourceProvider& rResourceProvider) {
  string vertexCode;
  rResourceProvider.readContentsFromFile(vertexShaderFile, &vertexCode);
  string fragmentCode;
  rResourceProvider.readContentsFromFile(fragShaderFile, &fragmentCode);

  unique_ptr<Shader> pShader = make_unique<Shader>();
  pShader->compile(vertexCode.c_str(), fragmentCode.c_str());

  m_shadersMap[name] = move(pShader);

  return *m_shadersMap[name];
}

Shader& ResourceManager::getShader(string const& name) {
  return *m_shadersMap[name];
}

Texture2D& ResourceManager::loadTexture(string const& file, string const& name,
                                        ResourceProvider& rResourceProvider) {
  unique_ptr<Texture2D> pTexture = make_unique<Texture2D>();

  int width, height;
  void* data = rResourceProvider.loadTexture(file, &width, &height);

  pTexture->generate(width, height, data);

  delete[] data;

  m_texturesMap[name] = move(pTexture);

  return *m_texturesMap[name];
}

Texture2D& ResourceManager::getTexture(string const& name) {
  return *m_texturesMap[name];
}

ResourceManagerDestroyer::ResourceManagerDestroyer(
    ResourceManager* pResourceManager) {
  m_pResourceManager = pResourceManager;
}

ResourceManagerDestroyer::~ResourceManagerDestroyer() {
  delete m_pResourceManager;
}

void ResourceManagerDestroyer::setSingleton(ResourceManager* pResourceManager) {
  m_pResourceManager = pResourceManager;
}
