#include "ResourceManager.hpp"
#include "OpenGLHeaders.h"
#include <fstream>
#include <iostream>
#include <sstream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "utils/FileUtils.h"

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
                                    string const& name) {
  string vertexCode = loadFile(vertexShaderFile);
  string fragmentCode = loadFile(fragShaderFile);

  unique_ptr<Shader> pShader = make_unique<Shader>();
  pShader->compile(vertexCode.c_str(), fragmentCode.c_str());

  m_shadersMap[name] = move(pShader);

  return *m_shadersMap[name];
}

Shader& ResourceManager::getShader(string const& name) {
  return *m_shadersMap[name];
}

Texture2D& ResourceManager::loadTexture(string const& file,
                                        string const& name) {
  unique_ptr<Texture2D> pTexture = make_unique<Texture2D>();

  int width, height, nrChannels;
  unsigned char* data =
      stbi_load(file.c_str(), &width, &height, &nrChannels, 0);

  pTexture->generate(width, height, data);

  stbi_image_free(data);

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